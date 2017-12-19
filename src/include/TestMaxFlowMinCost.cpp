#include "Graph.h"
#include <cassert>
#include <vector>
#include <cmath>
using std::vector;


//st->0->1->2->ed
//st->0->2->ed

int main(int argn, char *args[]) {

	sjtu::FlowGraph flow_graph;

	vector<sjtu::Graph::Vertex> vertices;

	vertices.push_back(flow_graph.new_vertex());
	vertices.push_back(flow_graph.new_vertex());
	vertices.push_back(flow_graph.new_vertex());

	flow_graph.insert(flow_graph.st, vertices[0], 2);
	flow_graph.insert(vertices[0], vertices[1], 1, 1.0f);
	flow_graph.insert(vertices[1], vertices[2], 1);
	flow_graph.insert(vertices[0], vertices[2], 1, 4.0f);
	flow_graph.insert(vertices[2], flow_graph.ed, 2);

	auto r = flow_graph.max_flow_min_cost();

	assert(r.first == 2 && std::abs(r.second - 5.0f) < 0.0001f);
	return 0;
}