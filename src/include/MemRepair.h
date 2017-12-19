#pragma once
#include <string>
#include <utility>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <cassert>
#include <cstddef>  // NULL

#include "Graph.h"


namespace sjtu {
	using std::vector;
	using std::string;
	using std::pair;
	using std::cout;
	using std::endl;
	using std::fstream;
	

	class MemRepair
	{
	public:
		virtual MemRepair& read_setting(const string& setting_file_path);

		virtual MemRepair& read_mcnts(const string& mcnt_file_path);

		virtual MemRepair& increment_mcnts(const vector<pair<int, int>>& mcnts);

		virtual MemRepair& build_flow_graph();

		virtual MemRepair& repair();

		virtual MemRepair& report_allocation();

	private:
		void non_imp_warning();

	public:
		MemRepair() = default;
		virtual ~MemRepair() = default;

	protected:
		int w, h;
		int w_segs, h_segs;
		int w_nums, h_nums;
		float share_cost;   // cost in sharing between adjacent sparing bits
	};

	class MemRepairBaseline: public MemRepair
	{
		//using std::map;
		//using std::pair;
	public:
		virtual MemRepair& increment_mcnts(const vector<pair<int, int>>& mcnts);

		virtual MemRepair& build_flow_graph();

		virtual MemRepair& repair();

		virtual MemRepair& report_allocation();
	

	public:
		MemRepairBaseline() = default;
		virtual ~MemRepairBaseline() = default;

	protected:
		FlowGraph mem_network;
		vector<Graph> bipartite;
	};
}