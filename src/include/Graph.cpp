#include "Graph.h"

namespace sjtu {

	typedef Graph::Edge Edge;
	typedef Graph::Vertex Vertex;
	
	Edge Graph::new_edge(Vertex u, Vertex v, int c, float w) {
		auto edge = new _Edge();

		edge->u = u, edge->v = v, edge->c = c, edge->w = w; 

		edge->id = edges.size();
		edge->next = NULL;

		edges.push_back(edge);

		return edge;
	}

	Vertex Graph::new_vertex(Edge first) {
		auto ver = new _Vertex();

		ver->id = vertices.size();
		ver->first = first;
		
		vertices.push_back(ver);

		return ver;
	}

	Graph& Graph::insert(Vertex u, Vertex v, int c, float w) {
		auto e = new_edge(u, v, c, w);
		
		e->next = u->first;
		u->first = e;
		
		return *this;
	}

	Graph::~Graph() {
		for (auto &&v : vertices) {
			delete v;
		}

		for (auto &&e : edges) {
			delete e;
		}
	}

	FlowGraph::FlowGraph() {
		st = new_vertex();
		ed = new_vertex();
	}

	pair<int, float> FlowGraph::max_flow_min_cost() {
		return std::make_pair(0, 0.0);
	}
}