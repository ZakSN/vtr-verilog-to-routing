#include <cstdio>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <limits>
#include <queue>

#include "vtr_assert.h"
#include "vtr_log.h"
#include "vtr_math.h"

#include "vpr_error.h"
#include "vpr_types.h"

#include "read_xml_arch_file.h"
#include "globals.h"
#include "atom_netlist.h"
#include "prepack.h"
#include "pack_types.h"
#include "pack.h"
#include "read_blif.h"
#include "cluster.h"
#include "SetupGrid.h"
#include "re_cluster.h"

/* #define DUMP_PB_GRAPH 1 */
/* #define DUMP_BLIF_INPUT 1 */

static bool try_size_device_grid(const t_arch& arch,
                                 const std::map<t_logical_block_type_ptr,size_t>& num_type_instances,
                                 float target_device_utilization,
                                 const std::string& device_layout_name);

/**
 * @brief Counts the total number of logic models that the architecture can implement.
 *
 * @param user_models A linked list of logic models.
 * @return int The total number of models in the linked list
 */
static int count_models(const t_model* user_models);

static std::vector<AtomBlockId> find_noc_router_atoms() {
    const auto& atom_ctx = g_vpr_ctx.atom();

    // NoC router atoms are expected to have a specific blif model
    const std::string noc_router_blif_model_name = "noc_router_adapter_block";

    // stores found NoC router atoms
    std::vector<AtomBlockId> noc_router_atoms;

    // iterate over all atoms and find those whose blif model matches
    for (auto atom_id : atom_ctx.nlist.blocks()) {
        const t_model* model = atom_ctx.nlist.block_model(atom_id);
        if (noc_router_blif_model_name == model->name) {
            noc_router_atoms.push_back(atom_id);
        }
    }

    return noc_router_atoms;
}

static void update_noc_reachability_partitions(const std::vector<AtomBlockId>& noc_atoms) {
    const auto& atom_ctx = g_vpr_ctx.atom();
    auto& constraints = g_vpr_ctx.mutable_floorplanning().constraints;
    const auto& high_fanout_thresholds = g_vpr_ctx.cl_helper().high_fanout_thresholds;
    const auto& device_ctx = g_vpr_ctx.device();
    const auto& grid = device_ctx.grid;

    t_logical_block_type_ptr logic_block_type = infer_logic_block_type(grid);
    const size_t high_fanout_threshold = high_fanout_thresholds.get_threshold(logic_block_type->name);

    // get the total number of atoms
    const size_t n_atoms = atom_ctx.nlist.blocks().size();

    vtr::vector<AtomBlockId, bool> atom_visited(n_atoms, false);

    int exclusivity_cnt = 0;

    RegionRectCoord unconstrained_rect{0,
                                       0,
                                       std::numeric_limits<int>::max(),
                                       std::numeric_limits<int>::max(),
                                       0};
    Region unconstrained_region;
    unconstrained_region.set_region_rect(unconstrained_rect);

    for (auto noc_atom_id : noc_atoms) {
        // check if this NoC router has already been visited
        if (atom_visited[noc_atom_id]) {
            continue;
        }

        exclusivity_cnt++;

        PartitionRegion associated_noc_partition_region;
        associated_noc_partition_region.set_exclusivity_index(exclusivity_cnt);
        associated_noc_partition_region.add_to_part_region(unconstrained_region);

        Partition associated_noc_partition;
        associated_noc_partition.set_name(atom_ctx.nlist.block_name(noc_atom_id));
        associated_noc_partition.set_part_region(associated_noc_partition_region);
        auto associated_noc_partition_id = (PartitionId)constraints.get_num_partitions();
        constraints.add_partition(associated_noc_partition);

        const PartitionId noc_partition_id = constraints.get_atom_partition(noc_atom_id);

        if (noc_partition_id == PartitionId::INVALID()) {
            constraints.add_constrained_atom(noc_atom_id, associated_noc_partition_id);
        } else {    // noc atom is already in a partition
            auto& noc_partition = constraints.get_mutable_partition(noc_partition_id);
            auto& noc_partition_region = noc_partition.get_mutable_part_region();
            VTR_ASSERT(noc_partition_region.get_exclusivity_index() < 0);
            noc_partition_region.set_exclusivity_index(exclusivity_cnt);
        }

        std::queue<AtomBlockId> q;
        q.push(noc_atom_id);
        atom_visited[noc_atom_id] = true;

        while (!q.empty()) {
            AtomBlockId current_atom = q.front();
            q.pop();

            PartitionId atom_partition_id = constraints.get_atom_partition(current_atom);
            if (atom_partition_id == PartitionId::INVALID()) {
                constraints.add_constrained_atom(current_atom, associated_noc_partition_id);
            } else {
                auto& atom_partition = constraints.get_mutable_partition(atom_partition_id);
                auto& atom_partition_region = atom_partition.get_mutable_part_region();
                VTR_ASSERT(atom_partition_region.get_exclusivity_index() < 0 || current_atom == noc_atom_id);
                atom_partition_region.set_exclusivity_index(exclusivity_cnt);
            }

            for(auto pin : atom_ctx.nlist.block_pins(current_atom)) {
                AtomNetId net_id = atom_ctx.nlist.pin_net(pin);
                size_t net_fanout = atom_ctx.nlist.net_sinks(net_id).size();

                if (net_fanout >= high_fanout_threshold) {
                    continue;
                }

                AtomBlockId driver_atom_id = atom_ctx.nlist.net_driver_block(net_id);
                if (!atom_visited[driver_atom_id]) {
                    q.push(driver_atom_id);
                    atom_visited[driver_atom_id] = true;
                }

                for (auto sink_pin : atom_ctx.nlist.net_sinks(net_id)) {
                    AtomBlockId sink_atom_id = atom_ctx.nlist.pin_block(sink_pin);
                    if (!atom_visited[sink_atom_id]) {
                        q.push(sink_atom_id);
                        atom_visited[sink_atom_id] = true;
                    }
                }

            }
        }

    }
}


bool try_pack(t_packer_opts* packer_opts,
              const t_analysis_opts* analysis_opts,
              const t_arch* arch,
              const t_model* user_models,
              const t_model* library_models,
              float interc_delay,
              std::vector<t_lb_type_rr_node>* lb_type_rr_graphs) {
    auto& helper_ctx = g_vpr_ctx.mutable_cl_helper();
    auto& atom_ctx = g_vpr_ctx.atom();
    auto& atom_mutable_ctx = g_vpr_ctx.mutable_atom();

    std::unordered_set<AtomNetId> is_clock, is_global;
    std::unordered_map<AtomBlockId, t_pb_graph_node*> expected_lowest_cost_pb_gnode; //The molecules associated with each atom block
    t_clustering_data clustering_data;
    std::vector<t_pack_patterns> list_of_packing_patterns;
    VTR_LOG("Begin packing '%s'.\n", packer_opts->circuit_file_name.c_str());

    /* determine number of models in the architecture */
    helper_ctx.num_models = count_models(user_models);
    helper_ctx.num_models += count_models(library_models);

    is_clock = alloc_and_load_is_clock(packer_opts->global_clocks);
    is_global.insert(is_clock.begin(), is_clock.end());

    size_t num_p_inputs = 0;
    size_t num_p_outputs = 0;
    for (auto blk_id : atom_ctx.nlist.blocks()) {
        auto type = atom_ctx.nlist.block_type(blk_id);
        if (type == AtomBlockType::INPAD) {
            ++num_p_inputs;
        } else if (type == AtomBlockType::OUTPAD) {
            ++num_p_outputs;
        }
    }

    VTR_LOG("\n");
    VTR_LOG("After removing unused inputs...\n");
    VTR_LOG("\ttotal blocks: %zu, total nets: %zu, total inputs: %zu, total outputs: %zu\n",
            atom_ctx.nlist.blocks().size(), atom_ctx.nlist.nets().size(), num_p_inputs, num_p_outputs);

    VTR_LOG("Begin prepacking.\n");
    list_of_packing_patterns = alloc_and_load_pack_patterns();

    //To ensure the list of packing patterns gets freed in case of an error, we create
    //a unique_ptr with custom deleter which will free the list at the end of the current
    //scope.
    auto list_of_packing_patterns_deleter = [](std::vector<t_pack_patterns>* ptr) {
        free_list_of_pack_patterns(*ptr);
    };
    std::unique_ptr<std::vector<t_pack_patterns>, decltype(list_of_packing_patterns_deleter)> list_of_packing_patterns_cleanup_guard(&list_of_packing_patterns,
                                                                                                                                     list_of_packing_patterns_deleter);

    atom_mutable_ctx.list_of_pack_molecules.reset(alloc_and_load_pack_molecules(list_of_packing_patterns.data(),
                                                                                expected_lowest_cost_pb_gnode,
                                                                                list_of_packing_patterns.size()));

    /* We keep attraction groups off in the first iteration,  and
     * only turn on in later iterations if some floorplan regions turn out to be overfull.
     */
    AttractionInfo attraction_groups(false);
    VTR_LOG("%d attraction groups were created during prepacking.\n", attraction_groups.num_attraction_groups());
    VTR_LOG("Finish prepacking.\n");

    if (packer_opts->auto_compute_inter_cluster_net_delay) {
        packer_opts->inter_cluster_net_delay = interc_delay;
        VTR_LOG("Using inter-cluster delay: %g\n", packer_opts->inter_cluster_net_delay);
    }

    helper_ctx.target_external_pin_util = t_ext_pin_util_targets(packer_opts->target_external_pin_util);
    helper_ctx.high_fanout_thresholds = t_pack_high_fanout_thresholds(packer_opts->high_fanout_threshold);

    VTR_LOG("Packing with pin utilization targets: %s\n", helper_ctx.target_external_pin_util.to_string().c_str());
    VTR_LOG("Packing with high fanout thresholds: %s\n", helper_ctx.high_fanout_thresholds.to_string().c_str());

    bool allow_unrelated_clustering = false;
    if (packer_opts->allow_unrelated_clustering == e_unrelated_clustering::ON) {
        allow_unrelated_clustering = true;
    } else if (packer_opts->allow_unrelated_clustering == e_unrelated_clustering::OFF) {
        allow_unrelated_clustering = false;
    }

    bool balance_block_type_util = false;
    if (packer_opts->balance_block_type_utilization == e_balance_block_type_util::ON) {
        balance_block_type_util = true;
    } else if (packer_opts->balance_block_type_utilization == e_balance_block_type_util::OFF) {
        balance_block_type_util = false;
    }

    int pack_iteration = 1;
    bool floorplan_regions_overfull = false;

    auto constraints_backup = g_vpr_ctx.floorplanning().constraints;
    // find all NoC router atoms
    auto noc_atoms = find_noc_router_atoms();
    update_noc_reachability_partitions(noc_atoms);

    while (true) {
        free_clustering_data(*packer_opts, clustering_data);

        //Cluster the netlist
        helper_ctx.num_used_type_instances = do_clustering(
            *packer_opts,
            *analysis_opts,
            arch, atom_mutable_ctx.list_of_pack_molecules.get(),
            is_clock,
            is_global,
            expected_lowest_cost_pb_gnode,
            allow_unrelated_clustering,
            balance_block_type_util,
            lb_type_rr_graphs,
            attraction_groups,
            floorplan_regions_overfull,
            clustering_data);

        //Try to size/find a device
        bool fits_on_device = try_size_device_grid(*arch, helper_ctx.num_used_type_instances, packer_opts->target_device_utilization, packer_opts->device_layout);

        /* We use this bool to determine the cause for the clustering not being dense enough. If the clustering
         * is not dense enough and there are floorplan constraints, it is presumed that the constraints are the cause
         * of the floorplan not fitting, so attraction groups are turned on for later iterations.
         */
        bool floorplan_not_fitting = (floorplan_regions_overfull || g_vpr_ctx.floorplanning().constraints.get_num_partitions() > 0);

        if (fits_on_device && !floorplan_regions_overfull) {
            break; //Done
        } else if (pack_iteration == 1 && !floorplan_not_fitting) {
            //1st pack attempt was unsuccessful (i.e. not dense enough) and we have control of unrelated clustering
            //
            //Turn it on to increase packing density
            if (packer_opts->allow_unrelated_clustering == e_unrelated_clustering::AUTO) {
                VTR_ASSERT(allow_unrelated_clustering == false);
                allow_unrelated_clustering = true;
            }
            if (packer_opts->balance_block_type_utilization == e_balance_block_type_util::AUTO) {
                VTR_ASSERT(balance_block_type_util == false);
                balance_block_type_util = true;
            }
            VTR_LOG("Packing failed to fit on device. Re-packing with: unrelated_logic_clustering=%s balance_block_type_util=%s\n",
                    (allow_unrelated_clustering ? "true" : "false"),
                    (balance_block_type_util ? "true" : "false"));
            /*
             * When running with tight floorplan constraints, some regions may become overfull with clusters (i.e.
             * the number of blocks assigned to the region exceeds the number of blocks available). When this occurs, we
             * cluster more densely to be able to adhere to the floorplan constraints. However, we do not want to cluster more
             * densely unnecessarily, as this can negatively impact wirelength. So, we have iterative approach. We check at the end
             * of every iteration if any floorplan regions are overfull. In the first iteration, we run
             * with no attraction groups (not packing more densely). If regions are overfull at the end of the first iteration,
             * we create attraction groups for partitions with overfull regions (pack those atoms more densely). We continue this way
             * until the last iteration, when we create attraction groups for every partition, if needed.
             */
        } else if (pack_iteration == 1 && floorplan_not_fitting) {
            VTR_LOG("Floorplan regions are overfull: trying to pack again using cluster attraction groups. \n");
            attraction_groups.create_att_groups_for_overfull_regions();
            attraction_groups.set_att_group_pulls(1);

        } else if (pack_iteration >= 2 && pack_iteration < 5 && floorplan_not_fitting) {
            if (pack_iteration == 2) {
                VTR_LOG("Floorplan regions are overfull: trying to pack again with more attraction groups exploration. \n");
                attraction_groups.create_att_groups_for_overfull_regions();
                VTR_LOG("Pack iteration is %d\n", pack_iteration);
            } else if (pack_iteration == 3) {
                attraction_groups.create_att_groups_for_all_regions();
                VTR_LOG("Floorplan regions are overfull: trying to pack again with more attraction groups exploration. \n");
                VTR_LOG("Pack iteration is %d\n", pack_iteration);
            } else if (pack_iteration == 4) {
                attraction_groups.create_att_groups_for_all_regions();
                VTR_LOG("Floorplan regions are overfull: trying to pack again with more attraction groups exploration and higher target pin utilization. \n");
                VTR_LOG("Pack iteration is %d\n", pack_iteration);
                attraction_groups.set_att_group_pulls(4);
                t_ext_pin_util pin_util(1.0, 1.0);
                helper_ctx.target_external_pin_util.set_block_pin_util("clb", pin_util);
            }

        } else { //Unable to pack densely enough: Give Up
            if (floorplan_regions_overfull) {
                VPR_FATAL_ERROR(VPR_ERROR_OTHER,
                                "Failed to find pack clusters densely enough to fit in the designated floorplan regions.\n"
                                "The floorplan regions may need to be expanded to run successfully. \n");
            }

            //No suitable device found
            std::string resource_reqs;
            std::string resource_avail;
            auto& grid = g_vpr_ctx.device().grid;
            for (auto iter = helper_ctx.num_used_type_instances.begin(); iter != helper_ctx.num_used_type_instances.end(); ++iter) {
                if (iter != helper_ctx.num_used_type_instances.begin()) {
                    resource_reqs += ", ";
                    resource_avail += ", ";
                }

                resource_reqs += std::string(iter->first->name) + ": " + std::to_string(iter->second);

                int num_instances = 0;
                for (auto type : iter->first->equivalent_tiles)
                    num_instances += grid.num_instances(type, -1);

                resource_avail += std::string(iter->first->name) + ": " + std::to_string(num_instances);
            }

            VPR_FATAL_ERROR(VPR_ERROR_OTHER, "Failed to find device which satisfies resource requirements required: %s (available %s)", resource_reqs.c_str(), resource_avail.c_str());
        }

        //Reset clustering for re-packing
        for (auto blk : g_vpr_ctx.atom().nlist.blocks()) {
            g_vpr_ctx.mutable_atom().lookup.set_atom_clb(blk, ClusterBlockId::INVALID());
            g_vpr_ctx.mutable_atom().lookup.set_atom_pb(blk, nullptr);
        }
        for (auto net : g_vpr_ctx.atom().nlist.nets()) {
            g_vpr_ctx.mutable_atom().lookup.set_atom_clb_net(net, ClusterNetId::INVALID());
        }
        g_vpr_ctx.mutable_floorplanning().cluster_constraints.clear();
        //attraction_groups.reset_attraction_groups();

        free_cluster_placement_stats(helper_ctx.cluster_placement_stats);
        delete[] helper_ctx.primitives_list;

        ++pack_iteration;
    }

    /* Packing iterative improvement can be done here */
    /*       Use the re-cluster API to edit it        */
    /******************* Start *************************/
    VTR_LOG("Start the iterative improvement process\n");
    //iteratively_improve_packing(*packer_opts, clustering_data, 2);
    VTR_LOG("the iterative improvement process is done\n");

    /*
     * auto& cluster_ctx = g_vpr_ctx.clustering();
     * for (auto& blk_id : g_vpr_ctx.clustering().clb_nlist.blocks()) {
     * free_pb_stats_recursive(cluster_ctx.clb_nlist.block_pb(blk_id));
     * }
     */
    /******************** End **************************/

    //check clustering and output it
    check_and_output_clustering(*packer_opts, is_clock, arch, helper_ctx.total_clb_num, clustering_data.intra_lb_routing);


    g_vpr_ctx.mutable_floorplanning().constraints = constraints_backup;
    const int max_y = (int)g_vpr_ctx.device().grid.height();
    const int max_x = (int)g_vpr_ctx.device().grid.width();
    for (auto& cluster_partition_region : g_vpr_ctx.mutable_floorplanning().cluster_constraints) {
        const auto& regions = cluster_partition_region.get_regions();
        if (regions.size() == 1) {
            const auto rect = regions[0].get_region_rect();

            if (rect.xmin <= 0 && rect.ymin <= 0 && rect.xmax >= max_x && rect.ymax >= max_y) {
                cluster_partition_region = PartitionRegion();
            }
        }
    }

    // Free Data Structures
    free_clustering_data(*packer_opts, clustering_data);

    VTR_LOG("\n");
    VTR_LOG("Netlist conversion complete.\n");
    VTR_LOG("\n");

    return true;
}

float get_arch_switch_info(short switch_index, int switch_fanin, float& Tdel_switch, float& R_switch, float& Cout_switch) {
    /* Fetches delay, resistance and output capacitance of the architecture switch at switch_index.
     * Returns the total delay through the switch. Used to calculate inter-cluster net delay. */

    /* The intrinsic delay may depend on fanin to the switch. If the delay map of a
     * switch from the architecture file has multiple (#inputs, delay) entries, we
     * interpolate/extrapolate to get the delay at 'switch_fanin'. */
    auto& device_ctx = g_vpr_ctx.device();

    Tdel_switch = device_ctx.arch_switch_inf[switch_index].Tdel(switch_fanin);
    R_switch = device_ctx.arch_switch_inf[switch_index].R;
    Cout_switch = device_ctx.arch_switch_inf[switch_index].Cout;

    /* The delay through a loaded switch is its intrinsic (unloaded)
     * delay plus the product of its resistance and output capacitance. */
    return Tdel_switch + R_switch * Cout_switch;
}

std::unordered_set<AtomNetId> alloc_and_load_is_clock(bool global_clocks) {
    /* Looks through all the atom blocks to find and mark all the clocks, by setting
     * the corresponding entry by adding the clock to is_clock.
     * global_clocks is used
     * only for an error check.                                                */

    int num_clocks = 0;
    std::unordered_set<AtomNetId> is_clock;

    /* Want to identify all the clock nets.  */
    auto& atom_ctx = g_vpr_ctx.atom();

    for (auto blk_id : atom_ctx.nlist.blocks()) {
        for (auto pin_id : atom_ctx.nlist.block_clock_pins(blk_id)) {
            auto net_id = atom_ctx.nlist.pin_net(pin_id);
            if (!is_clock.count(net_id)) {
                is_clock.insert(net_id);
                num_clocks++;
            }
        }
    }

    /* If we have multiple clocks and we're supposed to declare them global, *
     * print a warning message, since it looks like this circuit may have    *
     * locally generated clocks.                                             */

    if (num_clocks > 1 && global_clocks) {
        VTR_LOG_WARN(
            "All %d clocks will be treated as global.\n", num_clocks);
    }

    return (is_clock);
}

static bool try_size_device_grid(const t_arch& arch,
                                 const std::map<t_logical_block_type_ptr, size_t>& num_type_instances,
                                 float target_device_utilization,
                                 const std::string& device_layout_name) {
    auto& device_ctx = g_vpr_ctx.mutable_device();

    //Build the device
    auto grid = create_device_grid(device_layout_name, arch.grid_layouts, num_type_instances, target_device_utilization);

    /*
     *Report on the device
     */
    VTR_LOG("FPGA sized to %zu x %zu (%s)\n", grid.width(), grid.height(), grid.name().c_str());

    bool fits_on_device = true;

    float device_utilization = calculate_device_utilization(grid, num_type_instances);
    VTR_LOG("Device Utilization: %.2f (target %.2f)\n", device_utilization, target_device_utilization);
    std::map<t_logical_block_type_ptr, float> type_util;
    for (const auto& type : device_ctx.logical_block_types) {
        if (is_empty_type(&type)) continue;

        auto itr = num_type_instances.find(&type);
        if (itr == num_type_instances.end()) continue;

        float num_instances = itr->second;
        float util = 0.;

        float num_total_instances = 0.;
        for (const auto& equivalent_tile : type.equivalent_tiles) {
            num_total_instances += device_ctx.grid.num_instances(equivalent_tile, -1);
        }

        if (num_total_instances != 0) {
            util = num_instances / num_total_instances;
        }
        type_util[&type] = util;

        if (util > 1.) {
            fits_on_device = false;
        }
        VTR_LOG("\tBlock Utilization: %.2f Type: %s\n", util, type.name);
    }
    VTR_LOG("\n");

    return fits_on_device;
}

static int count_models(const t_model* user_models) {
    if (user_models == nullptr) {
        return 0;
    }

    const t_model* cur_model = user_models;
    int n_models = 0;

    while (cur_model) {
        n_models++;
        cur_model = cur_model->next;
    }

    return n_models;
}