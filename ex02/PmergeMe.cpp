#include "PmergeMe.hpp"
#include <bits/types/struct_timeval.h>
#include <climits>
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <sstream>
#include <cstdlib>
#include <sys/time.h>

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe& src) {
	*this = src;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& rhs) {
	(void) rhs;
	return *this;
}

PmergeMe::~PmergeMe() {}

static long long getTime() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000LL) + tv.tv_usec;
}

void PmergeMe::execute(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Error: Not enough arguments." << std::endl;
        return;
    }

    std::vector<int> vec;
    std::deque<int> deq;

	for (int i = 1; i < argc; ++i) {
		std::string arg(argv[i]);
		if (arg.empty()) {
			std::cout << "Error" << std::endl;
			return ;
		}

		char* end;
		long val = std::strtol(arg.c_str(), &end, 10);

		if (*end != '\0' || arg.c_str() == end) {
			std::cerr << "Error" << std::endl;
			return ;
		}

		if (val <= 0 || val > INT_MAX) {
			std::cerr << "Error" << std::endl;
			return ;
		}

		vec.push_back(static_cast<int>(val));
		deq.push_back(static_cast<int>(val));
	}

	std::cout << "Before: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << (i + 1 == vec.size() ? "" : " ");
    }
    std::cout << std::endl;

	long long startVec = getTime();
	fordJohnsonSort(vec);
	long long endVec = getTime();

	long long startDeq = getTime();
	fordJohnsonSort(deq);
	long long endDeq = getTime();

	std::cout << "After: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << (i + 1 == vec.size() ? "" : " ");
    }
    std::cout << std::endl;

	double elapsedVec = static_cast<double>(endVec - startVec);
    double elapsedDeq = static_cast<double>(endDeq - startDeq);

    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector : " << elapsedVec << " us" << std::endl;
    std::cout << "Time to process a range of " << deq.size() << " elements with std::deque : " << elapsedDeq << " us" << std::endl;
}
