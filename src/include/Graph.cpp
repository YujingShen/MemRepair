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

	FlowGraph::FlowGraph(): INF(10000000.0f) {
		st = new_vertex();
		ed = new_vertex();
	}

	pair<int, float> FlowGraph::max_flow_min_cost() {
		int vf = 0;
		float cost = 0.0f;

		vector<Edge> flow;
		float inc_cost;
		while (spfa(flow, inc_cost)) {
			int min_cap = 0x7ffffff;
			for (auto && e : flow) {
				min_cap = std::min(min_cap, e->c);
			}

			for (auto && e : flow) {
				e->c -= min_cap;
				edges[e->id ^ 1] += min_cap;
			}

			vf += min_cap;
			cost += inc_cost;
			flow.clear();
		}
		
		return std::make_pair(vf, cost);
	}

	bool FlowGraph::spfa(vector<Edge>& flow, float &inc_cost) {
		queue<Vertex> que;
		vector<bool> in_que(vertices.size(), false);
		vector<float> dist(vertices.size(), INF);
		vector<Edge> prev(vertices.size(), NULL);

		in_que[st->id] = true;
		dist[st->id] = 0.0f;
		que.push(st);

		while (!que.empty()) {
			auto u = que.front();
			que.pop();
			in_que[u->id] = false;
			for (auto e = u->first; e != NULL; e = e->next) {
				if (e->c > 0 && dist[u->id] + e->w < dist[e->v->id]) {
					dist[e->v->id] = dist[u->id] + e->w;
					prev[e->v->id] = e;
					
					if (!in_que[e->v->id]) {
						in_que[e->v->id] = true;
						que.push(e->v);
					}  // enque
				}
			}  // for edges
		}  // spfa

		if (prev[ed->id] == NULL || dist[ed->id] == INF) {
			return false;
		}

		inc_cost = dist[ed->id];
		auto u = ed;
		while (prev[u->id] != NULL) {
			flow.push_back(prev[u->id]);
			u = prev[u->id]->u;
		}  // extract flow
		return true;
	}
}