#pragma once
/*
 * This file is generated by uxsdcxx 0.1.0.
 * https://github.com/duck2/uxsdcxx
 * Modify only if your build process doesn't involve regenerating this file.
 *
 * Cmdline: uxsdcxx/uxsdcxx.py /home/amin/vtr-verilog-to-routing/libs/librrgraph/src/io/rr_graph.xsd
 * Input file: /home/amin/vtr-verilog-to-routing/libs/librrgraph/src/io/rr_graph.xsd
 * md5sum of input file: 8672cb3951993f7e0ea3433a02507672
 */

#include <functional>


/* All uxsdcxx functions and structs live in this namespace. */

#include <cstdlib>
#include <tuple>

namespace uxsd {

/* Enum tokens generated from XSD enumerations. */

enum class enum_switch_type {UXSD_INVALID = 0, MUX, TRISTATE, PASS_GATE, SHORT, BUFFER};

enum class enum_pin_type {UXSD_INVALID = 0, OPEN, OUTPUT, INPUT};

enum class enum_node_type {UXSD_INVALID = 0, CHANX, CHANY, SOURCE, SINK, OPIN, IPIN};

enum class enum_node_direction {UXSD_INVALID = 0, INC_DIR, DEC_DIR, BI_DIR};

enum class enum_loc_side {UXSD_INVALID = 0, LEFT, RIGHT, TOP, BOTTOM, RIGHT_LEFT, RIGHT_BOTTOM, RIGHT_BOTTOM_LEFT, TOP_RIGHT, TOP_BOTTOM, TOP_LEFT, TOP_RIGHT_BOTTOM, TOP_RIGHT_LEFT, TOP_BOTTOM_LEFT, TOP_RIGHT_BOTTOM_LEFT, BOTTOM_LEFT};

/* Base class for the schema. */
struct DefaultRrGraphContextTypes {
using ChannelReadContext = void *;
	using XListReadContext = void *;
	using YListReadContext = void *;
	using ChannelsReadContext = void *;
	using TimingReadContext = void *;
	using SizingReadContext = void *;
	using SwitchReadContext = void *;
	using SwitchesReadContext = void *;
	using SegmentTimingReadContext = void *;
	using SegmentReadContext = void *;
	using SegmentsReadContext = void *;
	using PinReadContext = void *;
	using PinClassReadContext = void *;
	using BlockTypeReadContext = void *;
	using BlockTypesReadContext = void *;
	using GridLocReadContext = void *;
	using GridLocsReadContext = void *;
	using NodeLocReadContext = void *;
	using NodeTimingReadContext = void *;
	using NodeSegmentReadContext = void *;
	using MetaReadContext = void *;
	using MetadataReadContext = void *;
	using NodeReadContext = void *;
	using RrNodesReadContext = void *;
	using EdgeReadContext = void *;
	using RrEdgesReadContext = void *;
	using RrGraphReadContext = void *;
using ChannelWriteContext = void *;
	using XListWriteContext = void *;
	using YListWriteContext = void *;
	using ChannelsWriteContext = void *;
	using TimingWriteContext = void *;
	using SizingWriteContext = void *;
	using SwitchWriteContext = void *;
	using SwitchesWriteContext = void *;
	using SegmentTimingWriteContext = void *;
	using SegmentWriteContext = void *;
	using SegmentsWriteContext = void *;
	using PinWriteContext = void *;
	using PinClassWriteContext = void *;
	using BlockTypeWriteContext = void *;
	using BlockTypesWriteContext = void *;
	using GridLocWriteContext = void *;
	using GridLocsWriteContext = void *;
	using NodeLocWriteContext = void *;
	using NodeTimingWriteContext = void *;
	using NodeSegmentWriteContext = void *;
	using MetaWriteContext = void *;
	using MetadataWriteContext = void *;
	using NodeWriteContext = void *;
	using RrNodesWriteContext = void *;
	using EdgeWriteContext = void *;
	using RrEdgesWriteContext = void *;
	using RrGraphWriteContext = void *;
};

template<typename ContextTypes=DefaultRrGraphContextTypes>
class RrGraphBase {
public:
	virtual ~RrGraphBase() {}
	virtual void start_load(const std::function<void(const char*)> *report_error) = 0;
	virtual void finish_load() = 0;
	virtual void start_write() = 0;
	virtual void finish_write() = 0;
	virtual void error_encountered(const char * file, int line, const char *message) = 0;
	/** Generated for complex type "channel":
	 * <xs:complexType name="channel">
	 *   <xs:attribute name="chan_width_max" type="xs:int" use="required" />
	 *   <xs:attribute name="x_min" type="xs:int" use="required" />
	 *   <xs:attribute name="y_min" type="xs:int" use="required" />
	 *   <xs:attribute name="x_max" type="xs:int" use="required" />
	 *   <xs:attribute name="y_max" type="xs:int" use="required" />
	 * </xs:complexType>
	*/
	virtual inline int get_channel_chan_width_max(typename ContextTypes::ChannelReadContext &ctx) = 0;
	virtual inline int get_channel_x_max(typename ContextTypes::ChannelReadContext &ctx) = 0;
	virtual inline int get_channel_x_min(typename ContextTypes::ChannelReadContext &ctx) = 0;
	virtual inline int get_channel_y_max(typename ContextTypes::ChannelReadContext &ctx) = 0;
	virtual inline int get_channel_y_min(typename ContextTypes::ChannelReadContext &ctx) = 0;

	/** Generated for complex type "x_list":
	 * <xs:complexType name="x_list">
	 *   
	 *   <xs:attribute name="index" type="xs:unsignedInt" use="required" />
	 *   <xs:attribute name="info" type="xs:int" use="required" />
	 * </xs:complexType>
	*/
	virtual inline unsigned int get_x_list_index(typename ContextTypes::XListReadContext &ctx) = 0;
	virtual inline int get_x_list_info(typename ContextTypes::XListReadContext &ctx) = 0;

	/** Generated for complex type "y_list":
	 * <xs:complexType name="y_list">
	 *   <xs:attribute name="index" type="xs:unsignedInt" use="required" />
	 *   <xs:attribute name="info" type="xs:int" use="required" />
	 * </xs:complexType>
	*/
	virtual inline unsigned int get_y_list_index(typename ContextTypes::YListReadContext &ctx) = 0;
	virtual inline int get_y_list_info(typename ContextTypes::YListReadContext &ctx) = 0;

	/** Generated for complex type "channels":
	 * <xs:complexType name="channels">
	 *   <xs:sequence>
	 *     <xs:element name="channel" type="channel" />
	 *     <xs:element name="x_list" type="x_list" maxOccurs="unbounded" />
	 *     <xs:element name="y_list" type="y_list" maxOccurs="unbounded" />
	 *   </xs:sequence>
	 * </xs:complexType>
	*/
	virtual inline typename ContextTypes::ChannelWriteContext init_channels_channel(typename ContextTypes::ChannelsWriteContext &ctx, int chan_width_max, int x_max, int x_min, int y_max, int y_min) = 0;
	virtual inline void finish_channels_channel(typename ContextTypes::ChannelWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::ChannelReadContext get_channels_channel(typename ContextTypes::ChannelsReadContext &ctx) = 0;
	virtual inline void preallocate_channels_x_list(typename ContextTypes::ChannelsWriteContext &ctx, size_t size) = 0;
	virtual inline typename ContextTypes::XListWriteContext add_channels_x_list(typename ContextTypes::ChannelsWriteContext &ctx, unsigned int index, int info) = 0;
	virtual inline void finish_channels_x_list(typename ContextTypes::XListWriteContext &ctx) = 0;
	virtual inline size_t num_channels_x_list(typename ContextTypes::ChannelsReadContext &ctx) = 0;
	virtual inline typename ContextTypes::XListReadContext get_channels_x_list(int n, typename ContextTypes::ChannelsReadContext &ctx) = 0;
	virtual inline void preallocate_channels_y_list(typename ContextTypes::ChannelsWriteContext &ctx, size_t size) = 0;
	virtual inline typename ContextTypes::YListWriteContext add_channels_y_list(typename ContextTypes::ChannelsWriteContext &ctx, unsigned int index, int info) = 0;
	virtual inline void finish_channels_y_list(typename ContextTypes::YListWriteContext &ctx) = 0;
	virtual inline size_t num_channels_y_list(typename ContextTypes::ChannelsReadContext &ctx) = 0;
	virtual inline typename ContextTypes::YListReadContext get_channels_y_list(int n, typename ContextTypes::ChannelsReadContext &ctx) = 0;

	/** Generated for complex type "timing":
	 * <xs:complexType name="timing">
	 *   
	 *   <xs:attribute name="R" type="xs:float" />
	 *   <xs:attribute name="Cin" type="xs:float" />
	 *   <xs:attribute name="Cinternal" type="xs:float" />
	 *   <xs:attribute name="Cout" type="xs:float" />
	 *   <xs:attribute name="Tdel" type="xs:float" />
	 * </xs:complexType>
	*/
	virtual inline float get_timing_Cin(typename ContextTypes::TimingReadContext &ctx) = 0;
	virtual inline void set_timing_Cin(float Cin, typename ContextTypes::TimingWriteContext &ctx) = 0;
	virtual inline float get_timing_Cinternal(typename ContextTypes::TimingReadContext &ctx) = 0;
	virtual inline void set_timing_Cinternal(float Cinternal, typename ContextTypes::TimingWriteContext &ctx) = 0;
	virtual inline float get_timing_Cout(typename ContextTypes::TimingReadContext &ctx) = 0;
	virtual inline void set_timing_Cout(float Cout, typename ContextTypes::TimingWriteContext &ctx) = 0;
	virtual inline float get_timing_R(typename ContextTypes::TimingReadContext &ctx) = 0;
	virtual inline void set_timing_R(float R, typename ContextTypes::TimingWriteContext &ctx) = 0;
	virtual inline float get_timing_Tdel(typename ContextTypes::TimingReadContext &ctx) = 0;
	virtual inline void set_timing_Tdel(float Tdel, typename ContextTypes::TimingWriteContext &ctx) = 0;

	/** Generated for complex type "sizing":
	 * <xs:complexType name="sizing">
	 *   <xs:attribute name="mux_trans_size" type="xs:float" use="required" />
	 *   <xs:attribute name="buf_size" type="xs:float" use="required" />
	 * </xs:complexType>
	*/
	virtual inline float get_sizing_buf_size(typename ContextTypes::SizingReadContext &ctx) = 0;
	virtual inline float get_sizing_mux_trans_size(typename ContextTypes::SizingReadContext &ctx) = 0;

	/** Generated for complex type "switch":
	 * <xs:complexType name="switch">
	 *   <xs:all>
	 *     <xs:element name="timing" type="timing" minOccurs="0" />
	 *     <xs:element name="sizing" type="sizing" />
	 *   </xs:all>
	 *   <xs:attribute name="id" type="xs:int" use="required" />
	 *   
	 *   <xs:attribute name="name" type="xs:string" use="required" />
	 *   
	 *   <xs:attribute name="type" type="switch_type" />
	 * </xs:complexType>
	*/
	virtual inline int get_switch_id(typename ContextTypes::SwitchReadContext &ctx) = 0;
	virtual inline const char * get_switch_name(typename ContextTypes::SwitchReadContext &ctx) = 0;
	virtual inline void set_switch_name(const char * name, typename ContextTypes::SwitchWriteContext &ctx) = 0;
	virtual inline enum_switch_type get_switch_type(typename ContextTypes::SwitchReadContext &ctx) = 0;
	virtual inline void set_switch_type(enum_switch_type type, typename ContextTypes::SwitchWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::TimingWriteContext init_switch_timing(typename ContextTypes::SwitchWriteContext &ctx) = 0;
	virtual inline void finish_switch_timing(typename ContextTypes::TimingWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::TimingReadContext get_switch_timing(typename ContextTypes::SwitchReadContext &ctx) = 0;
	virtual inline bool has_switch_timing(typename ContextTypes::SwitchReadContext &ctx) = 0;
	virtual inline typename ContextTypes::SizingWriteContext init_switch_sizing(typename ContextTypes::SwitchWriteContext &ctx, float buf_size, float mux_trans_size) = 0;
	virtual inline void finish_switch_sizing(typename ContextTypes::SizingWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::SizingReadContext get_switch_sizing(typename ContextTypes::SwitchReadContext &ctx) = 0;

	/** Generated for complex type "switches":
	 * <xs:complexType name="switches">
	 *   <xs:sequence>
	 *     <xs:element name="switch" type="switch" maxOccurs="unbounded" />
	 *   </xs:sequence>
	 * </xs:complexType>
	*/
	virtual inline void preallocate_switches_switch(typename ContextTypes::SwitchesWriteContext &ctx, size_t size) = 0;
	virtual inline typename ContextTypes::SwitchWriteContext add_switches_switch(typename ContextTypes::SwitchesWriteContext &ctx, int id) = 0;
	virtual inline void finish_switches_switch(typename ContextTypes::SwitchWriteContext &ctx) = 0;
	virtual inline size_t num_switches_switch(typename ContextTypes::SwitchesReadContext &ctx) = 0;
	virtual inline typename ContextTypes::SwitchReadContext get_switches_switch(int n, typename ContextTypes::SwitchesReadContext &ctx) = 0;

	/** Generated for complex type "segment_timing":
	 * <xs:complexType name="segment_timing">
	 *   <xs:attribute name="R_per_meter" type="xs:float" />
	 *   <xs:attribute name="C_per_meter" type="xs:float" />
	 * </xs:complexType>
	*/
	virtual inline float get_segment_timing_C_per_meter(typename ContextTypes::SegmentTimingReadContext &ctx) = 0;
	virtual inline void set_segment_timing_C_per_meter(float C_per_meter, typename ContextTypes::SegmentTimingWriteContext &ctx) = 0;
	virtual inline float get_segment_timing_R_per_meter(typename ContextTypes::SegmentTimingReadContext &ctx) = 0;
	virtual inline void set_segment_timing_R_per_meter(float R_per_meter, typename ContextTypes::SegmentTimingWriteContext &ctx) = 0;

	/** Generated for complex type "segment":
	 * <xs:complexType name="segment">
	 *   <xs:all>
	 *     <xs:element name="timing" type="segment_timing" minOccurs="0" />
	 *   </xs:all>
	 *   <xs:attribute name="id" type="xs:int" use="required" />
	 *   <xs:attribute name="name" type="xs:string" use="required" />
	 * </xs:complexType>
	*/
	virtual inline int get_segment_id(typename ContextTypes::SegmentReadContext &ctx) = 0;
	virtual inline const char * get_segment_name(typename ContextTypes::SegmentReadContext &ctx) = 0;
	virtual inline void set_segment_name(const char * name, typename ContextTypes::SegmentWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::SegmentTimingWriteContext init_segment_timing(typename ContextTypes::SegmentWriteContext &ctx) = 0;
	virtual inline void finish_segment_timing(typename ContextTypes::SegmentTimingWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::SegmentTimingReadContext get_segment_timing(typename ContextTypes::SegmentReadContext &ctx) = 0;
	virtual inline bool has_segment_timing(typename ContextTypes::SegmentReadContext &ctx) = 0;

	/** Generated for complex type "segments":
	 * <xs:complexType name="segments">
	 *   <xs:sequence>
	 *     <xs:element name="segment" type="segment" maxOccurs="unbounded" />
	 *   </xs:sequence>
	 * </xs:complexType>
	*/
	virtual inline void preallocate_segments_segment(typename ContextTypes::SegmentsWriteContext &ctx, size_t size) = 0;
	virtual inline typename ContextTypes::SegmentWriteContext add_segments_segment(typename ContextTypes::SegmentsWriteContext &ctx, int id) = 0;
	virtual inline void finish_segments_segment(typename ContextTypes::SegmentWriteContext &ctx) = 0;
	virtual inline size_t num_segments_segment(typename ContextTypes::SegmentsReadContext &ctx) = 0;
	virtual inline typename ContextTypes::SegmentReadContext get_segments_segment(int n, typename ContextTypes::SegmentsReadContext &ctx) = 0;

	/** Generated for complex type "pin":
	 * <xs:complexType name="pin">
	 *   <xs:simpleContent>
	 *     <xs:extension base="xs:string">
	 *       <xs:attribute name="ptc" type="xs:int" use="required" />
	 *     </xs:extension>
	 *   </xs:simpleContent>
	 * </xs:complexType>
	*/
	virtual inline int get_pin_ptc(typename ContextTypes::PinReadContext &ctx) = 0;
	virtual inline void set_pin_value(const char * value, typename ContextTypes::PinWriteContext &ctx) = 0;
	virtual inline const char * get_pin_value(typename ContextTypes::PinReadContext &ctx) = 0;

	/** Generated for complex type "pin_class":
	 * <xs:complexType name="pin_class">
	 *   <xs:sequence>
	 *     <xs:element name="pin" type="pin" maxOccurs="unbounded" />
	 *   </xs:sequence>
	 *   <xs:attribute name="type" type="pin_type" use="required" />
	 * </xs:complexType>
	*/
	virtual inline enum_pin_type get_pin_class_type(typename ContextTypes::PinClassReadContext &ctx) = 0;
	virtual inline void preallocate_pin_class_pin(typename ContextTypes::PinClassWriteContext &ctx, size_t size) = 0;
	virtual inline typename ContextTypes::PinWriteContext add_pin_class_pin(typename ContextTypes::PinClassWriteContext &ctx, int ptc) = 0;
	virtual inline void finish_pin_class_pin(typename ContextTypes::PinWriteContext &ctx) = 0;
	virtual inline size_t num_pin_class_pin(typename ContextTypes::PinClassReadContext &ctx) = 0;
	virtual inline typename ContextTypes::PinReadContext get_pin_class_pin(int n, typename ContextTypes::PinClassReadContext &ctx) = 0;

	/** Generated for complex type "block_type":
	 * <xs:complexType name="block_type">
	 *   <xs:sequence>
	 *     <xs:element name="pin_class" type="pin_class" minOccurs="0" maxOccurs="unbounded" />
	 *   </xs:sequence>
	 *   <xs:attribute name="id" type="xs:int" use="required" />
	 *   <xs:attribute name="name" type="xs:string" use="required" />
	 *   <xs:attribute name="width" type="xs:int" use="required" />
	 *   <xs:attribute name="height" type="xs:int" use="required" />
	 * </xs:complexType>
	*/
	virtual inline int get_block_type_height(typename ContextTypes::BlockTypeReadContext &ctx) = 0;
	virtual inline int get_block_type_id(typename ContextTypes::BlockTypeReadContext &ctx) = 0;
	virtual inline const char * get_block_type_name(typename ContextTypes::BlockTypeReadContext &ctx) = 0;
	virtual inline void set_block_type_name(const char * name, typename ContextTypes::BlockTypeWriteContext &ctx) = 0;
	virtual inline int get_block_type_width(typename ContextTypes::BlockTypeReadContext &ctx) = 0;
	virtual inline void preallocate_block_type_pin_class(typename ContextTypes::BlockTypeWriteContext &ctx, size_t size) = 0;
	virtual inline typename ContextTypes::PinClassWriteContext add_block_type_pin_class(typename ContextTypes::BlockTypeWriteContext &ctx, enum_pin_type type) = 0;
	virtual inline void finish_block_type_pin_class(typename ContextTypes::PinClassWriteContext &ctx) = 0;
	virtual inline size_t num_block_type_pin_class(typename ContextTypes::BlockTypeReadContext &ctx) = 0;
	virtual inline typename ContextTypes::PinClassReadContext get_block_type_pin_class(int n, typename ContextTypes::BlockTypeReadContext &ctx) = 0;

	/** Generated for complex type "block_types":
	 * <xs:complexType name="block_types">
	 *   <xs:sequence>
	 *     <xs:element name="block_type" type="block_type" maxOccurs="unbounded" />
	 *   </xs:sequence>
	 * </xs:complexType>
	*/
	virtual inline void preallocate_block_types_block_type(typename ContextTypes::BlockTypesWriteContext &ctx, size_t size) = 0;
	virtual inline typename ContextTypes::BlockTypeWriteContext add_block_types_block_type(typename ContextTypes::BlockTypesWriteContext &ctx, int height, int id, int width) = 0;
	virtual inline void finish_block_types_block_type(typename ContextTypes::BlockTypeWriteContext &ctx) = 0;
	virtual inline size_t num_block_types_block_type(typename ContextTypes::BlockTypesReadContext &ctx) = 0;
	virtual inline typename ContextTypes::BlockTypeReadContext get_block_types_block_type(int n, typename ContextTypes::BlockTypesReadContext &ctx) = 0;

	/** Generated for complex type "grid_loc":
	 * <xs:complexType name="grid_loc">
	 *   <xs:attribute name="x" type="xs:int" use="required" />
	 *   <xs:attribute name="y" type="xs:int" use="required" />
	 *   <xs:attribute name="layer" type="xs:int" use=:"required" />
	 *   <xs:attribute name="block_type_id" type="xs:int" use="required" />
	 *   <xs:attribute name="width_offset" type="xs:int" use="required" />
	 *   <xs:attribute name="height_offset" type="xs:int" use="required" />
	 * </xs:complexType>
	*/
	virtual inline int get_grid_loc_block_type_id(typename ContextTypes::GridLocReadContext &ctx) = 0;
	virtual inline int get_grid_loc_height_offset(typename ContextTypes::GridLocReadContext &ctx) = 0;
	virtual inline int get_grid_loc_width_offset(typename ContextTypes::GridLocReadContext &ctx) = 0;
	virtual inline int get_grid_loc_x(typename ContextTypes::GridLocReadContext &ctx) = 0;
	virtual inline int get_grid_loc_y(typename ContextTypes::GridLocReadContext &ctx) = 0;
	virtual inline int get_grid_loc_layer(typename ContextTypes::GridLocReadContext &ctx) =0;

	/** Generated for complex type "grid_locs":
	 * <xs:complexType name="grid_locs">
	 *   <xs:sequence>
	 *     <xs:element name="grid_loc" type="grid_loc" maxOccurs="unbounded" />
	 *   </xs:sequence>
	 * </xs:complexType>
	*/
	virtual inline void preallocate_grid_locs_grid_loc(typename ContextTypes::GridLocsWriteContext &ctx, size_t size) = 0;
	virtual inline typename ContextTypes::GridLocWriteContext add_grid_locs_grid_loc(typename ContextTypes::GridLocsWriteContext &ctx, int block_type_id, int height_offset, int width_offset, int x, int y) = 0;
	virtual inline void finish_grid_locs_grid_loc(typename ContextTypes::GridLocWriteContext &ctx) = 0;
	virtual inline size_t num_grid_locs_grid_loc(typename ContextTypes::GridLocsReadContext &ctx) = 0;
	virtual inline typename ContextTypes::GridLocReadContext get_grid_locs_grid_loc(int n, typename ContextTypes::GridLocsReadContext &ctx) = 0;

	/** Generated for complex type "node_loc":
	 * <xs:complexType name="node_loc">
	 *   <xs:attribute name="layer" type="xs:int" use="required" />
	 *   <xs:attribute name="xlow" type="xs:int" use="required" />
	 *   <xs:attribute name="ylow" type="xs:int" use="required" />
	 *   <xs:attribute name="xhigh" type="xs:int" use="required" />
	 *   <xs:attribute name="yhigh" type="xs:int" use="required" />
	 *   <xs:attribute name="side" type="loc_side" />
	 *   <xs:attribute name="ptc" type="xs:int" use="required" />
	 * </xs:complexType>
	*/
	virtual inline int get_node_loc_layer(typename ContextTypes::NodeLocReadContext &ctx) = 0;
	virtual inline int get_node_loc_ptc(typename ContextTypes::NodeLocReadContext &ctx) = 0;
	virtual inline enum_loc_side get_node_loc_side(typename ContextTypes::NodeLocReadContext &ctx) = 0;
	virtual inline void set_node_loc_side(enum_loc_side side, typename ContextTypes::NodeLocWriteContext &ctx) = 0;
	virtual inline int get_node_loc_xhigh(typename ContextTypes::NodeLocReadContext &ctx) = 0;
	virtual inline int get_node_loc_xlow(typename ContextTypes::NodeLocReadContext &ctx) = 0;
	virtual inline int get_node_loc_yhigh(typename ContextTypes::NodeLocReadContext &ctx) = 0;
	virtual inline int get_node_loc_ylow(typename ContextTypes::NodeLocReadContext &ctx) = 0;

	/** Generated for complex type "node_timing":
	 * <xs:complexType name="node_timing">
	 *   <xs:attribute name="R" type="xs:float" use="required" />
	 *   <xs:attribute name="C" type="xs:float" use="required" />
	 * </xs:complexType>
	*/
	virtual inline float get_node_timing_C(typename ContextTypes::NodeTimingReadContext &ctx) = 0;
	virtual inline float get_node_timing_R(typename ContextTypes::NodeTimingReadContext &ctx) = 0;

	/** Generated for complex type "node_segment":
	 * <xs:complexType name="node_segment">
	 *   <xs:attribute name="segment_id" type="xs:int" use="required" />
	 * </xs:complexType>
	*/
	virtual inline int get_node_segment_segment_id(typename ContextTypes::NodeSegmentReadContext &ctx) = 0;

	/** Generated for complex type "meta":
	 * <xs:complexType name="meta">
	 *   <xs:simpleContent>
	 *     <xs:extension base="xs:string">
	 *       <xs:attribute name="name" type="xs:string" use="required" />
	 *     </xs:extension>
	 *   </xs:simpleContent>
	 * </xs:complexType>
	*/
	virtual inline const char * get_meta_name(typename ContextTypes::MetaReadContext &ctx) = 0;
	virtual inline void set_meta_name(const char * name, typename ContextTypes::MetaWriteContext &ctx) = 0;
	virtual inline void set_meta_value(const char * value, typename ContextTypes::MetaWriteContext &ctx) = 0;
	virtual inline const char * get_meta_value(typename ContextTypes::MetaReadContext &ctx) = 0;

	/** Generated for complex type "metadata":
	 * <xs:complexType name="metadata">
	 *   <xs:sequence>
	 *     <xs:element name="meta" type="meta" maxOccurs="unbounded" />
	 *   </xs:sequence>
	 * </xs:complexType>
	*/
	virtual inline void preallocate_metadata_meta(typename ContextTypes::MetadataWriteContext &ctx, size_t size) = 0;
	virtual inline typename ContextTypes::MetaWriteContext add_metadata_meta(typename ContextTypes::MetadataWriteContext &ctx) = 0;
	virtual inline void finish_metadata_meta(typename ContextTypes::MetaWriteContext &ctx) = 0;
	virtual inline size_t num_metadata_meta(typename ContextTypes::MetadataReadContext &ctx) = 0;
	virtual inline typename ContextTypes::MetaReadContext get_metadata_meta(int n, typename ContextTypes::MetadataReadContext &ctx) = 0;

	/** Generated for complex type "node":
	 * <xs:complexType name="node">
	 *   <xs:all>
	 *     <xs:element name="loc" type="node_loc" />
	 *     <xs:element name="timing" type="node_timing" minOccurs="0" />
	 *     <xs:element name="segment" type="node_segment" minOccurs="0" />
	 *     <xs:element name="metadata" type="metadata" minOccurs="0" />
	 *   </xs:all>
	 *   <xs:attribute name="id" type="xs:unsignedInt" use="required" />
	 *   <xs:attribute name="type" type="node_type" use="required" />
	 *   <xs:attribute name="direction" type="node_direction" />
	 *   <xs:attribute name="capacity" type="xs:unsignedInt" use="required" />
	 * </xs:complexType>
	*/
	virtual inline unsigned int get_node_capacity(typename ContextTypes::NodeReadContext &ctx) = 0;
	virtual inline enum_node_direction get_node_direction(typename ContextTypes::NodeReadContext &ctx) = 0;
	virtual inline void set_node_direction(enum_node_direction direction, typename ContextTypes::NodeWriteContext &ctx) = 0;
	virtual inline unsigned int get_node_id(typename ContextTypes::NodeReadContext &ctx) = 0;
	virtual inline enum_node_type get_node_type(typename ContextTypes::NodeReadContext &ctx) = 0;
	virtual inline typename ContextTypes::NodeLocWriteContext init_node_loc(typename ContextTypes::NodeWriteContext &ctx, int layer, int ptc, int xhigh, int xlow, int yhigh, int ylow) = 0;
	virtual inline void finish_node_loc(typename ContextTypes::NodeLocWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::NodeLocReadContext get_node_loc(typename ContextTypes::NodeReadContext &ctx) = 0;
	virtual inline typename ContextTypes::NodeTimingWriteContext init_node_timing(typename ContextTypes::NodeWriteContext &ctx, float C, float R) = 0;
	virtual inline void finish_node_timing(typename ContextTypes::NodeTimingWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::NodeTimingReadContext get_node_timing(typename ContextTypes::NodeReadContext &ctx) = 0;
	virtual inline bool has_node_timing(typename ContextTypes::NodeReadContext &ctx) = 0;
	virtual inline typename ContextTypes::NodeSegmentWriteContext init_node_segment(typename ContextTypes::NodeWriteContext &ctx, int segment_id) = 0;
	virtual inline void finish_node_segment(typename ContextTypes::NodeSegmentWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::NodeSegmentReadContext get_node_segment(typename ContextTypes::NodeReadContext &ctx) = 0;
	virtual inline bool has_node_segment(typename ContextTypes::NodeReadContext &ctx) = 0;
	virtual inline typename ContextTypes::MetadataWriteContext init_node_metadata(typename ContextTypes::NodeWriteContext &ctx) = 0;
	virtual inline void finish_node_metadata(typename ContextTypes::MetadataWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::MetadataReadContext get_node_metadata(typename ContextTypes::NodeReadContext &ctx) = 0;
	virtual inline bool has_node_metadata(typename ContextTypes::NodeReadContext &ctx) = 0;

	/** Generated for complex type "rr_nodes":
	 * <xs:complexType name="rr_nodes">
	 *   <xs:choice maxOccurs="unbounded">
	 *     <xs:element name="node" type="node" />
	 *   </xs:choice>
	 * </xs:complexType>
	*/
	virtual inline void preallocate_rr_nodes_node(typename ContextTypes::RrNodesWriteContext &ctx, size_t size) = 0;
	virtual inline typename ContextTypes::NodeWriteContext add_rr_nodes_node(typename ContextTypes::RrNodesWriteContext &ctx, unsigned int capacity, unsigned int id, enum_node_type type) = 0;
	virtual inline void finish_rr_nodes_node(typename ContextTypes::NodeWriteContext &ctx) = 0;
	virtual inline size_t num_rr_nodes_node(typename ContextTypes::RrNodesReadContext &ctx) = 0;
	virtual inline typename ContextTypes::NodeReadContext get_rr_nodes_node(int n, typename ContextTypes::RrNodesReadContext &ctx) = 0;

	/** Generated for complex type "edge":
	 * <xs:complexType name="edge">
	 *   <xs:all>
	 *     <xs:element name="metadata" type="metadata" minOccurs="0" />
	 *   </xs:all>
	 *   <xs:attribute name="src_node" type="xs:unsignedInt" use="required" />
	 *   <xs:attribute name="sink_node" type="xs:unsignedInt" use="required" />
	 *   <xs:attribute name="switch_id" type="xs:unsignedInt" use="required" />
	 * </xs:complexType>
	*/
	virtual inline unsigned int get_edge_sink_node(typename ContextTypes::EdgeReadContext &ctx) = 0;
	virtual inline unsigned int get_edge_src_node(typename ContextTypes::EdgeReadContext &ctx) = 0;
	virtual inline unsigned int get_edge_switch_id(typename ContextTypes::EdgeReadContext &ctx) = 0;
	virtual inline typename ContextTypes::MetadataWriteContext init_edge_metadata(typename ContextTypes::EdgeWriteContext &ctx) = 0;
	virtual inline void finish_edge_metadata(typename ContextTypes::MetadataWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::MetadataReadContext get_edge_metadata(typename ContextTypes::EdgeReadContext &ctx) = 0;
	virtual inline bool has_edge_metadata(typename ContextTypes::EdgeReadContext &ctx) = 0;

	/** Generated for complex type "rr_edges":
	 * <xs:complexType name="rr_edges">
	 *   <xs:choice maxOccurs="unbounded">
	 *     <xs:element name="edge" type="edge" />
	 *   </xs:choice>
	 * </xs:complexType>
	*/
	virtual inline void preallocate_rr_edges_edge(typename ContextTypes::RrEdgesWriteContext &ctx, size_t size) = 0;
	virtual inline typename ContextTypes::EdgeWriteContext add_rr_edges_edge(typename ContextTypes::RrEdgesWriteContext &ctx, unsigned int sink_node, unsigned int src_node, unsigned int switch_id) = 0;
	virtual inline void finish_rr_edges_edge(typename ContextTypes::EdgeWriteContext &ctx) = 0;
	virtual inline size_t num_rr_edges_edge(typename ContextTypes::RrEdgesReadContext &ctx) = 0;
	virtual inline typename ContextTypes::EdgeReadContext get_rr_edges_edge(int n, typename ContextTypes::RrEdgesReadContext &ctx) = 0;

	/** Generated for complex type "rr_graph":
	 * <xs:complexType xmlns:xs="http://www.w3.org/2001/XMLSchema">
	 *     <xs:all>
	 *       <xs:element name="channels" type="channels" />
	 *       <xs:element name="switches" type="switches" />
	 *       <xs:element name="segments" type="segments" />
	 *       <xs:element name="block_types" type="block_types" />
	 *       <xs:element name="grid" type="grid_locs" />
	 *       <xs:element name="rr_nodes" type="rr_nodes" />
	 *       <xs:element name="rr_edges" type="rr_edges" />
	 *     </xs:all>
	 *     <xs:attribute name="tool_name" type="xs:string" />
	 *     <xs:attribute name="tool_version" type="xs:string" />
	 *     <xs:attribute name="tool_comment" type="xs:string" />
	 *   </xs:complexType>
	*/
	virtual inline const char * get_rr_graph_tool_comment(typename ContextTypes::RrGraphReadContext &ctx) = 0;
	virtual inline void set_rr_graph_tool_comment(const char * tool_comment, typename ContextTypes::RrGraphWriteContext &ctx) = 0;
	virtual inline const char * get_rr_graph_tool_name(typename ContextTypes::RrGraphReadContext &ctx) = 0;
	virtual inline void set_rr_graph_tool_name(const char * tool_name, typename ContextTypes::RrGraphWriteContext &ctx) = 0;
	virtual inline const char * get_rr_graph_tool_version(typename ContextTypes::RrGraphReadContext &ctx) = 0;
	virtual inline void set_rr_graph_tool_version(const char * tool_version, typename ContextTypes::RrGraphWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::ChannelsWriteContext init_rr_graph_channels(typename ContextTypes::RrGraphWriteContext &ctx) = 0;
	virtual inline void finish_rr_graph_channels(typename ContextTypes::ChannelsWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::ChannelsReadContext get_rr_graph_channels(typename ContextTypes::RrGraphReadContext &ctx) = 0;
	virtual inline typename ContextTypes::SwitchesWriteContext init_rr_graph_switches(typename ContextTypes::RrGraphWriteContext &ctx) = 0;
	virtual inline void finish_rr_graph_switches(typename ContextTypes::SwitchesWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::SwitchesReadContext get_rr_graph_switches(typename ContextTypes::RrGraphReadContext &ctx) = 0;
	virtual inline typename ContextTypes::SegmentsWriteContext init_rr_graph_segments(typename ContextTypes::RrGraphWriteContext &ctx) = 0;
	virtual inline void finish_rr_graph_segments(typename ContextTypes::SegmentsWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::SegmentsReadContext get_rr_graph_segments(typename ContextTypes::RrGraphReadContext &ctx) = 0;
	virtual inline typename ContextTypes::BlockTypesWriteContext init_rr_graph_block_types(typename ContextTypes::RrGraphWriteContext &ctx) = 0;
	virtual inline void finish_rr_graph_block_types(typename ContextTypes::BlockTypesWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::BlockTypesReadContext get_rr_graph_block_types(typename ContextTypes::RrGraphReadContext &ctx) = 0;
	virtual inline typename ContextTypes::GridLocsWriteContext init_rr_graph_grid(typename ContextTypes::RrGraphWriteContext &ctx) = 0;
	virtual inline void finish_rr_graph_grid(typename ContextTypes::GridLocsWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::GridLocsReadContext get_rr_graph_grid(typename ContextTypes::RrGraphReadContext &ctx) = 0;
	virtual inline typename ContextTypes::RrNodesWriteContext init_rr_graph_rr_nodes(typename ContextTypes::RrGraphWriteContext &ctx) = 0;
	virtual inline void finish_rr_graph_rr_nodes(typename ContextTypes::RrNodesWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::RrNodesReadContext get_rr_graph_rr_nodes(typename ContextTypes::RrGraphReadContext &ctx) = 0;
	virtual inline typename ContextTypes::RrEdgesWriteContext init_rr_graph_rr_edges(typename ContextTypes::RrGraphWriteContext &ctx) = 0;
	virtual inline void finish_rr_graph_rr_edges(typename ContextTypes::RrEdgesWriteContext &ctx) = 0;
	virtual inline typename ContextTypes::RrEdgesReadContext get_rr_graph_rr_edges(typename ContextTypes::RrGraphReadContext &ctx) = 0;
};

} /* namespace uxsd */
