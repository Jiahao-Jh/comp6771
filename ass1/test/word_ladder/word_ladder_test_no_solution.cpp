// test for no solution cases
// like normal no solution case and empty string
#include "comp6771/word_ladder.hpp"

#include <string>
#include <vector>

#include "catch2/catch.hpp"

TEST_CASE("abjure -> tokens") {
	auto const english_lexicon = ::word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("abjure", "tokens", english_lexicon);

	CHECK(std::size(ladders) == 0);
	CHECK(ladders.empty());
}

TEST_CASE("airplane -> tricycle") {
	auto const english_lexicon = ::word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("airplane", "tricycle", english_lexicon);

	CHECK(std::size(ladders) == 0);
	CHECK(ladders.empty());
}

TEST_CASE("toit -> toits") {
	auto const english_lexicon = ::word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("toit", "toits", english_lexicon);

	CHECK(std::size(ladders) == 0);
	CHECK(ladders.empty());
}

TEST_CASE("\"\" -> toits") {
	auto const english_lexicon = ::word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("", "toits", english_lexicon);

	CHECK(std::size(ladders) == 0);
	CHECK(ladders.empty());
}

TEST_CASE("toit -> \"\"") {
	auto const english_lexicon = ::word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("", "toits", english_lexicon);

	CHECK(std::size(ladders) == 0);
	CHECK(ladders.empty());
}

TEST_CASE("\"\" -> \"\"") {
	auto const english_lexicon = ::word_ladder::read_lexicon("./english.txt");
	auto const ladders = word_ladder::generate("", "", english_lexicon);

	CHECK(std::size(ladders) == 0);
	CHECK(ladders.empty());
}