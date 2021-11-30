// test program gives correct numbers of solutions
// and gives correct length of shortest solution
#include "comp6771/word_ladder.hpp"

#include <string>
#include <vector>

#include "catch2/catch.hpp"

TEST_CASE("at -> it") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("at", "it", english_lexicon);

	CHECK(std::size(ladders) == 1);
	for (auto i : ladders) {
		CHECK(std::size(i) == 2);
	}
}

TEST_CASE("work -> play") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("work", "play", english_lexicon);

	CHECK(std::size(ladders) == 12);
	for (auto i : ladders) {
		CHECK(std::size(i) == 7);
	}
}

TEST_CASE("awake -> sleep") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("awake", "sleep", english_lexicon);

	CHECK(std::size(ladders) == 2);
	for (auto i : ladders) {
		CHECK(std::size(i) == 10);
	}
}

TEST_CASE("atlases -> cabaret") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("atlases", "cabaret", english_lexicon);

	CHECK(std::size(ladders) == 840);
	for (auto i : ladders) {
		CHECK(std::size(i) == 58);
	}
}
