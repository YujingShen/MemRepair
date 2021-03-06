#pragma once
#include <vector>
#include <utility>
#include <string>
#include <tuple>
#include <fstream>
#include <sstream>

namespace sjtu {
	using std::vector;
	using std::pair;
	using std::string;
	using std::tuple;
	using std::fstream;
	using std::stringstream;

	class MESP_faultgen
	{
		
	public:
		MESP_faultgen() = default;
		virtual ~MESP_faultgen() = default;

		void load_distr(const string& distr_file_path);

		vector<int> next_distr();

		// not deal with redundancy
		vector<pair<int, int>> 
			gen_fault_from_distr(const vector<int>& distr, int row, int col);

		size_t size();
	private:
		vector<vector<int>> candidate;
		vector<vector<int>>::iterator candi_itr;
	};
}