#include "Graph.h"
#include <cassert>

int main(int narg, char *args[]) {
	auto block = new sjtu::BipartiteGraph();

	auto v = block->new_vertex_x();
	block->insert(block->st, v);
	assert((block->edges).size() == 2);
	return 0;
}