#include "MemRepair.h"
#include "FaultGen.h"
#include <string>
#include <iostream>
using std::string;

int main(int narg, char *args[]) {
	if (narg < 3) {
		std::cout
			<< "Useage: " << std::endl
			<< "./MemRepairBaseline setting_file_path distr_file_path(faultNum)"
			<< std::endl;
	}

	sjtu::MemRepairBaseline mem;
	sjtu::CNFET_faultgen fault_gen;

	mem.read_setting(args[1]);
	fault_gen.load_distr(args[2]);

	int success_num = 0;
	for (size_t i = 0; i < fault_gen.size(); ++i) {
		mem.rebuild_flow_graph();
		auto distr = fault_gen.next_distr();
		mem.increment_mcnts(
			fault_gen.gen_fault_from_distr(
				distr, mem.row_num(), mem.col_num()
			)
		);
		if (mem.repair()) {
			++success_num;
		}
	}

	float ratio = (float)success_num / (float)fault_gen.size();

	std::cout << "ratio: " << ratio << std::endl;

	return 0;
}