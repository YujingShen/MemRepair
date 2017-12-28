#include "FaultGen.h"
#include <cassert>
#include <iostream>

int main(int narg, char *args[]) {
	auto cnfet_gen = sjtu::MESP_faultgen();

	cnfet_gen.load_distr("../../../test/fault_distr.txt");
	
	
	for (int i = 0; i < 1001; ++i) {
		auto distr = cnfet_gen.next_distr();
		cnfet_gen.gen_fault_from_distr(distr, 64, 64);
	}
	
	return 0;
}