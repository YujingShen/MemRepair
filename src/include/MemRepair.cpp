#include "MemRepair.h"

namespace sjtu {

	MemRepair& MemRepair::read_setting(const string& setting_file_path) {
		fstream setting_file(setting_file_path, std::ios::in);

		assert(setting_file);
		setting_file
			>> w >> h
			>> w_segs >> h_segs
			>> w_nums >> h_nums
			>> share_cost;
		assert(w_segs < w && h_segs < h);

		setting_file.close();
		return build_flow_graph();
	}

	MemRepair& MemRepair::read_mcnts(const string& mcnt_file_path) {
		fstream mcnt_file(mcnt_file_path, std::ios::in);

		assert(mcnt_file);
		int r, c;
		vector<pair<int, int>> mcnts;
		while (mcnt_file >> r >> c) {
			mcnts.push_back(std::make_pair(r, c));
		}
		mcnt_file.close();
		return increment_mcnts(mcnts);
	}

	MemRepair& MemRepair::build_flow_graph() {
		non_imp_warning();
		return *this;
	}

	MemRepair& MemRepair::increment_mcnts(const vector<pair<int, int>>& mcnts) {
		non_imp_warning();
		return *this;
	}

	MemRepair& MemRepair::repair() {
		non_imp_warning();
		return *this;
	}

	MemRepair& MemRepair::report_allocation() {
		non_imp_warning();
		return *this;
	}

	void MemRepair::non_imp_warning() {
		cout << "WARNING: not implemented yet" << endl;
	}

	
	MemRepair& MemRepairBaseline::build_flow_graph() {
		int rs = h / h_segs;
		int cs = w / w_segs;

		for (int r = 0; r < h; r += rs) {
			for (int c = 0; c < w; c += cs) {

			}
		}

		return *this;
	}

	MemRepair& MemRepairBaseline::repair() {
		return *this;
	}

	MemRepair& MemRepairBaseline::increment_mcnts(const vector<pair<int, int>>& mcnts) {
		return *this;
	}

	MemRepair& MemRepairBaseline::report_allocation() {
		return *this;
	}
}