#include <iostream>
#include "static_graph.h"
#include <iterator>


using namespace std;
using namespace graph;


void test1()
{
	StaticGraph staticGraph;

	std::pair<StaticGraph::vertex_iterator, StaticGraph::vertex_iterator> vi = vertices(staticGraph);
	std::copy(vi.first, vi.second, std::ostream_iterator<StaticGraph::vertex_descriptor>{ std::cout, "\n" });
}

void test2()
{
	using vv = StaticGraph::vertex_descriptor;
	using t = std::pair<vv, vv>;

	std::vector<t> input = { t(1, 2), t(1, 3), t(2, 3), t(4, 1) };
	StaticGraph staticGraph(input.begin(), input.end(), (StaticGraph::vertices_size_type)4, (StaticGraph::edges_size_type)input.size());

	std::pair<StaticGraph::vertex_iterator, StaticGraph::vertex_iterator> vi = vertices(staticGraph);
	std::copy(vi.first, vi.second, std::ostream_iterator<StaticGraph::vertex_descriptor>{ std::cout, "\n" });
}

void test3()
{
	using vv = StaticGraph::vertex_descriptor;
	using t = std::pair<vv, vv>;

	std::vector<t> input = { t(1, 2), t(1, 3), t(2, 3) };
	StaticGraph staticGraph(input.begin(), input.end(), (StaticGraph::vertices_size_type)3, (StaticGraph::edges_size_type)input.size());



	std::cout << "adjacent for 1 = \n";
	std::pair<StaticGraph::adjacency_iterator, StaticGraph::adjacency_iterator> ai_1 = adjacent_vertices(1, staticGraph);
	std::copy(ai_1.first, ai_1.second, std::ostream_iterator<StaticGraph::vertex_descriptor>{ std::cout, "\n" });

	std::cout << "adjacent for 2 = \n";
	std::pair<StaticGraph::adjacency_iterator, StaticGraph::adjacency_iterator> ai_2 = adjacent_vertices(2, staticGraph);
	std::copy(ai_2.first, ai_2.second, std::ostream_iterator<StaticGraph::vertex_descriptor>{ std::cout, "\n" });


	std::cout << "adjacent for 3 = \n";
	std::pair<StaticGraph::adjacency_iterator, StaticGraph::adjacency_iterator> ai_3 = adjacent_vertices(3, staticGraph);
	std::copy(ai_3.first, ai_3.second, std::ostream_iterator<StaticGraph::vertex_descriptor>{ std::cout, "\n" });
}

void test4()
{
	using vv = StaticGraph::vertex_descriptor;
	using t = std::pair<vv, vv>;

	std::vector<t> input = { t(1, 2), t(1, 3), t(2, 3) };
	StaticGraph staticGraph(input.begin(), input.end(), (StaticGraph::vertices_size_type)3, (StaticGraph::edges_size_type)input.size());

	std::pair<StaticGraph::edge_descriptor, bool> res = edge(1, 2, staticGraph);
	std::cout << res.first.first << " " << res.first.second << " " << res.second << "\n";

	std::pair<StaticGraph::edge_descriptor, bool> res1 = edge(1, 3, staticGraph);
	std::cout << res1.first.first << " " << res1.first.second << " " << res1.second << "\n";

	std::pair<StaticGraph::edge_descriptor, bool> res2 = edge(2, 3, staticGraph);
	std::cout << res2.first.first << " " << res2.first.second << " " << res2.second << "\n";


	std::pair<StaticGraph::edge_descriptor, bool> res3 = edge(3, 1, staticGraph);
	std::cout << res3.first.first << " " << res3.first.second << " " << res3.second << "\n";


	std::pair<StaticGraph::edge_descriptor, bool> res4 = edge(3, 2, staticGraph);
	std::cout << res4.first.first << " " << res4.first.second << " " << res4.second << "\n";
}

void test5()
{
	using vv = StaticGraph::vertex_descriptor;
	using t = std::pair<vv, vv>;

	std::vector<t> input = { t(1, 2), t(1, 3), t(2, 3) };
	StaticGraph staticGraph(input.begin(), input.end(), (StaticGraph::vertices_size_type)3, (StaticGraph::edges_size_type)input.size());

	std::cout << out_degree(1, staticGraph) << "\n";
	std::cout << out_degree(2, staticGraph) << "\n";
	std::cout << out_degree(3, staticGraph) << "\n";
}



int main() 
{
	//test1();
	test2();
	//test3();
	//test4();
	//test5();
	system("pause");
	return 0;
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          