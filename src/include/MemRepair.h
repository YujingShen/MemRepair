#pragma once
#include <string>
#include <utility>
#include <iostream>
#include <map>
#include <vector>

#include "Graph.h"


namespace sjtu {
	
	class MemRepair
	{
		using std::string;
		using std::cout;
		using std::endl;

	public:
		virtual MemRepair& read_setting(string setting_file_path);

		virtual MemRepair& read_mcnts(string mcnt_file_path);

		virtual MemRepair& increment_mcnts(const vector<pair>& mcnts);

		virtual MemRepair& report_allocation();
	
	public:
		MemRepair() = default;
		virtual ~MemRepair() = default;
	
	protected:
		int w, h;
		int w_segs, h_segs;
		int w_nums, h_nums;
	};

	class MemRepairBaseline: public MemRepair
	{
		//using std::map;
		//using std::pair;
		using std::vector

	public:
		MemRepairBaseline();
		virtual ~MemRepairBaseline();
	private:
		Graph mem_network;
		vector<Graph> bipartite; 
	};
}