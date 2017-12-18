#pragma once

#include <vector>
#include <utility>

namespace sjtu {
	using std::vector;
	using std::pair;

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
			Vertex u, v;
			int c;
			float w;
			Edge next;
		};

	public:
		Graph();
		virtual ~Graph();

	public:
		// creat new vertex
		Vertex new_vertex();
		
		// insert an edge with capacity c weight w
		void insert(Vertex u, Vertex v, int c, float w);

		// visit vertex by index
		Vertex operator[](int i);

	private:
		// add new edge
		Edge new_edge(Vertex u, Vertex v, int c, float w);

	private:
		vector<Vertex> vertex_stack;
		vector<Edge> edge_stack;
	};

	class FlowGraph
	{
	public:
		Graph graph;
		Graph::Vertex st, ed;

	public:
		FlowGraph();
		virtual ~FlowGraph() = default;
	};

	class GraphAlgorithm {
	public:
		pair max_flow_min_cost(const Graph* graph, Graph::Vertex u, Graph::Vertex v);
		pair vertex_cover_on_bipartite(const Graph* graph, Graph::Vertex u, Graph::Vertex v);
	};
}

