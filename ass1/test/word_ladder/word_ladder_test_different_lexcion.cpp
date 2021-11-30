// test program using a different lexicon
// aaaaa.txt is fulled with string from aaaaa to eeeee
// so there is supposed to be 120 shorest solutions from aaaaa to eeeee
#include "comp6771/word_ladder.hpp"

#include <unordered_set>
#include <string>
#include <vector>

#include "catch2/catch.hpp"

auto ifLadder(std::string strA, std::string strB) -> int {
	auto count = 0;

	for (unsigned long i = 0; i < strA.size(); i++) {
		if (strA.at(i) != strB.at(i)) {
			count++;
		}
	}

	return count;
}

TEST_CASE("a -> b") {
	auto tmp = std::unordered_set<std::string>{"a", "b"};
	auto const ladders = word_ladder::generate("a", "b", tmp);

	CHECK(std::size(ladders) == 1);
	CHECK(std::is_sorted(ladders.begin(), ladders.end()));
	CHECK(std::count(ladders.begin(), ladders.end(), std::vector<std::string>{"a", "b"}) == 1);

	for (auto i : ladders) {
		for (auto x = i.begin(); std::next(x, 1) != i.end(); x++) {
			CHECK(ifLadder(*x, *std::next(x, 1)) == 1);
		}
	}
}

TEST_CASE("aaaaa -> eeeee") {
	auto const english_lexicon = word_ladder::read_lexicon("./aaaaa.txt");
	auto const ladders = word_ladder::generate("aaaaa", "eeeee", english_lexicon);

	CHECK(std::size(ladders) == 120);
	CHECK(std::is_sorted(ladders.begin(), ladders.end()));
	CHECK(std::count(ladders.begin(),
	                 ladders.end(),
	                 std::vector<std::string>{"aaaaa", "aaaae", "aaaee", "aaeee", "aeeee", "eeeee"})
	      == 1);

	for (auto i : ladders) {
		for (auto x = i.begin(); std::next(x, 1) != i.end(); x++) {
			CHECK(ifLadder(*x, *std::next(x, 1)) == 1);
		}
	}
}