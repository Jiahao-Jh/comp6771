// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "comp6771/euclidean_vector.hpp"
#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

namespace comp6771 {

	euclidean_vector::euclidean_vector() {
		this->dimension_ = 1;
		this->magnitude_ = std::make_unique<double[]>(1);
	}

	euclidean_vector::euclidean_vector(int number_of_dimensions) {
		this->dimension_ = number_of_dimensions;
		this->magnitude_ = std::make_unique<double[]>(static_cast<std::size_t>(number_of_dimensions));
	}

	euclidean_vector::euclidean_vector(int number_of_dimensions, double initialise_value) {
		this->dimension_ = number_of_dimensions;
		this->magnitude_ = std::make_unique<double[]>(static_cast<std::size_t>(number_of_dimensions));
		std::fill_n(this->magnitude_.get(), number_of_dimensions, initialise_value);
	}

	euclidean_vector::euclidean_vector(std::vector<double>::const_iterator begin,
	                                   std::vector<double>::const_iterator end) {
		this->dimension_ = static_cast<int>(end - begin);
		this->magnitude_ = std::make_unique<double[]>(static_cast<std::size_t>(this->dimension_));
		std::copy_n(begin, this->dimension_, this->magnitude_.get());
	}

	euclidean_vector::euclidean_vector(std::initializer_list<double> list) {
		this->dimension_ = static_cast<int>(list.size());
		this->magnitude_ = std::make_unique<double[]>(static_cast<std::size_t>(this->dimension_));
		std::copy_n(list.begin(), this->dimension_, this->magnitude_.get());
	}

	// Copy constructor
	euclidean_vector::euclidean_vector(euclidean_vector const& orig) {
		this->dimension_ = orig.dimension_;
		this->magnitude_ = std::make_unique<double[]>(static_cast<std::size_t>(orig.dimension_));
		std::copy_n(orig.magnitude_.get(), orig.dimension_, this->magnitude_.get());
	}

	// Move constructor
	euclidean_vector::euclidean_vector(euclidean_vector&& orig) {
		this->dimension_ = std::exchange(orig.dimension_, 0);
		this->magnitude_ = std::exchange(orig.magnitude_, nullptr);
	}

	euclidean_vector::~euclidean_vector() noexcept {}

	// Copy assignment
	auto euclidean_vector::operator=(euclidean_vector const& orig) -> euclidean_vector& {
		auto copy = euclidean_vector(orig);
		std::swap(this->dimension_, copy.dimension_);
		std::swap(this->magnitude_, copy.magnitude_);
		return *this;
	}

	// Move assignment
	auto euclidean_vector::operator=(euclidean_vector&& orig) noexcept -> euclidean_vector& {
		std::swap(this->dimension_, orig.dimension_);
		std::swap(this->magnitude_, orig.magnitude_);
		return *this;
	}

	auto euclidean_vector::operator[](int position) const noexcept -> double {
		assert(position >= 0 && position < this->dimension_);
		return this->magnitude_[static_cast<std::size_t>(position)];
	}

	auto euclidean_vector::operator[](int position) noexcept -> double& {
		assert(position >= 0 && position < this->dimension_);
		return this->magnitude_[static_cast<std::size_t>(position)];
	}

	auto euclidean_vector::operator+() const noexcept -> euclidean_vector {
		return *this;
	}

	auto euclidean_vector::operator-() -> euclidean_vector {
		std::transform(this->magnitude_.get(),
		               this->magnitude_.get() + this->dimension_,
		               this->magnitude_.get(),
		               std::negate<double>());
		return *this;
	}

	auto euclidean_vector::operator+=(euclidean_vector const& add_vector) -> euclidean_vector& {
		if (this->dimension_ != add_vector.dimension_) {
			auto throw_string = "Dimensions of LHS(" + std::to_string(this->dimension_) + ") and RHS("
			                    + std::to_string(add_vector.dimension_) + ") do not match";
			throw euclidean_vector_error(throw_string);
		}

		std::transform(this->magnitude_.get(),
		               this->magnitude_.get() + this->dimension_,
		               add_vector.magnitude_.get(),
		               this->magnitude_.get(),
		               std::plus<double>());
		return *this;
	}

	auto euclidean_vector::operator-=(euclidean_vector const& add_vector) -> euclidean_vector& {
		if (this->dimension_ != add_vector.dimension_) {
			auto throw_string = "Dimensions of LHS(" + std::to_string(this->dimension_) + ") and RHS("
			                    + std::to_string(add_vector.dimension_) + ") do not match";
			throw euclidean_vector_error(throw_string);
		}

		std::transform(this->magnitude_.get(),
		               this->magnitude_.get() + this->dimension_,
		               add_vector.magnitude_.get(),
		               this->magnitude_.get(),
		               std::minus<double>());
		return *this;
	}

	auto euclidean_vector::operator*=(double scalar) -> euclidean_vector& {
		std::transform(this->magnitude_.get(),
		               this->magnitude_.get() + this->dimension_,
		               this->magnitude_.get(),
		               std::bind(std::multiplies<double>(), std::placeholders::_1, scalar));
		return *this;
	}

	auto euclidean_vector::operator/=(double scalar) -> euclidean_vector& {
		if (scalar == 0) {
			throw euclidean_vector_error("Invalid vector division by 0");
		}
		std::transform(this->magnitude_.get(),
		               this->magnitude_.get() + this->dimension_,
		               this->magnitude_.get(),
		               std::bind(std::divides<double>(), std::placeholders::_1, scalar));
		return *this;
	}
	euclidean_vector::operator std::vector<double>() const {
		return std::vector<double>{this->magnitude_.get(), this->magnitude_.get() + this->dimension_};
	}

	euclidean_vector::operator std::list<double>() const {
		return std::list<double>{this->magnitude_.get(), this->magnitude_.get() + this->dimension_};
	}

	auto euclidean_vector::at(int position) const -> double {
		if (position < 0 || position >= this->dimension_) {
			auto throw_string =
			   "Index " + std::to_string(position) + " is not valid for this euclidean_vector object";
			throw euclidean_vector_error(throw_string);
		}

		return this->magnitude_[static_cast<std::size_t>(position)];
	}

	auto euclidean_vector::at(int position) -> double& {
		if (position < 0 || position >= this->dimension_) {
			auto throw_string =
			   "Index " + std::to_string(position) + " is not valid for this euclidean_vector object";
			throw euclidean_vector_error(throw_string);
		}

		return this->magnitude_[static_cast<std::size_t>(position)];
	}

	auto euclidean_vector::dimensions() const noexcept -> int {
		return dimension_;
	}

	// set up a unique pointer e_norm as cache in private section and default -1
	// get_e_norm return a dereference of e_norm
	// use copy_n to change the e_norm value and avoid const
	auto euclidean_norm(euclidean_vector const& v) -> double {
		if (v.get_e_norm() == -1) {
			auto norm = std::sqrt(std::inner_product(v.magnitude_.get(),
			                                         v.magnitude_.get() + v.dimension_,
			                                         v.magnitude_.get(),
			                                         0.0));
			auto n = std::make_unique<double>(norm);
			std::copy_n(n.get(), 1, v.e_norm.get());
			return norm;
		}
		return v.get_e_norm();
	}

	auto unit(euclidean_vector const& v) -> euclidean_vector {
		if (v.dimensions() == 0) {
			throw euclidean_vector_error("euclidean_vector with no dimensions does not have a unit "
			                             "vector");
		}
		auto norm = euclidean_norm(v);
		if (norm == 0) {
			throw euclidean_vector_error("euclidean_vector with zero euclidean normal does not have a "
			                             "unit vector");
		}
		return v / norm;
	}

	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double {
		if (x.dimension_ != y.dimension_) {
			auto throw_string = "Dimensions of LHS(" + std::to_string(x.dimension_) + ") and RHS("
			                    + std::to_string(y.dimension_) + ") do not match";
			throw euclidean_vector_error(throw_string);
		}
		return std::inner_product(x.magnitude_.get(),
		                          x.magnitude_.get() + x.dimension_,
		                          y.magnitude_.get(),
		                          0.0);
	}

} // namespace comp6771
