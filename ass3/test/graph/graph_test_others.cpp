#include "gdwg/graph.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <vector>

TEST_CASE("Extractor  test") {
	using graph = gdwg::graph<int, double>;
	auto const v = std::vector<graph::value_type>{
	   {1, 1, 1.2},
	   {1, 1, 2.3},
	   {1, 1, 3.4},
	   {1, 2, 5.6},
	   {2, 1, 5.6},
	   {2, 2, 8.888},
	   {2, 3, -5.0},
	   {2, 7, -9787},
	};

	auto g = graph{};
	for (const auto& [from, to, weight] : v) {
		g.insert_node(from);
		g.insert_node(to);
		g.insert_edge(from, to, weight);
	}

	auto out = std::ostringstream{};
	out << g;
	auto const expected_output = std::string_view(R"(1 (
  1 | 1.2
  1 | 2.3
  1 | 3.4
  2 | 5.6
)
2 (
  1 | 5.6
  2 | 8.888
  3 | -5
  7 | -9787
)
3 (
)
7 (
)
)");
	CHECK(out.str() == expected_output);
}

TEST_CASE("Comparisons  test") {
	auto g1 = gdwg::graph<int, std::string>{};
	auto g2 = gdwg::graph<int, std::string>{46, 47, 48, 0};
	auto g3 = gdwg::graph<int, std::string>{46, 47, 48, 0};

	CHECK(g1 == g1);
	CHECK(g2 == g2);
	CHECK(g3 == g3);

	CHECK(g2 == g3);

	g2.insert_edge(46, 0, "wubu");
	CHECK(g2 != g3);

	g3.insert_edge(46, 0, "wubu");
	CHECK(g2 == g3);
}