#pragma once
#include <string>
#include <utility>

#include "Graph.h"


namespace sjtu {
	using std::string;
	using std::pair;

	class MemRepair
	{
	public:
		void read_setting(string setting_file_path);

		void read_mcnts(string mcnt_file_path);

		void increment_mcnts(const vector<pair>& mcnts);

		void report_allocation();
	
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
	public:
		MemRepairBaseline();
		virtual ~MemRepairBaseline();
	private:

	};
}