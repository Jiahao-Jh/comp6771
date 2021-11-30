#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <experimental/iterator>
#include <iostream>
#include <list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what)
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		euclidean_vector();
		explicit euclidean_vector(int);
		euclidean_vector(int, double);
		euclidean_vector(std::vector<double>::const_iterator, std::vector<double>::const_iterator);
		euclidean_vector(std::initializer_list<double>);
		euclidean_vector(euclidean_vector const&);
		euclidean_vector(euclidean_vector&&);
		~euclidean_vector() noexcept;

		auto operator=(euclidean_vector const&) -> euclidean_vector&;
		auto operator=(euclidean_vector&&) noexcept -> euclidean_vector&;
		auto operator[](int) const noexcept -> double;
		auto operator[](int) noexcept -> double&;
		auto operator+() const noexcept -> euclidean_vector;
		auto operator-() -> euclidean_vector;
		auto operator+=(euclidean_vector const&) -> euclidean_vector&;
		auto operator-=(euclidean_vector const&) -> euclidean_vector&;
		auto operator*=(double) -> euclidean_vector&;
		auto operator/=(double) -> euclidean_vector&;
		explicit operator std::vector<double>() const;
		explicit operator std::list<double>() const;

		auto at(int) const -> double;
		auto at(int) -> double&;
		auto dimensions() const noexcept -> int;

		friend auto operator==(euclidean_vector const& v1, euclidean_vector const& v2) -> bool {
			return v1.dimension_ == v2.dimension_
			       && std::equal(v1.magnitude_.get(),
			                     v1.magnitude_.get() + v2.dimension_,
			                     v2.magnitude_.get());
		}

		friend auto operator!=(euclidean_vector const& v1, euclidean_vector const& v2) -> bool {
			return !(v1 == v2);
		}

		friend auto operator+(euclidean_vector const& v1, euclidean_vector const& v2)
		   -> euclidean_vector {
			auto v3 = v1;
			return v3 += v2;
		}

		friend auto operator-(euclidean_vector const& v1, euclidean_vector const& v2)
		   -> euclidean_vector {
			auto v3 = v1;
			return v3 -= v2;
		}

		friend auto operator*(euclidean_vector const& v1, double scalar) -> euclidean_vector {
			auto v2 = v1;
			v2 *= scalar;
			return v2;
		}

		friend auto operator/(euclidean_vector const& v1, double scalar) -> euclidean_vector {
			auto v2 = v1;
			v2 /= scalar;
			return v2;
		}

		friend auto operator<<(std::ostream& out, euclidean_vector const& v1) -> std::ostream& {
			out << '[';
			std::copy(v1.magnitude_.get(),
			          v1.magnitude_.get() + v1.dimension_,
			          std::experimental::make_ostream_joiner(out, " "));
			out << ']';
			return out;
		}

		friend auto euclidean_norm(euclidean_vector const& v) -> double;
		friend auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double;

	private:
		// ass2 spec requires we use double[]
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitude_;
		int dimension_;
		std::unique_ptr<double> e_norm = std::make_unique<double>(-1);

		auto get_e_norm() const noexcept -> double {
			return *this->e_norm;
		}
	};

	auto euclidean_norm(euclidean_vector const& v) -> double;
	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double;
	auto unit(euclidean_vector const& v) -> euclidean_vector;
} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
