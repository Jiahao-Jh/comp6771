// test output is correct laddered (exactly one char different every time)
// using for loop go though the solutions and find the number of diffrent char between curr word and
// the next word
#include "comp6771/word_ladder.hpp"

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

TEST_CASE("at -> it") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("at", "it", english_lexicon);

	for (auto i : ladders) {
		for (auto x = i.begin(); std::next(x, 1) != i.end(); x++) {
			CHECK(ifLadder(*x, *std::next(x, 1)) == 1);
		}
	}
}

TEST_CASE("work -> play") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("work", "play", english_lexicon);

	for (auto i : ladders) {
		for (auto x = i.begin(); std::next(x, 1) != i.end(); x++) {
			CHECK(ifLadder(*x, *std::next(x, 1)) == 1);
		}
	}
}

TEST_CASE("atlases -> cabaret") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("atlases", "cabaret", english_lexicon);

	for (auto i : ladders) {
		for (auto x = i.begin(); std::next(x, 1) != i.end(); x++) {
			CHECK(ifLadder(*x, *std::next(x, 1)) == 1);
		}
	}
}
