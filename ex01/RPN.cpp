#include "RPN.hpp"
#include <iostream>
#include <stack>
#include <list>
#include <sstream>
#include <cstdlib>

// TODO: Implement Orthodox Canonical Form

// TODO: Implement evaluate(const std::string& expression)
// 1. Create a std::stack<int, std::list<int> > (Using std::list perfectly complies with the container rule!)
// 2. Loop through the expression character by character (or stringstream by word)
// 3. Ignore spaces
// 4. If you see a digit (0-9), push it to the stack (convert char to int by subtracting '0', e.g. token[0] - '0')
// 5. If you see an operator (+, -, *, /):
//      - Check if the stack has at least 2 elements. If not, print "Error" and return.
//      - Pop the top element (call it 'b')
//      - Pop the next element (call it 'a')
//      - Apply the operator: 'a + b', 'a - b', 'a * b', or 'a / b' (Check for division by zero!)
//      - Push the result back to the stack.
// 6. If you see any other character, print "Error" and return.
// 7. After the loop, if the stack has EXACTLY 1 element, print it!
// 8. If the stack has more than 1 element (e.g. "1 2 3 +"), print "Error".

void RPN::evaluate(const std::string& expression) {
    (void)expression;
    // Your magic goes here...
}
