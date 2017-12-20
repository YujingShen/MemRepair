#pragma once

#include <vector>
#include <utility>
#include <cstddef>  // NULL
#include <queue>
#include <set>
#include <cassert>

namespace sjtu {
	using std::queue;
	using std::pair;
	using std::vector;
	using std::set;

	class Graph;
	class FlowGraph;
	class BipartiteGraph;

	class Graph
	{
	public:
		struct _Vertex;
		struct _Edge;

		typedef _Vertex* Vertex;
		typedef _Edge* Edge;

		struct _Vertex {
			int id;
			int d;  // degree
			Edge first;
		};

		struct _Edge
		{
			int id;
			Vertex u, v;
			int c;
			float w;
			Edge next;
		};

		Graph() = default;
		virtual ~Graph();

		// creat new vertex
		virtual Vertex new_vertex(Edge first = NULL);

		// add new edge
		virtual Edge new_edge(Vertex u = NULL, Vertex v = NULL, int c = 0, float w = 0.0f);
		
		// insert an edge<u, v> with capacity c weight w
		virtual Edge insert(Vertex u, Vertex v, int c = 0, float w = 0.0f);

		vector<Vertex> vertices;
		vector<Edge> edges;
	};

	class FlowGraph : public Graph
	{
		const float INF;
		bool spfa(float &inc_cost, vector<Edge>& prev, vector<bool>& in_que, vector<float>& dist);

	public:
		pair<int, float> max_flow_min_cost();
		
		virtual Edge insert(Vertex u, Vertex v, int c = 0, float w = 0.0f);
	public:
		FlowGraph();
		virtual ~FlowGraph() = default;
		
	public:
		Vertex st, ed;
	};

	class BipartiteGraph : public FlowGraph
	{
	public:
		virtual Vertex new_vertex_x(Edge first = NULL);
		virtual Vertex new_vertex_y(Edge first = NULL);
		virtual Edge insert(Vertex u, Vertex v, int c = 0, float w = 0.0f);
		virtual pair<int, int> min_weighted_cover();
	public:
		vector<Vertex> ver_x, ver_y;
	protected:
		int prev_x, prev_y;
	};
}

