#include "comp6771/word_ladder.hpp"
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

auto ifLadder(std::string const& strA, std::string const& strB) -> bool {
	auto flag = false;

	auto iter_a = strA.cbegin();
	auto iter_b = strB.cbegin();

	for (; iter_a != strA.cend();) {
		if (*iter_a != *iter_b && flag == true) {
			return false;
		}
		if (*iter_a != *iter_b) {
			flag = true;
		}
		iter_a++;
		iter_b++;
	}

	return true;
}

// auto ifLadder(std::string const strA, std::string const strB) -> bool {
// 	auto flag = false;
// 	auto length = strA.size();

// 	unsigned long iter_a = 0;
// 	unsigned long iter_b = 0;

// 	for (; iter_a <length;) {
// 		if (strA[iter_a] != strB[iter_b] && flag == true) {
// 			return false;
// 		}
// 		if (strA[iter_a] != strB[iter_b]) {
// 			flag = true;
// 		}
// 		iter_a++;
// 		iter_b++;
// 	}

// 	return true;
// }

auto constructGraph(std::string const from, std::unordered_set<std::string> lexicon)
   -> std::unordered_map<std::string, std::vector<std::string>> {
	// use bfs to constructGraph
	auto graph = std::unordered_map<std::string, std::vector<std::string>>{};
	auto queue = std::queue<std::string>{};
	auto expanded_node = std::unordered_set<std::string>{};

	queue.push(from);
	lexicon.erase(from);

	while (!queue.empty()) {
		// loop layer by layer
		for (auto x = queue.size(); x > 0; x--) {
			auto tmp_string = queue.front();
			queue.pop();

			for (auto i = lexicon.cbegin(); i != lexicon.cend(); i++) {
				if (ifLadder(tmp_string, *i)) {
					// pushback if exist
					// create new one and pushback if not exist
					graph[tmp_string].push_back(*i);

					if (!expanded_node.contains(*i)) {
						expanded_node.insert(*i);
						queue.push(*i);
					}
				}
			}
		}

		// delete last layer expanded_node from lexicon
		//
		for (auto i = expanded_node.cbegin(); i != expanded_node.cend(); i++) {
			lexicon.erase(*i);
		}
		expanded_node.clear();
	}
	return graph;
}

auto findPaths(std::string const from,
               std::string const to,
               std::unordered_map<std::string, std::vector<std::string>> const graph)
   -> std::vector<std::vector<std::string>> {
	auto paths = std::vector<std::vector<std::string>>{};
	auto queue = std::queue<std::vector<std::string>>{};
	// use bfs to find paths
	queue.push({from});
	while (!queue.empty()) {
		auto path = queue.front();
		queue.pop();

		auto const& tmp_string = path.back();

		if (tmp_string == to) {
			paths.push_back(path);
		}

		if (graph.find(tmp_string) != graph.end()) {
			for (auto const& i : graph.find(tmp_string)->second) {
				auto newpath = std::vector<std::string>(path);
				newpath.push_back(i);
				queue.push(newpath);
			}
		}
	}
	return paths;
}

namespace word_ladder {
	auto generate(std::string const& from,
	              std::string const& to,
	              std::unordered_set<std::string> const& lexicon)
	   -> std::vector<std::vector<std::string>> {
		auto const word_length = from.size();
		auto tmp_lexicon = std::unordered_set<std::string>{};
		auto const diff_length = [word_length](auto const x) { return x.size() == word_length; };

		// only copy the word with same length
		std::copy_if(lexicon.begin(),
		             lexicon.end(),
		             std::inserter(tmp_lexicon, tmp_lexicon.begin()),
		             diff_length);

		auto const& graph = constructGraph(from, tmp_lexicon);
		auto paths = findPaths(from, to, graph);

		sort(paths.begin(), paths.end());

		return paths;
	}
} // namespace word_ladder
