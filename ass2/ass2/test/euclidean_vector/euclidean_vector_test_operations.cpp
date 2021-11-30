// I decided to test friends function (section 3 in spec) in this file.

// I use std::vector, c style for loop, at and dimensions to cheack the result is correct after each
// operation.

// I chose to make most of my variable const, except those are meant to be mutated
#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <sstream>

// dimension 0 test
TEST_CASE("Copy Assignment") {
	auto const v1 = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};

	auto const a1 = comp6771::euclidean_vector(v1.begin(), v1.end());
	auto const a2 = comp6771::euclidean_vector(0);

	auto const a3 = a1;

	CHECK(a3.dimensions() == 5);
	CHECK(a1.dimensions() == 5);

	for (int i = 0; i < static_cast<int>(v1.size()); i++) {
		CHECK(a1.at(i) == a3.at(i));
		CHECK(a1.at(i) == v1.at(static_cast<std::size_t>(i)));
		CHECK(a3.at(i) == v1.at(static_cast<std::size_t>(i)));
	}

	auto const a4 = a2;

	CHECK(a4.dimensions() == 0);
	CHECK(a2.dimensions() == 0);
}

TEST_CASE("Move Assignment") {
	auto const v = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto a1 = comp6771::euclidean_vector(v.begin(), v.end());

	auto const a2 = std::move(a1);

	CHECK(a1.dimensions() == 0);
	CHECK(a2.dimensions() == 5);

	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		CHECK_THROWS(a1.at(i) == a2.at(i));
		CHECK(a2.at(i) == v.at(static_cast<std::size_t>(i)));
	}
}

TEST_CASE("Subscript operator (const version)") {
	auto const v = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto const a1 = comp6771::euclidean_vector(v.begin(), v.end());

	CHECK(a1.dimensions() == 5);

	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		CHECK(a1[i] == v[static_cast<std::size_t>(i)]);
	}

	CHECK(a1.dimensions() == 5);
}

TEST_CASE("Subscript operator (non-const version)") {
	auto const v = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto a1 = comp6771::euclidean_vector(v.begin(), v.end());

	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		CHECK(a1[i] == v[static_cast<std::size_t>(i)]);
		a1[i] = 0.0;
	}

	CHECK(a1.dimensions() == 5);

	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		CHECK(a1[i] == 0);
	}
}

TEST_CASE("Unary plus operator") {
	auto const v = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto const a1 = comp6771::euclidean_vector(v.begin(), v.end());
	auto const a2 = comp6771::euclidean_vector(0);

	+a1;
	+a2;

	CHECK(a1.dimensions() == 5);
	CHECK(a2.dimensions() == 0);

	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		CHECK(a1.at(i) == v.at(static_cast<std::size_t>(i)));
	}
}

TEST_CASE("Negation operator") {
	auto const v = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto a1 = comp6771::euclidean_vector(v.begin(), v.end());
	auto a2 = comp6771::euclidean_vector(0);

	-a1;
	-a2;

	CHECK(a1.dimensions() == 5);
	CHECK(a2.dimensions() == 0);

	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		CHECK(a1.at(i) == -(v.at(static_cast<std::size_t>(i))));
	}
}

TEST_CASE("Compound Addition operator") {
	auto const v = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto a1 = comp6771::euclidean_vector(v.begin(), v.end());
	auto const a2 = comp6771::euclidean_vector(v.begin(), v.end());
	auto const a3 = comp6771::euclidean_vector(5);
	auto a4 = comp6771::euclidean_vector(0);

	a1 += a2;

	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		CHECK(Approx(a1.at(i)) == 2 * v.at(static_cast<std::size_t>(i)));
		CHECK(a2.at(i) == v.at(static_cast<std::size_t>(i)));
	}

	a1 += a1;

	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		CHECK(Approx(a1.at(i)) == 4 * v.at(static_cast<std::size_t>(i)));
	}

	a1 += a3;

	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		CHECK(Approx(a1.at(i)) == 4 * v.at(static_cast<std::size_t>(i)));
		CHECK(a3.at(i) == 0.0);
	}

	CHECK(a1.dimensions() == 5);
	CHECK(a2.dimensions() == 5);
	CHECK(a3.dimensions() == 5);

	CHECK(a4.dimensions() == 0);

	a4 += a4;

	CHECK(a4.dimensions() == 0);

	CHECK_THROWS_WITH(a1 += a4, "Dimensions of LHS(5) and RHS(0) do not match");
}

TEST_CASE("Compound Subtraction operator") {
	auto const v = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto const v1 = std::vector<double>{-1, -2, -3, -4, 5};
	auto a1 = comp6771::euclidean_vector(v.begin(), v.end());
	auto const a2 = comp6771::euclidean_vector(v.begin(), v.end());
	auto const a3 = comp6771::euclidean_vector{-1, -2, -3, -4, 5};
	auto a4 = comp6771::euclidean_vector(0);

	a1 -= a2;

	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		CHECK(a1.at(i) == 0);
		CHECK(a2.at(i) == v.at(static_cast<std::size_t>(i)));
	}

	a1 -= a1;

	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		CHECK(a1.at(i) == 0);
	}

	a1 -= a3;

	for (int i = 0; i < static_cast<int>(v1.size()); i++) {
		CHECK(a1.at(i) == -v1.at(static_cast<std::size_t>(i)));
		CHECK(a3.at(i) == v1.at(static_cast<std::size_t>(i)));
	}

	CHECK(a1.dimensions() == 5);
	CHECK(a2.dimensions() == 5);
	CHECK(a3.dimensions() == 5);

	CHECK(a4.dimensions() == 0);

	a4 -= a4;

	CHECK(a4.dimensions() == 0);

	CHECK_THROWS_WITH(a1 -= a4, "Dimensions of LHS(5) and RHS(0) do not match");
}

TEST_CASE("Compound Multiplication operator") {
	auto const v = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto a1 = comp6771::euclidean_vector(v.begin(), v.end());
	auto a2 = comp6771::euclidean_vector(0);

	a1 *= 2;

	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		CHECK(Approx(a1.at(i)) == 2 * v.at(static_cast<std::size_t>(i)));
	}

	a1 *= 10.1;

	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		CHECK(Approx(a1.at(i)) == 2 * 10.1 * v.at(static_cast<std::size_t>(i)));
	}

	a1 *= 0;

	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		CHECK(a1.at(i) == 0);
	}

	CHECK(a2.dimensions() == 0);

	a2 *= 89;

	CHECK(a2.dimensions() == 0);
}

TEST_CASE("Compound Division operator") {
	auto const v = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto a1 = comp6771::euclidean_vector(v.begin(), v.end());
	auto a2 = comp6771::euclidean_vector(0);

	a1 /= 2;

	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		CHECK(Approx(a1.at(i)) == v.at(static_cast<std::size_t>(i)) / 2);
	}

	a1 /= 10.1;

	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		CHECK(Approx(a1.at(i)) == (v.at(static_cast<std::size_t>(i)) / 2) / 10.1);
	}

	CHECK(a2.dimensions() == 0);
	a2 /= 76;
	CHECK(a2.dimensions() == 0);

	CHECK_THROWS_WITH(a1 /= 0, "Invalid vector division by 0");
}

TEST_CASE("Vector Type Conversion") {
	auto const v1 = std::vector<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto const a1 = comp6771::euclidean_vector(v1.begin(), v1.end());
	auto const a2 = comp6771::euclidean_vector(v1.begin(), v1.end());

	auto const v2 = static_cast<std::vector<double>>(a1);
	auto const v3 = static_cast<std::vector<double>>(a2);

	CHECK(v1 == v2);
	CHECK(v1 == v3);

	CHECK(a1.dimensions() == 5);
	CHECK(a2.dimensions() == 5);
	for (int i = 0; i < static_cast<int>(v1.size()); i++) {
		CHECK(a1.at(i) == v1.at(static_cast<std::size_t>(i)));
		CHECK(a2.at(i) == v1.at(static_cast<std::size_t>(i)));
	}
}

TEST_CASE("List Type Conversion") {
	auto v1 = std::list<double>{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto const a1 = comp6771::euclidean_vector{3.14, -2.189, 46.579, 1234.5678, 0.0};
	auto const a2 = comp6771::euclidean_vector{3.14, -2.189, 46.579, 1234.5678, 0.0};

	auto const v2 = static_cast<std::list<double>>(a1);
	auto const v3 = static_cast<std::list<double>>(a2);

	CHECK(v1 == v2);
	CHECK(v1 == v3);

	CHECK(a1.dimensions() == 5);
	CHECK(a2.dimensions() == 5);

	for (int i = 0; i < static_cast<int>(v1.size()); i++) {
		CHECK(a1.at(i) == v1.front());
		CHECK(a2.at(i) == v1.front());
		v1.pop_front();
	}
}
