#include "Graph.h"

namespace sjtu {

	using Graph::Edge;
	using Graph::Vertex;
	
	Edge Graph::new_edge(Vertex u, Vertex v, int c, float w) {
		auto edge = new _Edge();
		edge->u = u, edge->v = v, edge->c = c, edge->w = w;
		edge_stack.push_back(edge);
		return edge;
	}



}