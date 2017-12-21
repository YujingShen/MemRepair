#include "MemRepair.h"
#include <string>
#include <iostream>
using std::string;

int main(int narg, char *args[]) {
	if (narg < 3) {
		std::cout
			<< "Useage: " << std::endl
			<< "./MemRepairBaseline setting_file_path mcnts_path"
			<< std::endl;
	}

	sjtu::MemRepairBaseline mem;

	mem.read_setting(args[1]);
	mem.read_mcnts(args[2]);
	mem.repair();
	mem.report_allocation();

	return 0;
}