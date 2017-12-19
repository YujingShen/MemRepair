#include "Graph.h"
#include <cassert>

int main(int argn, char *args[]) {
	sjtu::FlowGraph flow_graph;

	flow_graph.insert(flow_graph.st, flow_graph.ed, 1);
	assert(flow_graph.edges.size() == 2);

	return 0;
}