#ifndef RPN_HPP
#define RPN_HPP

#include <string>

class RPN {
    private:
        // Orthodox Canonical Form (Not strictly necessary if all methods are static,
        // but required by the module rules unless explicitly stated otherwise)
        RPN();
        RPN(const RPN& src);
        RPN& operator=(const RPN& rhs);
        ~RPN();

    public:
        // Core Function
        static void evaluate(const std::string& expression);
};

#endif
