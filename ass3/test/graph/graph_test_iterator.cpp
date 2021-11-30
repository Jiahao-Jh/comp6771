#include "gdwg/graph.hpp"

#include <catch2/catch.hpp>
#include <vector>

TEST_CASE("iterator constructor test") {
	SECTION("iterator constructor with list constructor") {
		auto g1 = gdwg::graph<int, int>{23, 31, 71};

		g1.insert_edge(23, 31, 6);
		g1.insert_edge(23, 31, 5);
		g1.insert_edge(31, 23, 7);
		g1.insert_edge(31, 23, 8);

		auto a = g1.begin();
		a = g1.end();
	}

	SECTION("iterator constructor with default graph Constructors ") {
		auto g2 = gdwg::graph<int, int>();
		auto a = g2.begin();
		a = g2.end();
	}
}

TEST_CASE("iterator increment test") {
	auto g1 = gdwg::graph<int, int>{23, 31, 71};

	g1.insert_edge(31, 23, 7);
	g1.insert_edge(23, 31, 6);
	g1.insert_edge(23, 31, 5);
	g1.insert_edge(31, 23, 8);
	g1.insert_edge(31, 31, 9);

	int count = 0;
	for (auto i = g1.begin(); i != g1.end(); i++) {
		switch (count) {
		case 0:
			CHECK((*i).from == 23);
			CHECK((*i).to == 31);
			CHECK((*i).weight == 5);
			break;
		case 1:
			CHECK((*i).from == 23);
			CHECK((*i).to == 31);
			CHECK((*i).weight == 6);
			break;
		case 2:
			CHECK((*i).from == 31);
			CHECK((*i).to == 23);
			CHECK((*i).weight == 7);
			break;
		case 3:
			CHECK((*i).from == 31);
			CHECK((*i).to == 23);
			CHECK((*i).weight == 8);
			break;
		case 4:
			CHECK((*i).from == 31);
			CHECK((*i).to == 31);
			CHECK((*i).weight == 9);
			break;
		}
		count++;
	}

	CHECK(count == 5);
}

TEST_CASE("iterator decrement test") {
	auto g1 = gdwg::graph<int, int>{23, 31, 71};

	g1.insert_edge(31, 23, 7);
	g1.insert_edge(23, 31, 6);
	g1.insert_edge(23, 31, 5);
	g1.insert_edge(31, 23, 8);

	int count = 0;
	for (auto i = g1.end(); i != g1.begin();) {
		--i;
		switch (count) {
		case 0:
			CHECK((*i).from == 31);
			CHECK((*i).to == 23);
			CHECK((*i).weight == 8);
			break;
		case 1:
			CHECK((*i).from == 31);
			CHECK((*i).to == 23);
			CHECK((*i).weight == 7);
			break;
		case 2:
			CHECK((*i).from == 23);
			CHECK((*i).to == 31);
			CHECK((*i).weight == 6);
			break;
		case 3:
			CHECK((*i).from == 23);
			CHECK((*i).to == 31);
			CHECK((*i).weight == 5);
			break;
		}
		count++;
	}

	CHECK(count == 4);
}

TEST_CASE("iterator general test") {
	auto g1 = gdwg::graph<int, int>{23, 31, 71};

	g1.insert_edge(31, 23, 7);
	g1.insert_edge(23, 31, 6);
	g1.insert_edge(23, 31, 5);
	g1.insert_edge(31, 23, 8);

	int count = 0;
	for (auto i = g1.end(); i != g1.begin();) {
		--i;
		switch (count) {
		case 0:
			CHECK((*i).from == 31);
			CHECK((*i).to == 23);
			CHECK((*i).weight == 8);
			break;
		case 1:
			CHECK((*i).from == 31);
			CHECK((*i).to == 23);
			CHECK((*i).weight == 7);
			break;
		case 2:
			CHECK((*i).from == 23);
			CHECK((*i).to == 31);
			CHECK((*i).weight == 6);
			break;
		case 3:
			CHECK((*i).from == 23);
			CHECK((*i).to == 31);
			CHECK((*i).weight == 5);
			break;
		}
		count++;
	}

	CHECK(count == 4);
	count = 0;
	for (auto i = g1.begin(); i != g1.end(); i++) {
		switch (count) {
		case 0:
			CHECK((*i).from == 23);
			CHECK((*i).to == 31);
			CHECK((*i).weight == 5);
			break;
		case 1:
			CHECK((*i).from == 23);
			CHECK((*i).to == 31);
			CHECK((*i).weight == 6);
			break;
		case 2:
			CHECK((*i).from == 31);
			CHECK((*i).to == 23);
			CHECK((*i).weight == 7);
			break;
		case 3:
			CHECK((*i).from == 31);
			CHECK((*i).to == 23);
			CHECK((*i).weight == 8);
			break;
		}
		count++;
	}

	CHECK(count == 4);
}

TEST_CASE("iterator equal test") {
	auto g1 = gdwg::graph<int, std::string>{23, 31};
	auto g2 = gdwg::graph<int, std::string>();

	CHECK(g1.begin() == g1.begin());
	CHECK(g1.begin() == g1.end());

	CHECK(g2.begin() == g2.end());
}