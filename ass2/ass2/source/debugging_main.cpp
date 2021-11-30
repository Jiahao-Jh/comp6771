#include "comp6771/euclidean_vector.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

auto main() -> int {
	// auto a = comp6771::euclidean_vector(3,3.0);
	// for (int i = 0; i < 3; i++){
	//     std::cout << a.at(i) << "\n";
	// }

	// auto a1 = comp6771::euclidean_vector{3.14,-2.189,46.579,1234.5678,0.0};

	// std::cout << a1<< "\n";

	// double a = 1234.5678;
	// std::cout << a << "\n";

	auto a2 = comp6771::euclidean_vector{8989, 354.5456, 5647.005};
	// double n = comp6771::euclidean_norm(a);
	// std::cout << n << "\n";
	// n = comp6771::euclidean_norm(a);
	auto n = comp6771::euclidean_norm(a2);
	std::cout << n << "\n";

	std::cout << comp6771::unit(a2) << "\n";
	std::cout << comp6771::dot(a2, a2) << "\n";
}