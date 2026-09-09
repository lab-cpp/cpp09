#include "PmergeMe.hpp"
#include <algorithm>
#include <cstddef>

template <typename Container>
static void fordJohnsonSort(Container& container) {
	if (container.size() < 2) {
		return ;
	}
	
	typedef typename Container::value_type value_type;
	typedef std::pair<value_type, value_type> value_pair;
	typedef std::vector<value_pair> pair_vector;

	bool hasOdd = (container.size() % 2 != 0);
	value_type oddElement = value_type();
	if (hasOdd) {
		oddElement = container.back();
		container.pop_back();
	}

	pair_vector pairs;
	typename Container::iterator it = container.begin();
	while (it != container.end()) {
		value_type a = *it++;
		value_type b = *it++;

		if (a < b) {
			pairs.push_back(std::make_pair(b, a));
		} else {
			pairs.push_back(std::make_pair(a, b));
		}
	}

	Container mainChain;
	for (size_t i = 0; i < pairs.size(); ++i) {
		mainChain.push_back(pairs[i].first);
	}

	fordJohnsonSort(mainChain);

	pair_vector sortedPairs;
	for (size_t i = 0; i < mainChain.size(); ++i) {
		for (size_t j = 0; j < pairs.size(); ++j) {
			if (pairs[j].first == mainChain[i]) {
				sortedPairs.push_back(pairs[j]);
				pairs.erase(pairs.begin() + j);
				break ;
			}
		}
	}

	pairs = sortedPairs;
	if (!pairs.empty()) {
		mainChain.insert(mainChain.begin(), pairs[0].second);
	}

	std::vector<std::size_t> jacobsthal;
	jacobsthal.push_back(0);
	jacobsthal.push_back(1);

	while (true) {
		size_t nextVal = jacobsthal[jacobsthal.size() - 1] + 2 * jacobsthal[jacobsthal.size() - 2];
		if (nextVal >= pairs.size()) {
			break ;
		}
		jacobsthal.push_back(nextVal);
	}

	std::vector<bool> inserted(pairs.size(), false);
	inserted[0] = true;

	size_t prevJ = 1;
	for (size_t k = 0; k < jacobsthal.size(); ++k) {
		size_t currJ = jacobsthal[k];
		for (long long idx = static_cast<long long>(currJ); idx > static_cast<long long>(prevJ); --idx) {
			if (static_cast<size_t>(idx) < pairs.size() && !inserted[idx]) {
				typename Container::iterator itPos = std::lower_bound(mainChain.begin(), mainChain.end(), pairs[idx].second);
				mainChain.insert(itPos, pairs[idx].second);
				inserted[idx] = true;
			}
		}
		prevJ = currJ;
	}

	for (long long idx = static_cast<long long>(pairs.size()) - 1; idx >= 0; --idx) {
        if (!inserted[idx]) {
            typename Container::iterator itPos = std::lower_bound(mainChain.begin(), mainChain.end(), pairs[idx].second);
            mainChain.insert(itPos, pairs[idx].second);
            inserted[idx] = true;
        }
    }

	if (hasOdd) {
        typename Container::iterator itPos = std::lower_bound(mainChain.begin(), mainChain.end(), oddElement);
        mainChain.insert(itPos, oddElement);
    }

    container.clear();
    for (size_t i = 0; i < mainChain.size(); ++i) {
        container.push_back(mainChain[i]);
    }
}
