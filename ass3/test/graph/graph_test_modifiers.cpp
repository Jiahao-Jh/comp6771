#include "gdwg/graph.hpp"

#include <catch2/catch.hpp>
#include <vector>

// TODO
TEST_CASE("insert_edge test") {
	auto g1 = gdwg::graph<int, int>{23, 31, 71};
	CHECK(g1.insert_edge(31, 23, 7));
	CHECK(g1.insert_edge(31, 31, 7));

	CHECK(!g1.insert_edge(31, 31, 7));
	CHECK_THROWS(g1.insert_edge(31, 99, 7));
	CHECK_THROWS(g1.insert_edge(99, 23, 7));
}

TEST_CASE("insert_node test") {
	auto g1 = gdwg::graph<int, int>{23, 31, 71};

	CHECK(!g1.insert_node(31));
	CHECK(!g1.insert_node(23));
	CHECK(!g1.insert_node(71));

	CHECK(g1.insert_node(89));
	CHECK(g1.insert_node(76));
}

TEST_CASE("clear test") {
	auto g1 = gdwg::graph<int, int>{23, 31, 71};

	g1.insert_edge(31, 23, 7);
	g1.insert_edge(23, 31, 6);
	g1.insert_edge(23, 31, 5);
	g1.insert_edge(31, 23, 8);

	g1.clear();
	CHECK(g1.empty());
}

TEST_CASE("erase node test") {
	auto g1 = gdwg::graph<int, int>{23, 31, 71};

	g1.insert_edge(31, 23, 7);
	g1.insert_edge(23, 31, 6);
	g1.insert_edge(23, 31, 5);
	g1.insert_edge(31, 23, 8);

	CHECK(g1.erase_node(23));
	CHECK(!g1.erase_node(283));

	CHECK(g1.nodes() == std::vector<int>{31, 71});
	CHECK(g1.connections(31).empty());
	CHECK(g1.connections(71).empty());
}

TEST_CASE("erase_edge test") {
	auto g1 = gdwg::graph<int, int>{23, 31, 71};

	g1.insert_edge(31, 23, 7);
	g1.insert_edge(23, 31, 6);
	g1.insert_edge(23, 31, 5);
	g1.insert_edge(31, 23, 8);

	CHECK(g1.erase_edge(31, 23, 8));
	CHECK(!g1.erase_edge(31, 23, 889));
}

TEST_CASE("erase_edge iterator test") {
	auto g1 = gdwg::graph<int, int>{23, 31, 71};

	g1.insert_edge(31, 23, 7);
	g1.insert_edge(23, 31, 6);
	g1.insert_edge(23, 31, 5);
	g1.insert_edge(31, 23, 8);

	auto res = g1.erase_edge(g1.begin());
	CHECK((*res).from == 23);
	CHECK((*res).to == 31);
	CHECK((*res).weight == 6);

	res = g1.erase_edge(res);
	CHECK((*res).from == 31);
	CHECK((*res).to == 23);
	CHECK((*res).weight == 7);

	CHECK(g1.connections(23).empty());

	res = g1.erase_edge(res);
	CHECK((*res).from == 31);
	CHECK((*res).to == 23);
	CHECK((*res).weight == 8);

	CHECK(g1.weights(31, 23) == std::vector<int>{8});

	res = g1.erase_edge(res);
	CHECK(res == g1.end());
}

TEST_CASE("erase_edge two iterator test") {
	SECTION("erase edge use begin and end") {
		auto g1 = gdwg::graph<int, int>{23, 31, 71};

		g1.insert_edge(31, 23, 7);
		g1.insert_edge(23, 31, 6);
		g1.insert_edge(23, 31, 5);
		g1.insert_edge(31, 23, 8);

		auto res = g1.erase_edge(g1.begin(), g1.end());
		CHECK(res == g1.end());

		CHECK(g1.connections(23).empty());
		CHECK(g1.connections(31).empty());
	}

	SECTION("erase edge use begin and ++") {
		auto g2 = gdwg::graph<int, int>{23, 31, 71};
		g2.insert_edge(31, 23, 7);
		g2.insert_edge(23, 31, 6);
		g2.insert_edge(23, 31, 5);
		g2.insert_edge(31, 23, 8);

		auto it = g2.begin();
		it++;
		it++;

		g2.erase_edge(g2.begin(), it);

		CHECK(g2.connections(23).empty());
		CHECK(g2.weights(31, 23) == std::vector<int>{7, 8});
	}
}

TEST_CASE("replace_node test") {
	auto g1 = gdwg::graph<int, int>{23, 31, 71};

	g1.insert_edge(31, 23, 7);
	g1.insert_edge(23, 31, 6);
	g1.insert_edge(23, 31, 5);
	g1.insert_edge(31, 23, 8);
	g1.insert_edge(23, 23, 9);

	CHECK_THROWS(g1.replace_node(99, 99));

	CHECK(g1.replace_node(23, 99));

	CHECK(g1.weights(99, 31) == std::vector<int>{5, 6});
	CHECK(g1.weights(31, 99) == std::vector<int>{7, 8});
	CHECK(g1.weights(99, 99) == std::vector<int>{9});
}

TEST_CASE("merge_replace_node test") {
	SECTION("merge_replace_node without reflexive edge") {
		auto g1 = gdwg::graph<int, int>{23, 31, 71};

		g1.insert_edge(31, 23, 7);
		g1.insert_edge(23, 31, 6);
		g1.insert_edge(23, 31, 5);
		g1.insert_edge(31, 23, 8);

		CHECK_THROWS(g1.merge_replace_node(31, 99));
		CHECK_THROWS(g1.merge_replace_node(99, 23));

		g1.merge_replace_node(23, 31);

		CHECK(g1.weights(31, 31) == std::vector<int>{5, 6, 7, 8});

		g1.merge_replace_node(31, 71);

		CHECK(g1.weights(71, 71) == std::vector<int>{5, 6, 7, 8});
	}

	SECTION("merge_replace_node with reflexive edge") {
		auto g2 = gdwg::graph<int, int>{23, 31, 71};
		g2.insert_edge(23, 23, 7);
		g2.insert_edge(31, 31, 7);

		g2.merge_replace_node(23, 31);

		CHECK(g2.weights(31, 31) == std::vector<int>{7});
	}

	SECTION("merge_replace_node with string and int") {
		auto g3 = gdwg::graph<std::string, int>{"a", "b", "c", "d"};
		g3.insert_edge("a", "b", 1);
		g3.insert_edge("a", "c", 2);
		g3.insert_edge("a", "d", 3);
		g3.insert_edge("b", "b", 1);

		g3.merge_replace_node("a", "b");

		CHECK(g3.weights("b", "b") == std::vector<int>{1});
		CHECK(g3.weights("b", "c") == std::vector<int>{2});
		CHECK(g3.weights("b", "d") == std::vector<int>{3});
	}
}