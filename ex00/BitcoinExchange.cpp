#include "BitcoinExchange.hpp"
#include <cstddef>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& src) {
	*this = src;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& rhs) {
	if (this != &rhs) {
		_database = rhs._database;
	}

	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

void BitcoinExchange::loadDatabase(const std::string& filename) {
	std::ifstream file(filename.c_str());

	if (!file.is_open()) {
		throw BitcoinExchange::FileException();
	}

	std::string line;
	std::string date;
	std::string rateStr;

	while (std::getline(file, line)) {
		if (line.empty()) {
			continue ;
		}
		std::istringstream iss(line);

		if (std::getline(iss, date, ',')) {
			if (std::getline(iss, rateStr)) {
				_database[date] = std::atof(rateStr.c_str());
			}
		}
	}
}

void BitcoinExchange::evaluateInput(const std::string& filename) {
	std::ifstream file(filename.c_str());

	if (!file.is_open()) {
		throw BitcoinExchange::FileException();
	}

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line)) {
		if (line.empty()) {
			continue ;
		}
		size_t delimPos = line.find(" | ");
		if (delimPos == std::string::npos) {
			std::cerr << "Error: bad input => " << line << std::endl;
			continue ;
		}
		std::string date = line.substr(0, delimPos);
		std::string valueStr = line.substr(delimPos + 3);
		if (!isValidDate(date)) {
			std::cerr << "Error: bad input => " << date << std::endl;
			continue ;
		}
		float value;
		if (!isValidValue(valueStr, value)) {
			continue ;
		}
		std::map<std::string, float>::const_iterator it = _database.lower_bound(date);
		if (it != _database.end() && it->first == date) {

		} else if (it == _database.begin()) {
			std::cerr << "Error: no data for date " << date << std::endl;
			continue ;
		} else {
			--it;
		}
		std::cout << date << " => " << value << " = " << (value * it->second) << std::endl;
	}
}

bool BitcoinExchange::isValidValue(const std::string& valueStr, float& outValue) const {
	if (valueStr.length() > 0 && valueStr[0] == '-') {
		std::cerr << "Error: not a positive number." << std::endl;
		return false;
	}

	outValue = std::atof(valueStr.c_str());

	if (outValue > 1000.0f) {
		std::cerr << "Error: too large a number." << std::endl;
		return false;
	}
	return true;
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
	if (date.length() != 10) return false;
	if (date[4] != '-' || date[7] != '-') return false;
	
	for (size_t i = 0; i < date.length(); i++) {
		if (i == 4 || i == 7) continue;
		if (!isdigit(date[i])) return false;
	}

	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());

	if (year < 2009 || year > 9999) return false;
	if (month < 1 || month > 12) return false;
	if (day < 1 || day > 31) return false;

	if (month == 2 && day > 29) return false;

	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;

	return true;
}
