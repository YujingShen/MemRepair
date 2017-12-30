#include "MemRepair.h"
//#define DEBUG

namespace sjtu {

	void MemRepair::read_setting(const string& setting_file_path) {
		fstream setting_file(setting_file_path, std::ios::in);

		assert(setting_file);
		setting_file
			>> cols >> rows
			>> c_segs >> r_segs
			>> c_nums >> r_nums
			>> share_cost;
		assert(c_segs <= cols && r_segs <= rows);

		setting_file.close();
		build_flow_graph();
	}

	void MemRepair::read_mcnts(const string& mcnt_file_path) {
		fstream mcnt_file(mcnt_file_path, std::ios::in);

		assert(mcnt_file);
		int r, c;
		vector<pair<int, int>> mcnts;
		while (mcnt_file >> r >> c) {
			mcnts.push_back(std::make_pair(r, c));
		}
		mcnt_file.close();
		increment_mcnts(mcnts);
	}

	void MemRepair::build_flow_graph() {
		non_imp_warning();
	}

	void MemRepair::increment_mcnts(const vector<pair<int, int>>& mcnts) {
		non_imp_warning();
	}

	bool MemRepair::repair() {
		non_imp_warning();
	}

	void MemRepair::report_allocation() {
		non_imp_warning();
	}

	void MemRepair::non_imp_warning() {
		cout << "WARNING: not implemented yet" << endl;
	}

	int MemRepair::col_num() {
		return cols;
	}
	int MemRepair::row_num() {
		return rows;
	}


	MemRepairBaseline::MemRepairBaseline() {
		mem_network = new FlowGraph();
	}

	MemRepairBaseline::~MemRepairBaseline() {
		clear();
	}

	void MemRepairBaseline::clear() {
		delete mem_network;
		mem_network = NULL;

		for (auto&& b : bi_block) {
			delete b;
		}
		
		bi_block.clear();
		spare_r.clear();
		spare_c.clear();
		v_block_x.clear();
		v_block_y.clear();
		failure_map.clear();

		rs = cs = current_flow = INF_CAP = 0;
	}

	void MemRepairBaseline::rebuild_flow_graph() {
		clear();
		mem_network = new FlowGraph();
		build_flow_graph();
	}
	
	void MemRepairBaseline::build_flow_graph() {
		
		rs = rows / r_segs;
		cs = cols / c_segs;
		INF_CAP = rs * cs * 4;

		auto st = mem_network->st;
		auto ed = mem_network->ed;

		int r, c;

		for (r = 0; r < r_segs; ++r) {
			auto v = mem_network->new_vertex();
			if (!spare_r.empty()) {
				auto u = spare_r.back();
				mem_network->insert(u, v, r_nums, share_cost);
				mem_network->insert(v, u, r_nums, share_cost);
			}
			spare_r.push_back(v);
			mem_network->insert(st, v, r_nums);
		}

		for (c = 0; c < c_segs; ++c) {
			auto v = mem_network->new_vertex();
			if (!spare_c.empty()) {
				auto u = spare_c.back();
				mem_network->insert(u, v, c_nums, share_cost);
				mem_network->insert(v, u, c_nums, share_cost);
			}  // sharing structure

			spare_c.push_back(v);
			mem_network->insert(st, v, c_nums);
		}

		for (r = 0; r < r_segs; ++r) {
			for (c = 0; c < c_segs; ++c) {
				auto block = new BipartiteGraph();
				bi_block.push_back(block);

				auto v = mem_network->new_vertex();
				v_block_x.push_back(v);
				mem_network->insert(spare_c[c], v, INF_CAP);  // INF capacity
				mem_network->insert(v, ed); 

				v = mem_network->new_vertex();
				v_block_y.push_back(v);
				mem_network->insert(spare_r[r], v, INF_CAP);
				mem_network->insert(v, ed);
				
				int mi = r == r_segs - 1 ? rs + rows % r_segs : rs;
				int mj = c == c_segs - 1 ? cs + cols % c_segs : cs;

				for (int k = 0; k < mi; ++k) {
					auto v = block->new_vertex_x();
					block->insert(block->st, v, 1);
				}  // for rows X i

				for (int k = 0; k < mj; ++k) {
					auto v = block->new_vertex_y();
					block->insert(v, block->ed, 1);
				}  // for cols Y j
			}
		}  // build block grid
	}

	tuple<int, int, int> 
		MemRepairBaseline::gloabl_to_local(int gi, int gj) {

		int r = gi / rs;
		int c = gj / cs;
		int li = (gi % rs) + (r == r_segs ? rs : 0);
		int lj = (gj % cs) + (c == c_segs ? cs : 0);

		int b_id = std::min(r, r_segs - 1) * c_segs + std::min(c, c_segs - 1);
		return std::make_tuple(b_id, li, lj);
	}

	int MemRepairBaseline::total_failures() {
		return failure_map.size();
	}

	void MemRepairBaseline::increment_mcnts(const vector<pair<int, int>>& mcnts) {
		for (auto && pos : mcnts) {
			auto it = failure_map.find(pos);
			if (it == failure_map.end()) {
				failure_map.insert(pos);

				auto local = gloabl_to_local(pos.first, pos.second);
				int b_id = std::get<0>(local);
				int i = std::get<1>(local), j = std::get<2>(local);

				auto block = bi_block[b_id];
				block->insert(block->ver_x[i], block->ver_y[j], INF_CAP);
			}
		}
	}

	bool MemRepairBaseline::repair() {
		
		int inc_req = 0;
		for (size_t i = 0; i < bi_block.size(); ++i) {
			auto cover = bi_block[i]->inc_min_weighted_cover();

			auto u = v_block_x[i];
			for (auto&& e = u->first; e != NULL; e = e->next) {
				if (e->v == mem_network->ed) {
					e->c = cover.first;
					inc_req += e->c;
					break;
				}
			}

			u = v_block_y[i];
			for (auto&& e = u->first; e != NULL; e = e->next) {
				if (e->v == mem_network->ed) {
					e->c = cover.second;
					inc_req += e->c;
					break;
				}
			}
		}  // check all blocks and update residule graph


		auto flow_cost = mem_network->max_flow_min_cost();

		current_flow += flow_cost.first;
		if (flow_cost.first < inc_req) {
			return false;
		}
		return true;
	}

	void MemRepairBaseline::report_allocation() {
		map<Graph::Vertex, int> resource_alloc;

		for (auto e = mem_network->st->first; e != NULL; e = e->next) {
			resource_alloc[e->v] = mem_network->edges[e->id ^ 1]->c;
		}

		cout 
			<< "<<<<<<<<<<<<<<<<<<"
			<< "Report Sparing bit line usage"
			<< ">>>>>>>>>>>>>>>>>>" << endl;


		cout << "Sparing Row bit lines: " << endl;
		for (auto && v : spare_c) {
			cout << resource_alloc[v] << " ";
		} cout << endl;


		cout << "Sparing Column bit lines: " << endl;
		for (auto && v : spare_r) {
			cout << resource_alloc[v] << " ";
		} cout << endl;

	}
}