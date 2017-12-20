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

	Edge Graph::insert(Vertex u, Vertex v, int c, float w) {
		auto e = new_edge(u, v, c, w);
		
		e->next = u->first;
		u->first = e;
		return e;
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

	Edge FlowGraph::insert(Vertex u, Vertex v, int c, float w) {
		auto e = Graph::insert(u, v, c, w);
		Graph::insert(v, u, 0, -w);
		return e;
	}

	pair<int, float> FlowGraph::max_flow_min_cost() {
		int vf = 0;
		float cost = 0.0f;

		vector<Edge> prev(vertices.size(), NULL);
		vector<bool> in_que(vertices.size(), false);
		vector<float> dist(vertices.size(), 0.0f);
		float inc_cost;

		while (spfa(inc_cost, prev, in_que, dist)) {
			int min_cap = 0x7ffffff;

			auto u = ed;
			while (prev[u->id] != NULL) {
				min_cap = std::min(min_cap, prev[u->id]->c);
				u = prev[u->id]->u;
			}

			u = ed;
			while (prev[u->id] != NULL) {
				auto e = prev[u->id];
				e->c -= min_cap;
				edges[e->id ^ 1]->c += min_cap;
				u = e->u;
			}

			vf += min_cap;
			cost += inc_cost * min_cap;
		}
		
		return std::make_pair(vf, cost);
	}

	bool FlowGraph::spfa(float& inc_cost, 
		vector<Edge>& prev, vector<bool>& in_que, vector<float>& dist) {
		
		for (size_t i = 0; i < vertices.size(); ++i) {
			prev[i] = NULL, in_que[i] = false, dist[i] = INF;
		}
		
		queue<Vertex> que;

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
		return true;
	}


	Vertex BipartiteGraph::new_vertex_x(Edge first) {
		auto ver = new_vertex(first);
		ver_x.push_back(ver);
		return ver;
	}

	Vertex BipartiteGraph::new_vertex_y(Edge first) {
		auto ver = new_vertex(first);
		ver_y.push_back(ver);
		return ver;
	}

	Edge BipartiteGraph::insert(Vertex u, Vertex v, int c, float w) {
		auto e = FlowGraph::insert(u, v, c, w);
		if (u == st) {
			edges_s.push_back(e);
		} else if(v == ed) {
			edges_t.push_back(e);
		}
		return e;
	}
}