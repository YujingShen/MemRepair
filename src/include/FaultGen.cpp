#include "FaultGen.h"
#include <cassert>
#include <iostream>

namespace sjtu {


	void CNFET_faultgen::load_distr(const string& distr_file_path) {
		
		fstream distr_file(distr_file_path, std::ios::in);
		assert(distr_file);

		string distr_raw;
		for (int i = 0; i < 6; ++i) {
			distr_file >> distr_raw;

			int j = 0;
			for (size_t k = 0; k < distr_raw.size(); ++k) {
				if (distr_raw[k] >= '0' && distr_raw[k] <= '9') {
					int num = distr_raw[k] - '0';
					while (
						k + 1 < distr_raw.size()
						&& distr_raw[k + 1] >= '0'
						&& distr_raw[k + 1] <= '9') {
	
						num = num * 10 + (distr_raw[++k] - '0');
					}

					if (candidate.size() < ++j) {
						candidate.push_back({ 0, 0, 0, 0, 0, 0 });
					}
					candidate[j - 1][i] = num;
				}  // get num			
			}  // scan for num
		}  // for 6 cases
		candi_itr = candidate.begin();
	}

	vector<int> CNFET_faultgen::next_distr() {
		if (candi_itr == candidate.end()) {
			candi_itr = candidate.begin();
		}
		return *(candi_itr++);
	}

	vector<pair<int, int>> CNFET_faultgen::gen_fault_from_distr(
		const vector<int>& distr, int row, int col) {

		vector<pair<int, int>> fault;

		int n_single_cell = 1 * distr[0];
		int n_double_cell = 1 * distr[1];
		int n_wordline = 1 * distr[2];
		int n_double_wordline = 1 * distr[3];
		int n_bitline = 1 * distr[4];
		int n_double_bitline = 1 * distr[5];

		int nm_line_f;

		for (int f = 0; f < n_single_cell; f++) {
			int r = abs(rand()) % row;
			int c = abs(rand()) % col;
			fault.push_back(pair<int, int>(r, c));
		}
		for (int f = 0; f < n_double_cell; f += 1) {
			int r = abs(rand()) % row;
			int c = abs(rand()) % (col - 1);
			fault.push_back(pair<int, int>(r, c));
			fault.push_back(pair<int, int>(r, c + 1));
		}
		for (int f = 0; f < n_wordline; f += 1) {
			int r = abs(rand()) % row;
			nm_line_f = 2;
			for (int i = 0; i < nm_line_f; i++) {
				int c = abs(rand()) % col;
				fault.push_back(pair<int, int>(r, c));
			}
		}
		for (int f = 0; f < n_double_wordline; f += 1) {
			int r = abs(rand()) % (row - 1);
			nm_line_f = 2;
			for (int i = 0; i < nm_line_f; i++) {
				int c = abs(rand()) % col;
				fault.push_back(pair<int, int>(r, c));
				c = abs(rand()) % col;
				fault.push_back(pair<int, int>(r + 1, c));
			}
		}
		for (int f = 0; f < n_bitline; f += 1) {
			int c = abs(rand()) % col;
			nm_line_f = 2;
			for (int i = 0; i<nm_line_f; i++) {
				int r = abs(rand()) % row;
				fault.push_back(pair<int, int>(r, c));
			}
		}
		for (int f = 0; f < n_double_bitline; f += 1) {
			int c = abs(rand()) % (col - 1);
			nm_line_f = 2;
			for (int i = 0; i<nm_line_f; i++) {
				int r = abs(rand()) % row;
				fault.push_back(pair<int, int>(r, c));
				r = abs(rand()) % row;
				fault.push_back(pair<int, int>(r, c + 1));
			}
		}
		return fault;
	}


	size_t CNFET_faultgen::size() {
		return candidate.size();
	}
}