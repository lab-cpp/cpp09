#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>
#include <exception>

class BitcoinExchange {
    private:
        std::map<std::string, float> _database;

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& src);
        BitcoinExchange& operator=(const BitcoinExchange& rhs);
        ~BitcoinExchange();

        void loadDatabase(const std::string& filename);
        void evaluateInput(const std::string& filename);
        
        bool isValidDate(const std::string& date) const;
        bool isValidValue(const std::string& valueStr, float& outValue) const;

        class FileException : public std::exception {
            public:
                virtual const char* what() const throw() { return "Error: could not open file."; }
        };
};

#endif
