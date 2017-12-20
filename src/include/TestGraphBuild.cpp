#include "MemRepair.h"
#include <cassert>
#include <fstream>
#include <utility>

void create_file() {
	std::ofstream sf;
	sf.open("setting_file.txt", std::ios::out);
	sf
		<< 10 << " " << 10 << std::endl
		<< 3 << " " << 3 << std::endl
		<< 1 << " " << 1 << std::endl
		<< 1.0 << std::endl;
	sf.close();
}

using std::get;
using std::cout;
using std::endl;

int main(int narg, char *args[]) {
	create_file();
	sjtu::MemRepairBaseline mem;

	mem.read_setting("setting_file.txt");

	auto r = mem.gloabl_to_local(9, 9);

	assert(get<0>(r) == 8);
	assert(get<1>(r) == 1);
	assert(get<2>(r) == 1);

	r = mem.gloabl_to_local(0, 0);
	assert(get<0>(r) == 0);
	assert(get<1>(r) == 0);
	assert(get<2>(r) == 0);

	r = mem.gloabl_to_local(5, 5);
	assert(get<0>(r) == 4);
	assert(get<1>(r) == 1);
	assert(get<2>(r) == 1);


	return 0;
}