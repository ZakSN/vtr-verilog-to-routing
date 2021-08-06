yosys -import

# Read VTR baseline library first
read_verilog -nomem2reg $env(PRIMITIVES);
setattr -mod -set keep_hierarchy 1 single_port_ram;
setattr -mod -set keep_hierarchy 1 dual_port_ram;

# Read the hardware decription Verilog
read_verilog -nomem2reg -nolatches $env(TCL_CIRCUIT);
# Check that cells match libraries and find top module
hierarchy -check -auto-top;

# Make name convention more readable
autoname;
# Translate processes to entlist components such as MUXs, FFs and latches
procs; opt;
# Extraction and optimization of finite state machines
fsm; opt;
# Collects memories, their port and create multiport memory cells
memory_collect; memory_dff; opt;

# Looking for combinatorial loops, wires with multiple drivers and used wires without any driver.
check;
# resolve asynchronous dffs
techmap -map $env(ODIN_TECHLIB)/adff2dff.v;
techmap -map $env(ODIN_TECHLIB)/adffe2dff.v;
# convert mem block to bram/rom

# [NOTE]: Yosys complains about expression width more than 24 bits.
# E.g. [63:0] memory [18:0] ==>  ERROR: Expression width 33554432 exceeds implementation limit of 16777216!
# mem will be handled using Odin-II
# memory_bram -rules $env(ODIN_TECHLIB)/mem_rules.txt
# techmap -map $env(ODIN_TECHLIB)/mem_map.v; 

# Transform the design into a new one with single top module
flatten;
# Transforms pmux into trees of regular multiplexers
pmuxtree;
# undirven to ensure there is no wire without drive
opt -undriven -full; # -noff #potential option to remove all sdff and etc. Only dff will remain
# Make name convention more readable
autoname;
# Print statistics
stat;

# param is to print non-standard cells attributes
# impltf is also used not to show the definition of primary netlist ports, i.e. VCC, GND and PAD, in the output.
write_blif -param -impltf $env(OUTPUT_BLIF_PATH)/$env(TCL_BLIF_NAME);

exit;
