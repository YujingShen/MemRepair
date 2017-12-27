#pragma once
#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <cassert>
#include <tuple>
#include <cstddef>  // NULL

#include "Graph.h"
#include "FaultGen.h"


namespace sjtu {
	using std::vector;
	using std::string;
	using std::pair;
	using std::cout;
	using std::endl;
	using std::fstream;
	using std::tuple;
	using std::set;
	using std::map;

	class MemRepair
	{
	public:
		virtual void read_setting(const string& setting_file_path);

		virtual void read_mcnts(const string& mcnt_file_path);

		virtual void increment_mcnts(const vector<pair<int, int>>& mcnts);

		virtual void build_flow_graph();

		virtual bool repair();

		virtual void report_allocation();

	private:
		void non_imp_warning();

	public:
		MemRepair() = default;
		virtual ~MemRepair() = default;

	protected:
		int cols, rows;
		int col_segs, r_segs;  // segment numbers
		int c_nums, r_nums;  // sparing bit line number
		float share_cost;  // cost in sharing between adjacent sparing bits
	};

	class MemRepairBaseline: public MemRepair
	{

	public:
		virtual void increment_mcnts(const vector<pair<int, int>>& mcnts);

		virtual void build_flow_graph();

		virtual void rebuild_flow_graph();

		virtual bool repair();

		virtual void report_allocation();

		// global i, j -> block_id, local i, j
		tuple<int, int, int> gloabl_to_local(int gi, int gj);

		int total_failures();
	public:
		MemRepairBaseline();
		virtual ~MemRepairBaseline();

	protected:
		FlowGraph* mem_network;
		vector<BipartiteGraph*> bi_block;
		void clear();

	protected:
		vector<Graph::Vertex> spare_r, spare_c;
		int rs, cs;
		int INF_CAP;

		vector<Graph::Vertex> v_block_x, v_block_y;  // vertex in mem net w.r.t. bi block
	protected:
		set<pair<int, int>> failure_map;
		int current_flow;
	};
}