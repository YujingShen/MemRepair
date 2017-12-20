#include "Graph.h"
#include <cassert>

int main(int narg, char *args[]) {
	auto block = new sjtu::BipartiteGraph();

	auto u1 = block->new_vertex_x();
	block->insert(block->st, u1, 2);
	assert((block->edges).size() == 2);

	auto u2 = block->new_vertex_x();
	block->insert(block->st, u2, 1);

	auto v = block->new_vertex_y();
	block->insert(v, block->ed, 1);
	
	block->insert(u1, v, 10);
	block->insert(u2, v, 10);

	auto r = block->min_weighted_cover();
	assert(r.first == 0 && r.second == 1);

	return 0;
}