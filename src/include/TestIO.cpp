#include "MemRepair.h"
#include <fstream>

void create_file() {
	std::ofstream sf;
	sf.open("setting_file.txt", std::ios::out);
	sf
		<< 10 << " " << 10 << std::endl
		<< 1 << " " << 1 << std::endl
		<< 1 << " " << 1 << std::endl
		<< 1.0 << std::endl;
	sf.close();

	std::ofstream ff;
	ff.open("mcnt_file.txt", std::ios::out);
	ff
		<< 1 << " " << 2 << std::endl
		<< 1 << " " << 3 << std::endl
		<< 1 << " " << 4 << std::endl;
	ff.close();

}

int main() {
	sjtu::MemRepair mem;
	
	create_file();

	mem.read_setting("setting_file.txt");
	mem.read_mcnts("mcnt_file.txt");
	mem.repair();
	mem.report_allocation();
	return 0;
}