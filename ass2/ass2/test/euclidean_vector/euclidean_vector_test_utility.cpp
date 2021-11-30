// I decided to test utility functions (section 6 in spec) in this file.

// I use c style for loop, at and dimensions to check the result is correct after each
// operation. and for utility function, check their parameters's content don't changes

// I chose to make all my variable const since utility funcitons don't change their parameters's
// content
#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <numeric>
#include <sstream>

TEST_CASE("Euclidean Norm") {
	auto const a1 = comp6771::euclidean_vector(0);
	auto const a2 = comp6771::euclidean_vector{8989, 354.5456, 5647.005};
	auto const a3 = comp6771::euclidean_vector{8989.01};

	CHECK(comp6771::euclidean_norm(a2)
	      == Approx(std::sqrt(8989 * 8989 + 354.5456 * 354.5456 + 5647.005 * 5647.005)));
	CHECK(comp6771::euclidean_norm(a2)
	      == Approx(std::sqrt(8989 * 8989 + 354.5456 * 354.5456 + 5647.005 * 5647.005)));

	CHECK(comp6771::euclidean_norm(a3) == Approx(8989.01));
	CHECK(comp6771::euclidean_norm(a3) == Approx(8989.01));

	CHECK(comp6771::euclidean_norm(a1) == 0);
	CHECK(comp6771::euclidean_norm(a1) == 0);

	CHECK(a1.dimensions() == 0);
	CHECK(a2.dimensions() == 3);
	CHECK(a3.dimensions() == 1);

	CHECK(a2.at(0) == 8989);
	CHECK(a2.at(1) == 354.5456);
	CHECK(a2.at(2) == 5647.005);

	CHECK(a3.at(0) == 8989.01);
}

TEST_CASE("Unit") {
	auto const a1 = comp6771::euclidean_vector(0);
	auto const a2 = comp6771::euclidean_vector();
	auto const a3 = comp6771::euclidean_vector{8989, 354.5456, 5647.005};
	auto const a4 = comp6771::euclidean_vector{8989.01};

	CHECK_THROWS_WITH(comp6771::unit(a1),
	                  "euclidean_vector with no dimensions does not have a unit vector");

	CHECK_THROWS_WITH(comp6771::unit(a2),
	                  "euclidean_vector with zero euclidean normal does not have a unit vector");

	CHECK(comp6771::unit(a4).dimensions() == 1);
	CHECK(comp6771::unit(a4).at(0) == 1);

	CHECK(comp6771::unit(a3).dimensions() == 3);
	CHECK(comp6771::unit(a3).at(0)
	      == Approx(8989 / std::sqrt(8989 * 8989 + 354.5456 * 354.5456 + 5647.005 * 5647.005)));
	CHECK(comp6771::unit(a3).at(1)
	      == Approx(354.5456 / std::sqrt(8989 * 8989 + 354.5456 * 354.5456 + 5647.005 * 5647.005)));
	CHECK(comp6771::unit(a3).at(2)
	      == Approx(5647.005 / std::sqrt(8989 * 8989 + 354.5456 * 354.5456 + 5647.005 * 5647.005)));

	CHECK(a1.dimensions() == 0);
	CHECK(a2.dimensions() == 1);
	CHECK(a3.dimensions() == 3);
	CHECK(a4.dimensions() == 1);

	CHECK(a2.at(0) == 0);

	CHECK(a3.at(0) == 8989);
	CHECK(a3.at(1) == 354.5456);
	CHECK(a3.at(2) == 5647.005);

	CHECK(a4.at(0) == 8989.01);
}

TEST_CASE("Dot") {
	auto const a1 = comp6771::euclidean_vector(0);
	auto const a2 = comp6771::euclidean_vector();
	auto const a3 = comp6771::euclidean_vector{8989, 354.5456, 5647.005};
	auto const a4 = comp6771::euclidean_vector{8989.01};
	auto const a5 = comp6771::euclidean_vector{8989.01, 0, -1};
	auto const a6 = comp6771::euclidean_vector(3);

	CHECK(comp6771::dot(a1, a1) == 0);
	CHECK_THROWS_WITH(comp6771::dot(a1, a2), "Dimensions of LHS(0) and RHS(1) do not match");

	CHECK(comp6771::dot(a2, a2) == 0);

	CHECK(comp6771::dot(a4, a4) == Approx(8989.01 * 8989.01));

	CHECK(comp6771::dot(a3, a3) == Approx(8989 * 8989 + 354.5456 * 354.5456 + 5647.005 * 5647.005));

	CHECK(comp6771::dot(a3, a5) == Approx(8989 * 8989.01 + 0 + -5647.005));

	CHECK(comp6771::dot(a3, a6) == 0);

	CHECK(a1.dimensions() == 0);
	CHECK(a2.dimensions() == 1);
	CHECK(a3.dimensions() == 3);
	CHECK(a4.dimensions() == 1);
	CHECK(a5.dimensions() == 3);
	CHECK(a6.dimensions() == 3);

	CHECK(a2.at(0) == 0);

	CHECK(a3.at(0) == 8989);
	CHECK(a3.at(1) == 354.5456);
	CHECK(a3.at(2) == 5647.005);

	CHECK(a4.at(0) == 8989.01);

	CHECK(a5.at(0) == 8989.01);
	CHECK(a5.at(1) == 0);
	CHECK(a5.at(2) == -1);

	CHECK(a6.at(0) == 0);
	CHECK(a6.at(1) == 0);
	CHECK(a6.at(2) == 0);
}