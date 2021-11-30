#include "gdwg/graph.hpp"

#include <catch2/catch.hpp>
#include <vector>

TEST_CASE("empty constructor test") {
	auto g = gdwg::graph<int, std::string>();
	CHECK(g.empty());

	CHECK(g.insert_node(23));
	CHECK(g.insert_node(31));

	CHECK(g.insert_edge(23, 31, "wubu"));

	CHECK(g.empty() == false);
	CHECK(g.is_node(23));
	CHECK(g.is_node(31));
	CHECK(g.is_connected(23, 31));
}

TEST_CASE("initializer list constructor test") {
	auto g = gdwg::graph<int, std::string>{23, 31};

	CHECK(g.empty() == false);
	CHECK(g.is_node(23));
	CHECK(g.is_node(31));
	CHECK(g.is_node(99) == false);
}

TEST_CASE("iterator constructor test") {
	auto v = std::vector<int>{23, 31};
	auto g = gdwg::graph<int, std::string>(v.begin(), v.end());

	CHECK(g.empty() == false);
	CHECK(g.is_node(23));
	CHECK(g.is_node(31));
	CHECK(g.is_node(99) == false);
}

TEST_CASE("move constructor test") {
	auto g1 = gdwg::graph<int, std::string>{23, 31};
	auto g2 = gdwg::graph(std::move(g1));

	CHECK(g1.empty());
	CHECK(g2.empty() == false);
	CHECK(g2.is_node(23));
	CHECK(g2.is_node(31));
	CHECK(g2.is_node(99) == false);
}

TEST_CASE("move assignment test") {
	auto g1 = gdwg::graph<int, std::string>{23, 31};
	auto g2 = gdwg::graph<int, std::string>();
	g2 = std::move(g1);

	CHECK(g1.empty());
	CHECK(g2.empty() == false);
	CHECK(g2.is_node(23));
	CHECK(g2.is_node(31));
	CHECK(g2.is_node(99) == false);
}

TEST_CASE("copy constructor test") {
	auto g1 = gdwg::graph<int, std::string>{23, 31};

	g1.insert_edge(23, 31, "wubu");

	auto g2 = gdwg::graph(g1);

	CHECK(g1 == g2);

	CHECK(g1.empty() == false);
	CHECK(g2.empty() == false);
	CHECK(g1.is_node(23));
	CHECK(g1.is_node(31));
	CHECK(g2.is_node(23));
	CHECK(g2.is_node(31));

	CHECK(g1.is_connected(23, 31));
	CHECK(g2.is_connected(23, 31));

	CHECK(g1.is_node(99) == false);
	CHECK(g1.is_node(99) == false);
}

TEST_CASE("copy assignment test") {
	auto g1 = gdwg::graph<int, std::string>{23, 31};
	auto g2 = gdwg::graph<int, std::string>();
	g2 = g1;

	CHECK(g1 == g2);

	CHECK(g1.empty() == false);
	CHECK(g2.empty() == false);
	CHECK(g1.is_node(23));
	CHECK(g1.is_node(31));
	CHECK(g2.is_node(23));
	CHECK(g2.is_node(31));

	CHECK(g1.is_node(99) == false);
	CHECK(g1.is_node(99) == false);
}
