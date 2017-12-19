#pragma once

#include <vector>
#include <utility>

namespace sjtu {


	class Graph
	{
		using std::vector;

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

	public:
		Graph();
		virtual ~Graph();

	public:
		// creat new vertex
		Vertex new_vertex();

		// add new edge
		Edge new_edge(Vertex u, Vertex v, int c, float w);
		
		// insert an edge with capacity c weight w
		Graph& insert(Vertex u, Vertex v, int c, float w);

	public:
		vector<Vertex> vertices;
		vector<Edge> edges;
	};

	class GraphAlgorithm {
		using std::pair;

	public:
		static pair max_flow_min_cost(const Graph* graph, Graph::Vertex u, Graph::Vertex v);
		static pair vertex_cover_on_bipartite(const Graph* graph, Graph::Vertex u, Graph::Vertex v);
	};
}

