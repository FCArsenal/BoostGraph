#pragma once
#include <vector>
#include <stdint.h>

namespace graph {

	class StaticGraph;
	template <typename Iterator>
	class Vertex
	{
		public:
			Vertex(Iterator t, int d) 
				: begin(t)
				, d(d)
			{}
			
			Vertex()
			: d(0)
			{}
			
			Vertex(int d)
				: d(d)
			{}

			Iterator begin;
			int d;
	};

	class StaticGraph
	{
		class VertexIterator;
	public:
		using edge_size_type = uint32_t;
		using vertices_size_type = uint32_t;
		using edges_size_type = uint32_t;
		using degree_size_type = uint16_t;
		using vertex_descriptor = vertices_size_type;
	private:
		using EdgesVecType = std::vector<vertex_descriptor>;		// вектор интов для ребер
	public:
		using adjacency_iterator = EdgesVecType::const_iterator;	// итератор по смежным вершинам ( по вектору интов )
		using VertexType = Vertex<EdgesVecType::const_iterator>;
	private:
		using VerticesVecType = std::vector<VertexType>;			// вектор интов для вершин
	public:

		VerticesVecType		vertG;
		EdgesVecType		edges;


		vertices_size_type	nodes;
		edge_size_type		arcs;
		vertex_descriptor	currentVert;


		class vertex_iterator : public std::iterator<std::forward_iterator_tag, VertexType>
		{
			private:

				const StaticGraph	*sgraph;
			
			public:
			VerticesVecType::const_iterator				iter;

			public:

				vertex_iterator(const StaticGraph * g, VerticesVecType::const_iterator idx)
					: iter(idx)
					, sgraph(g)	{}

				vertex_iterator()
					: iter()
					, sgraph(nullptr){}

				vertex_descriptor vertex_iterator::operator*() const {
					return iter->d;
				}

				void vertex_iterator::operator++() {
					if (iter->d <= sgraph->nodes)
					{
						//std::cout << sgraph->nodes << " " << index << " ";
						++iter;
					}
				}

				bool vertex_iterator::operator== (const vertex_iterator& anotherIterator) const {
					return iter == anotherIterator.iter;
				}

				bool vertex_iterator::operator!= (const vertex_iterator& other) const {
					return !(this->operator==(other));
				}
		
		};

		using edge_descriptor = std::pair<vertex_descriptor, vertex_descriptor>;		// ребро - пара вершин (а, м)

		StaticGraph() {};

		template <class PairIterator>
		StaticGraph(PairIterator begin, PairIterator end, vertices_size_type n, edges_size_type m);

	};

	template <class PairIterator>
	StaticGraph::StaticGraph(PairIterator begin, PairIterator end, vertices_size_type n, edges_size_type m)
		: nodes(n)
		, arcs(m)
	{
		// (1, 2) (1, 3) (2, 1) (2, 3)

		vertex_descriptor shift = 0;
		
		vertG.resize(n + 2);
		edges.resize(m + 1);

		currentVert = begin->first;															// 1
		edges[shift++] = begin->second;														// edges[1] = 2, где "1" - название вершины 
		vertG[begin->first] = Vertex<EdgesVecType::const_iterator>(edges.begin(), begin->first);
		vertG[begin->second] = Vertex<EdgesVecType::const_iterator>(begin->second);

		

		for (auto t = begin + 1; t != end; ++t)
		{
			// подряд добавляем ребра
			if (t->first == currentVert)
			{
				edges[shift++] = t->second;
				vertG[t->second] = Vertex<EdgesVecType::const_iterator>(edges.begin() + shift, t->second);
			}
			// новое ребро
			else
			{
				currentVert = t->first;
				edges[shift++] = t->second;
				vertG[t->first]		= Vertex<EdgesVecType::const_iterator>(edges.begin() + shift - 1, t->first);
				vertG[t->second] = Vertex<EdgesVecType::const_iterator>(edges.begin() + shift, t->second);
			}
		}
		vertG[n + 1] = Vertex<EdgesVecType::const_iterator>(edges.begin() + shift, 1);
	}

	// вернуть итератор всех вершин графа		vertices(const StaticGraph& g)

	std::pair<StaticGraph::vertex_iterator, StaticGraph::vertex_iterator> vertices(const StaticGraph& g) 
	{
		return std::make_pair( StaticGraph::vertex_iterator(&g, g.vertG.begin() + 1), StaticGraph::vertex_iterator(&g, g.vertG.end() - 1 ) );
	}

	// вернуть итератор всех смежных для u вершин графа, т.е. таких v :   u ---> v
	std::pair<StaticGraph::adjacency_iterator, StaticGraph::adjacency_iterator>
		adjacent_vertices(StaticGraph::vertex_descriptor u, const StaticGraph& g)
	{
			return std::make_pair(g.vertG[u].begin, g.vertG[u + 1].begin);
	}
	

	// Если существует ребро м/у вершиной u и v, return ребро и true. Иначе return a pair with an arbitrary edge descriptor and false.
	std::pair<StaticGraph::edge_descriptor, bool>
		edge(StaticGraph::vertex_descriptor u, StaticGraph::vertex_descriptor v,
		const StaticGraph& g)
	{
			for (auto t = g.vertG[u].begin; t != g.vertG[u + 1].begin; ++t)
			{
				if (*t == v)
					return std::pair<StaticGraph::edge_descriptor, bool>(StaticGraph::edge_descriptor(u, v), true);
			}
			return std::pair<StaticGraph::edge_descriptor, bool>(StaticGraph::edge_descriptor(u, u), false);
	}

	// Returns u , where u--------->v
	StaticGraph::vertex_descriptor
		source(StaticGraph::edge_descriptor e, const StaticGraph& g)
	{
			return e.first;
	}

	// Returns v , where u--------->v
	StaticGraph::vertex_descriptor
		target(StaticGraph::edge_descriptor e, const StaticGraph& g)
	{
			return e.second;
	}

	// Возвращаем число исходящих вершин
	StaticGraph::degree_size_type
		out_degree(StaticGraph::vertex_descriptor u, const StaticGraph& g)
	{
			return g.vertG[u + 1].begin - g.vertG[u].begin;
	}

	// возвращаем число всех вершин графа
	StaticGraph::vertices_size_type
		num_vertices(const StaticGraph& g)
	{
			return g.nodes;
	}

	// возвращаем число всех ребер графа
	StaticGraph::edges_size_type
		num_edges(const StaticGraph& g)
	{
			return g.arcs;
	}
}