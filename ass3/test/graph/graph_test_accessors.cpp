#include "gdwg/graph.hpp"

#include <catch2/catch.hpp>
#include <vector>

TEST_CASE("is_node test") {
	auto g = gdwg::graph<int, std::string>{46, 47, 48, 0};

	CHECK(g.is_node(46));
	CHECK(!g.is_node(465));
}

TEST_CASE("empty test") {
	auto g = gdwg::graph<int, std::string>();
	auto g1 = gdwg::graph<int, std::string>{46, 47, 48, 0};

	CHECK(g.empty());
	CHECK(!g1.empty());
}

TEST_CASE("is_connected test") {
	auto g1 = gdwg::graph<int, int>{23, 31, 71};

	g1.insert_edge(31, 23, 7);
	g1.insert_edge(23, 31, 6);
	g1.insert_edge(23, 31, 5);
	g1.insert_edge(31, 23, 8);

	CHECK(g1.is_connected(23, 31));
	CHECK(!g1.is_connected(23, 23));

	CHECK_THROWS(g1.is_connected(46546, 31));
	CHECK_THROWS(g1.is_connected(23, 846465));
}

TEST_CASE("nodes function test") {
	SECTION("nodes function test use list constructor and compare to vector") {
		auto v = std::vector<int>{0, 46, 47, 48};
		auto g = gdwg::graph<int, std::string>{46, 47, 48, 0};
		CHECK(v == g.nodes());
		CHECK(g.nodes() == g.nodes());
	}

	SECTION("nodes function test use vector constructor and compare to that vector") {
		auto v1 = std::vector<int>{0, 46, 47, 48, 78798};
		auto g1 = gdwg::graph<int, std::string>(v1.begin(), v1.end());
		CHECK(g1.nodes() == v1);
	}
}

TEST_CASE("weights function test") {
	auto g1 = gdwg::graph<int, int>{23, 31, 71};

	g1.insert_edge(31, 23, 7);
	g1.insert_edge(23, 31, 6);
	g1.insert_edge(23, 31, 5);
	g1.insert_edge(31, 23, 8);

	g1.insert_edge(31, 31, 9);
	g1.insert_edge(31, 31, 10);

	CHECK(g1.weights(23, 31) == std::vector<int>{5, 6});
	CHECK(g1.weights(31, 23) == std::vector<int>{7, 8});
	CHECK(g1.weights(31, 31) == std::vector<int>{9, 10});
}

TEST_CASE("find function test") {
	auto g1 = gdwg::graph<int, int>{23, 31, 71};

	g1.insert_edge(31, 23, 7);
	g1.insert_edge(23, 31, 6);
	g1.insert_edge(23, 31, 5);
	g1.insert_edge(31, 23, 8);

	CHECK(g1.find(23, 31, 5) == g1.begin());
	CHECK(g1.find(99, 99, 99) == g1.end());
}

TEST_CASE("connections function test") {
	auto g1 = gdwg::graph<int, int>{23, 31, 71};

	g1.insert_edge(31, 23, 7);
	g1.insert_edge(23, 31, 6);
	g1.insert_edge(23, 31, 5);
	g1.insert_edge(31, 23, 8);

	g1.insert_edge(31, 31, 9);
	g1.insert_edge(31, 31, 10);

	CHECK(g1.connections(31) == std::vector<int>{23, 31});
	CHECK(g1.connections(23) == std::vector<int>{31});

	CHECK_THROWS(g1.connections(99));
}