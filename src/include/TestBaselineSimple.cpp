#include "MemRepair.h"
#include <cassert>

void create_file() {
	std::ofstream sf;
	sf.open("setting_file.txt", std::ios::out);
	sf
		<< 10 << " " << 10 << std::endl
		<< 3 << " " << 3 << std::endl
		<< 1 << " " << 1 << std::endl
		<< 1.0 << std::endl;
	sf.close();

	std::ofstream ff;
	ff.open("mcnt_file_1.txt", std::ios::out);
	ff
		<< 5 << " " << 4 << std::endl
		<< 5 << " " << 5 << std::endl
		<< 5 << " " << 6 << std::endl;
	ff.close();

	ff.open("mcnt_file_2.txt", std::ios::out);
	ff
		<< 5 << " " << 7 << std::endl;
	ff.close();
}




int main(int narg, char *args[]) {
	create_file();

	sjtu::MemRepairBaseline mem;
	mem.read_setting("setting_file.txt");
	mem.read_mcnts("mcnt_file_1.txt");

	assert(mem.repair() == true);
	mem.read_mcnts("mcnt_file_2.txt");

	assert(mem.repair() == true);
	return 0;
}