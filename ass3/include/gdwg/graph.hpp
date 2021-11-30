#ifndef GDWG_GRAPH_HPP
#define GDWG_GRAPH_HPP

#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

// TODO: Make this graph generic
//       ... this won't just compile
//       straight away

namespace gdwg {
	template<typename N, typename E>
	class graph {
	public:
		class iterator;
		// Iterator access

		[[nodiscard]] auto begin() const -> iterator {
			return iterator(graph_, true);
		}
		[[nodiscard]] auto end() const -> iterator {
			return iterator(graph_, false);
		}

		// Constructors
		graph() noexcept
		: graph_{std::map<std::unique_ptr<N>, std::set<Edges>, nodeCompare>()} {}

		graph(std::initializer_list<N> il) {
			std::for_each(il.begin(), il.end(), [this](N const& i) { insert_node(i); });
		}

		template<typename InputIt>
		graph(InputIt first, InputIt last) {
			std::for_each(first, last, [this](N const& i) { insert_node(i); });
		}

		graph(graph&& other) noexcept
		: graph_{std::exchange(other.graph_,
		                       std::map<std::unique_ptr<N>, std::set<Edges>, nodeCompare>())} {}

		auto operator=(graph&& other) noexcept -> graph& {
			std::swap(graph_, other.graph_);
			other.graph_ = std::map<std::unique_ptr<N>, std::set<Edges>, nodeCompare>();
			return *this;
		}

		graph(graph const& other) {
			for (auto const& i : other.graph_) {
				graph_.emplace(std::make_unique<N>(*(i.first)), i.second);
			}
		}

		auto operator=(graph const& other) -> graph& {
			auto copy = graph(other);
			std::swap(copy, *this);
			return *this;
		}

		// Modifiers
		auto insert_node(N const& value) -> bool {
			auto const& found_node = find_node(value);

			if (found_node == graph_.end()) {
				graph_.emplace(std::make_unique<N>(value), std::set<Edges>());
				return true;
			}
			return false;
		}

		auto insert_edge(N const& src, N const& dst, E const& weight) -> bool {
			if (is_node(src) && is_node(dst)) {
				auto const& found_src = find_node(src);
				auto const& found_dst = find_node(dst);

				auto const& set_edges = found_dst->second;

				if (std::find_if(
				       set_edges.begin(),
				       set_edges.end(),
				       [dst, weight](Edges const& i) { return *(i.to) == dst && *(i.weight) == weight; })
				    == set_edges.end())
				{
					auto a = Edges();
					a.to = found_dst->first.get();
					a.weight = std::make_unique<E>(weight);

					found_src->second.insert(std::move(a));

					return true;
				}

				return false;
			}
			throw std::runtime_error("Cannot call gdwg::graph<N, E>::insert_edge when either src or "
			                         "dst node does not exist");
		}

		auto clear() noexcept -> void {
			graph_.clear();
		}

		auto replace_node(N const& old_data, N const& new_data) -> bool {
			if (is_node(new_data)) {
				return false;
			}
			if (!is_node(old_data)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::replace_node on a node that "
				                         "doesn't exist");
			}

			insert_node(new_data);

			for (auto const& i : graph_) {
				if (*(i.first) == old_data) {
					for (auto const& x : i.second) {
						if (*(x.to) == old_data) {
							insert_edge(new_data, new_data, *(x.weight));
						}
						else {
							insert_edge(new_data, *(x.to), *(x.weight));
						}
					}
				}
				else {
					for (auto const& x : i.second) {
						if (*(x.to) == old_data) {
							insert_edge(*(i.first), new_data, *(x.weight));
						}
					}
				}
			}
			erase_node(old_data);

			return true;
		}

		auto merge_replace_node(N const& old_data, N const& new_data) -> void {
			if (!is_node(old_data) || !is_node(new_data)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::merge_replace_node on old or "
				                         "new data if they don't exist in the graph");
			}

			for (auto const& i : graph_) {
				if (*(i.first) == old_data) {
					for (auto const& x : i.second) {
						if (*(x.to) == old_data) {
							insert_edge(new_data, new_data, *(x.weight));
						}
						else {
							insert_edge(new_data, *(x.to), *(x.weight));
						}
					}
				}
				else {
					for (auto const& x : i.second) {
						if (*(x.to) == old_data) {
							insert_edge(*(i.first), new_data, *(x.weight));
						}
					}
				}
			}

			erase_node(old_data);
		}

		auto erase_node(N const& value) -> bool {
			if (!is_node(value)) {
				return false;
			}
			auto const& to_be_earse = find_node(value);

			for (auto& i : graph_) {
				std::erase_if(i.second, [value](auto const& x) { return *(x.to) == value; });
			}
			graph_.erase(to_be_earse);
			return true;
		}

		auto erase_edge(N const& src, N const& dst, E const& weight) -> bool {
			if (!is_node(src) || !is_node(dst)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::erase_edge on src or dst if "
				                         "they don't exist in the graph");
			}
			auto i = find_node(src);
			auto const& e =
			   std::find_if(i->second.begin(), i->second.end(), [dst, weight](Edges const& i) {
				   return *(i.to) == dst && *(i.weight) == weight;
			   });
			if (e == i->second.end()) {
				return false;
			}
			i->second.erase(e);
			return true;
		}

		auto erase_edge(iterator i) -> iterator;
		auto erase_edge(iterator i, iterator s) -> iterator;

		// Accessors
		[[nodiscard]] auto is_node(N const& value) const -> bool {
			auto const& found_node = find_node(value);
			if (found_node != graph_.end()) {
				return true;
			}
			return false;
		}

		[[nodiscard]] auto is_connected(N const& src, N const& dst) const -> bool {
			if (!is_node(src) || !is_node(dst)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::is_connected if src or dst "
				                         "node don't exist in the graph");
			}
			auto const& found_node = find_node(src);

			if (found_node != graph_.end()) {
				auto const& set_edges = found_node->second;
				std::cout << set_edges.size();
				if (std::find_if(set_edges.begin(),
				                 set_edges.end(),
				                 [dst](Edges const& i) { return *(i.to) == dst; })
				    != set_edges.end())
				{
					return true;
				}
			}
			return false;
		}

		[[nodiscard]] auto empty() const -> bool {
			return graph_.empty();
		}

		[[nodiscard]] auto nodes() const -> std::vector<N> {
			auto res = std::vector<N>{};
			for_each(graph_.begin(), graph_.end(), [&res](auto const& i) { res.push_back(*(i.first)); });
			return res;
		}

		[[nodiscard]] auto weights(N const& src, N const& dst) const -> std::vector<E> {
			if (!is_node(src) || !is_node(dst)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::weights if src or dst node "
				                         "don't exist in the graph");
			}
			auto res = std::vector<E>{};
			auto const& i = find_node(src);
			for (auto x : i->second) {
				if (*(x.to) == dst) {
					res.push_back(*(x.weight));
				}
			}
			return res;
		}

		[[nodiscard]] auto find(N const& src, N const& dst, E const& weight) const -> iterator {
			auto const& i = find_node(src);
			if (i == graph_.end()) {
				return end();
			}
			auto const& e =
			   std::find_if(i->second.begin(), i->second.end(), [dst, weight](Edges const& i) {
				   return *(i.to) == dst && *(i.weight) == weight;
			   });

			if (e == i->second.end()) {
				return end();
			}
			return iterator(i, e, graph_.begin(), graph_.end());
		}

		[[nodiscard]] auto connections(N const& src) const -> std::vector<N> {
			auto res = std::vector<N>{};
			if (!is_node(src)) {
				throw std::runtime_error("Cannot call gdwg::graph<N, E>::connections if src doesn't "
				                         "exist in the graph");
			}
			auto const i = find_node(src);
			N prev;
			for (auto x = i->second.begin(); x != i->second.end(); x++) {
				if (x == i->second.begin()) {
					prev = *(x->to);
					res.push_back(*(x->to));
				}
				else if (*(x->to) != prev) {
					prev = *(x->to);
					res.push_back(*(x->to));
				}
			}

			return res;
		}

		// Comparisons

		// TODO
		[[nodiscard]] auto operator==(graph const& other) const -> bool {
			if (other.graph_.size() != graph_.size()) {
				return false;
			}

			auto y = other.graph_.begin();
			for (auto const& i : graph_) {
				if (*(i.first) != *(y->first)) {
					return false;
				}

				if (i.second.size() != y->second.size()) {
					return false;
				}

				auto set_y = y->second.begin();
				for (auto const& set_i : i.second) {
					if (*(set_i.to) != *(set_y->to)) {
						return false;
					}
					if (*(set_i.weight) != *(set_y->weight)) {
						return false;
					}
					set_y++;
				}
				y++;
			}
			return true;
		}

		// Extractor
		friend auto operator<<(std::ostream& os, graph const& g) -> std::ostream& {
			for (auto const& i : g.graph_) {
				os << *(i.first) << " ";
				os << "(\n";
				for (auto const& x : i.second) {
					os << "  " << *(x.to) << " | " << *(x.weight) << "\n";
				}
				os << ")\n";
			}

			return os;
		}

		struct value_type {
			N from;
			N to;
			E weight;
		};

		// Your member functions go here
	private:
		// struct edges contain observer pointer of des node, and edge weight
		// implemented copy constructor and overload operator<
		struct Edges {
			N* to;
			std::unique_ptr<E> weight;

			Edges() {}

			Edges(Edges const& other)
			: to{other.to}
			, weight{std::make_unique<E>(*(other.weight))} {}

			auto operator<(const Edges& rhs) const -> bool {
				if (*to != *rhs.to) {
					return *to < *rhs.to;
				}
				return *weight < *(rhs.weight);
			}
		};

		struct nodeCompare {
			bool operator()(const std::unique_ptr<N>& lhs, const std::unique_ptr<N>& rhs) const {
				return *lhs < *rhs;
			}
		};

		std::map<std::unique_ptr<N>, std::set<Edges>, nodeCompare> graph_;

		auto find_node(N const& value) const ->
		   typename std::map<std::unique_ptr<N>, std::set<Edges>, nodeCompare>::const_iterator {
			return std::find_if(graph_.begin(), graph_.end(), [&value](auto const& i) {
				return *(i.first) == value;
			});
		}

		auto find_node(N const& value) ->
		   typename std::map<std::unique_ptr<N>, std::set<Edges>, nodeCompare>::iterator {
			return std::find_if(graph_.begin(), graph_.end(), [&value](auto const& i) {
				return *(i.first) == value;
			});
		}
	};

	// Iterator
	template<typename N, typename E>
	class graph<N, E>::iterator {
	public:
		using value_type = graph<N, E>::value_type;
		using reference = value_type;
		using pointer = void;
		using difference_type = std::ptrdiff_t;
		using iterator_category = std::bidirectional_iterator_tag;

		iterator() = default;

		auto operator*() const -> reference {
			auto res = value_type{};
			res.from = *(node_->first);
			res.to = *(edges_->to);
			res.weight = *(edges_->weight);
			return res;
		}

		auto operator++() -> iterator& {
			if (edges_ != node_->second.end()) {
				edges_++;
			}

			if (edges_ == node_->second.end()) {
				node_++;
				if (node_ != node_end_) {
					edges_ = find_next_edge();
				}
			}

			return *this;
		}

		auto operator++(int) -> iterator {
			auto copy{*this};
			++(*this);
			return copy;
		}

		auto operator--() -> iterator& {
			while (node_ == node_end_ || node_->second.empty()) {
				node_--;
				edges_ = node_->second.end();
			}

			if (edges_ == node_->second.begin()) {
				node_--;
				edges_ = find_before_edge();
			}
			edges_--;
			return *this;
		}

		auto operator--(int) -> iterator {
			auto copy{*this};
			--(*this);
			return copy;
		}

		auto operator==(iterator const& other) const -> bool {
			// if one of the comparison is end, only compare the node_
			if (node_ == node_end_ || other.node_ == other.node_end_) {
				return node_ == other.node_;
			}
			else {
				return node_ == other.node_ && edges_ == other.edges_;
			}
		}

	private:
		explicit iterator(std::map<std::unique_ptr<N>, std::set<Edges>, nodeCompare> const& g, bool b) {
			if (g.begin() == g.end() || b == false) {
				node_ = g.end();
				node_end_ = g.end();
				node_start_ = g.begin();
			}
			else {
				node_ = g.begin();
				node_end_ = g.end();
				node_start_ = g.begin();
				edges_ = find_next_edge();
			}
		}

		iterator(
		   typename std::map<std::unique_ptr<N>, std::set<Edges>, nodeCompare>::const_iterator i,
		   typename std::set<Edges>::iterator e,
		   typename std::map<std::unique_ptr<N>, std::set<Edges>, nodeCompare>::const_iterator i_start,
		   typename std::map<std::unique_ptr<N>, std::set<Edges>, nodeCompare>::const_iterator i_end) noexcept
		: node_{i}
		, node_end_{i_end}
		, node_start_{i_start}
		, edges_{e} {}

		auto find_next_edge() -> typename std::set<Edges>::iterator {
			while (node_ != node_end_ && node_->second.empty()) {
				node_++;
			}
			if (node_ != node_end_) {
				edges_ = node_->second.begin();
			}
			return edges_;
		}

		auto find_before_edge() -> typename std::set<Edges>::iterator {
			while (node_ == node_end_ || node_->second.empty()) {
				node_--;
			}
			edges_ = node_->second.end();
			return edges_;
			// while (node_ != node_start_ && node_->second.empty()){
			// 	node_--;
			// }

			// if (node_ != node_start_){
			// 	edges_ = node_->second.rbegin().base();
			// }
			// return edges_;
		}

		auto erase() -> void {
			const_cast<std::set<Edges>&>(node_->second).erase(edges_);
		}

		// auto remove_constness(std::set<Edges>& s, std::set<Edges>::const_iterator it) -> void{
		// 	s.erase(it).
		// }

		typename std::map<std::unique_ptr<N>, std::set<Edges>, nodeCompare>::const_iterator node_;
		typename std::map<std::unique_ptr<N>, std::set<Edges>, nodeCompare>::const_iterator node_end_;
		typename std::map<std::unique_ptr<N>, std::set<Edges>, nodeCompare>::const_iterator node_start_;
		typename std::set<Edges>::iterator edges_;
		friend class graph;
	};

	template<typename N, typename E>
	auto graph<N, E>::erase_edge(iterator i) -> iterator {
		if (i == end()) {
			return end();
		}
		auto a = i;
		a++;
		i.erase();
		return a;
	}

	template<typename N, typename E>
	auto graph<N, E>::erase_edge(iterator i, iterator s) -> iterator {
		while (i != s) {
			i = erase_edge(i);
		}
		return i;
	}

} // namespace gdwg

#endif // GDWG_GRAPH_HPP
