#include "gdwg/graph.hpp"
#include <iostream>

auto main() -> int {
	// auto g1 = gdwg::graph<int, int>{23, 31,71};

	// g1.insert_edge(31,23,7);
	// g1.insert_edge(23,31,6);
	// g1.insert_edge(23,31,5);
	// g1.insert_edge(31,23,8);

	// // std::cout<<g1 <<" \n";
	// g1.merge_replace_node(23,31);
	// std::cout<<g1 <<" \n";
	// g1.merge_replace_node(31, 71);
	// std::cout<<g1 <<" \n";

	auto g2 = gdwg::graph<int, int>{23, 31, 71};
	g2.insert_edge(23, 23, 7);
	g2.insert_edge(31, 31, 7);

	g2.merge_replace_node(23, 31);
	std::cout << g2 << " \n";

	// g1.insert_edge(23,31,6);
	// g1.insert_edge(23,31,5);
	// g1.insert_edge(31,23,7);
	// g1.insert_edge(31,23,8);

	// for (auto i = g1.end(); i != g1.begin();){
	//     --i;
	// 	std::cout << *i << "\n";
	// }

	// for (auto i = g1.begin(); i != g1.end();i++){
	// 	std::cout << *i << "\n";
	// }
}