/*
#include <iostream>
#include "static_graph.h"


using namespace std;
using namespace graph;
int main() {
	StaticGraph staticGraph;
	return 0;
}
*/
//#include <boost / config.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <boost/graph/adjacency_list.hpp>
#include <boost/tuple/tuple.hpp>

enum family
{
	Jeanie, Debbie, Rick, John, Amanda, Margaret, Benjamin, N
};

int main()
{
	using namespace boost;
	const char *name[] = { "Jeanie", "Debbie", "Rick", "John", "Amanda",
		"Margaret", "Benjamin"
	};

	typedef adjacency_list <> Graph;
	adjacency_list <> g(N);
	add_edge(Jeanie, Debbie, g);
	add_edge(Jeanie, Rick, g);
	add_edge(Jeanie, John, g);
	add_edge(Debbie, Amanda, g);
	add_edge(Rick, Margaret, g);
	add_edge(John, Benjamin, g);

	graph_traits < adjacency_list <> >::vertex_iterator i, end;
	graph_traits < adjacency_list <> >::adjacency_iterator ai, a_end;
	property_map < adjacency_list <>, vertex_index_t >::type
		index_map = get(vertex_index, g);

	for (boost::tie(i, end) = vertices(g); i != end; ++i) {
		std::cout << name[get(index_map, *i)];
		boost::tie(ai, a_end) = adjacent_vertices(*i, g);
		if (ai == a_end)
			std::cout << " has no children";
		else
			std::cout << " is the parent of ";
		for (; ai != a_end; ++ai) {
			std::cout << name[get(index_map, *ai)];
			if (boost::next(ai) != a_end)
				std::cout << ", ";
		}
		std::cout << std::endl;
	}

	std::pair<boost::adjacency_list<>::vertex_iterator,
		boost::adjacency_list<>::vertex_iterator> vs = boost::vertices(g);

	std::copy(vs.first, vs.second, std::ostream_iterator<boost::adjacency_list<>::vertex_descriptor>{ std::cout, "\n" });


	std::cout << "adjacent(g) = ";
	graph_traits<Graph>::adjacency_iterator ait, aend;
	std::tie(ait, aend) = boost::adjacent_vertices(1, g);
	std::copy(ait, aend, std::ostream_iterator<Graph::vertex_descriptor>{std::cout, "\n"});

	// ITERATORS
	std::cout << "edges(g) = ";
	graph_traits<Graph>::edge_iterator ei, ei_end;
	for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
		std::cout << "(" << (*ei).m_source << "," << (*ei).m_target << ") ";
	std::cout << std::endl;

	std::cout << "edges(g) = ";
	graph_traits<Graph>::vertex_iterator vi, vi_end;
	for (tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi)
		std::cout << (*vi) <<" ";
	std::cout << std::endl;

	system("pause");
	return EXIT_SUCCESS;
}