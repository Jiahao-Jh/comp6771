// I decided to test constructor, at member function and dimensions member function (section 1 and 4
// in spec)in this file. I use at and dimensions to get access to the content of euclidean_vector
// and use that to test constructors. This is because at and dimensions is the easier way compare to
// subscript to get asscess to the contents and testing constructor require test the correctness of
// the content.

// I use std::vector, c style for loop, at and dimensions to cheack the result is correct after each
// operation.

// I chose to make most of my variable const, since const variable is more strict than the non-const
// variable. Except some variable in test_case(at member function (non const version)) and
// test_case(move constructor) cause they are used to test mutability
#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>
#include <vector>

TEST_CASE("Constructors") {
	auto const v = std::vector<double>{1.0, 2.0, 3.0, 4.9};
	auto const a1 = comp6771::euclidean_vector();
	auto const a2 = comp6771::euclidean_vector(90);
	auto const a3 = comp6771::euclidean_vector(56, 9.8);
	auto const a4 = comp6771::euclidean_vector(v.begin(), v.end());
	auto const a5 = comp6771::euclidean_vector{9.9};
	auto const a6 = comp6771::euclidean_vector(a1);
	auto const a7 = comp6771::euclidean_vector(std::move(a1));
}

TEST_CASE("Default Constructor") {
	auto const a1 = comp6771::euclidean_vector();
	auto const a2 = comp6771::euclidean_vector();

	CHECK(a1.at(0) == 0.0);
	CHECK(a1.dimensions() == 1);
	CHECK(a2.at(0) == 0.0);
	CHECK(a2.dimensions() == 1);

	CHECK_THROWS_WITH(a1.at(1), "Index 1 is not valid for this euclidean_vector object");
	CHECK_THROWS_WITH(a2.at(1), "Index 1 is not valid for this euclidean_vector object");
}

TEST_CASE("Single-argument Constructor") {
	auto const num = 70;
	auto const a1 = comp6771::euclidean_vector(1);
	auto const a2 = comp6771::euclidean_vector(num);

	CHECK(a1.at(0) == 0.0);
	CHECK(a1.dimensions() == 1);
	CHECK(a2.at(0) == 0.0);
	CHECK(a2.at(69) == 0.0);
	CHECK(a2.dimensions() == 70);

	CHECK_THROWS_WITH(a1.at(1), "Index 1 is not valid for this euclidean_vector object");
	CHECK_THROWS_WITH(a2.at(70), "Index 70 is not valid for this euclidean_vector object");
}

TEST_CASE("Two-argument Constructor (int , double)") {
	auto const num = 70;
	auto const num1 = 1.0;
	auto const a1 = comp6771::euclidean_vector(1, 1.0);
	auto const a2 = comp6771::euclidean_vector(num, num1);

	CHECK(a1.at(0) == 1.0);
	CHECK(a1.dimensions() == 1);
	CHECK(a2.at(0) == 1.0);
	CHECK(a2.at(69) == 1.0);
	CHECK(a2.dimensions() == 70);

	CHECK_THROWS_WITH(a1.at(1), "Index 1 is not valid for this euclidean_vector object");
	CHECK_THROWS_WITH(a2.at(70), "Index 70 is not valid for this euclidean_vector object");
}

TEST_CASE("Two-argument Constructor (const_iterator , const_iterator)") {
	auto const v = std::vector<double>{1.0, 2.0, 3.0, 4.9};
	auto const v1 = std::vector<double>{};

	auto const a1 = comp6771::euclidean_vector(v.begin(), v.end());
	auto const a2 = comp6771::euclidean_vector(v.cbegin(), v.cend());
	auto const a3 = comp6771::euclidean_vector(v1.begin(), v1.end());

	CHECK(a1.dimensions() == static_cast<int>(v.size()));
	CHECK(a2.dimensions() == static_cast<int>(v.size()));
	CHECK(a3.dimensions() == 0);

	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		CHECK(a1.at(i) == v.at(static_cast<std::size_t>(i)));
		CHECK(a2.at(i) == v.at(static_cast<std::size_t>(i)));
	}
}

TEST_CASE("Single-argument Constructor (initializer_list)") {
	auto const a1 = comp6771::euclidean_vector{1.0, 2.0, 3.0, 4.9};
	CHECK(a1.at(0) == 1.0);
	CHECK(a1.at(3) == 4.9);
	CHECK(a1.dimensions() == 4);

	CHECK_THROWS_WITH(a1.at(4), "Index 4 is not valid for this euclidean_vector object");
}

TEST_CASE("Copy Constructor") {
	auto const v = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto const a1 = comp6771::euclidean_vector(v.begin(), v.end());

	auto const a2 = comp6771::euclidean_vector(a1);

	CHECK(a1.dimensions() == static_cast<int>(v.size()));
	CHECK(a2.dimensions() == static_cast<int>(v.size()));

	for (int i = 0; i < 4; i++) {
		CHECK(a1.at(i) == a2.at(i));
		CHECK(a1.at(i) == v.at(static_cast<std::size_t>(i)));
	}
}

TEST_CASE("Move Constructor") {
	auto const v = std::vector<double>{1.0, 2.0, 3.0, 4.9};
	auto a1 = comp6771::euclidean_vector(v.begin(), v.end());

	auto const a2 = comp6771::euclidean_vector(std::move(a1));

	CHECK(a1.dimensions() == 0);
	CHECK(a2.dimensions() == static_cast<int>(v.size()));

	for (int i = 0; i < 4; i++) {
		CHECK_THROWS_WITH(
		   a1.at(i),
		   "Index " + std::to_string(i) + " is not valid for this euclidean_vector object");
		CHECK(a2.at(i) == v.at(static_cast<std::size_t>(i)));
	}
}

TEST_CASE("at member function (non const version)") {
	auto a1 = comp6771::euclidean_vector{1.0, 2.0, 3.0, 4.9};

	a1.at(0) = 99;
	a1.at(0) = 99;

	a1.at(2) = 99;
	a1.at(3) = 99;

	CHECK(a1.at(0) == 99);
	CHECK(a1.at(1) == 2);
	CHECK(a1.at(2) == 99);
	CHECK(a1.at(3) == 99);
}