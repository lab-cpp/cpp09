#ifndef RPN_HPP
#define RPN_HPP

#include <string>

class RPN {
    private:
        RPN();
        RPN(const RPN& src);
        RPN& operator=(const RPN& rhs);
        ~RPN();

    public:
        static void evaluate(const std::string& expression);
};

#endif
