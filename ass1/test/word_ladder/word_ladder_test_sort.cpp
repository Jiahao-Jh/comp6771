// test if the output is sorted
#include "comp6771/word_ladder.hpp"

#include <string>
#include <vector>

#include "catch2/catch.hpp"

TEST_CASE("sky -> fly") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("sky", "fly", english_lexicon);

	CHECK(std::is_sorted(ladders.begin(), ladders.end()));
}

TEST_CASE("work -> play") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("work", "play", english_lexicon);

	CHECK(std::is_sorted(ladders.begin(), ladders.end()));
}

TEST_CASE("atlases -> cabaret") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("atlases", "cabaret", english_lexicon);

	CHECK(std::is_sorted(ladders.begin(), ladders.end()));
}
