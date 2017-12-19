#pragma once

#include <vector>
#include <utility>
#include <cstddef>  // NULL
#include <queue>

namespace sjtu {
	using std::queue;
	using std::pair;
	using std::vector;


	class Graph
	{
	public:
		struct _Vertex;
		struct _Edge;

		typedef _Vertex* Vertex;
		typedef _Edge* Edge;

		struct _Vertex {
			int id;
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
		Vertex new_vertex(Edge first = NULL);

		// add new edge
		Edge new_edge(Vertex u = NULL, Vertex v = NULL, int c = 0, float w = 0.0f);
		
		// insert an edge with capacity c weight w
		Graph& insert(Vertex u, Vertex v, int c = 0, float w = 0.0f);

		vector<Vertex> vertices;
		vector<Edge> edges;
	};

	class FlowGraph: public Graph
	{
		const float INF;
		bool spfa(float &inc_cost, vector<Edge>& prev, vector<bool>& in_que, vector<float>& dist);

	public:
		pair<int, float> max_flow_min_cost();
		
		Graph& insert(Vertex u, Vertex v, int c = 0, float w = 0.0f);
	public:
		FlowGraph();
		virtual ~FlowGraph() = default;
		
	public:
		Vertex st, ed;
	};
}

