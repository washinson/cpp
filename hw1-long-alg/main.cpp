#include <iostream>
#include <string>
#include "big_integer.h"

int main() {
    std::string a;
    std::string op;
    std::string b;

    std::cout << "input a op b, like 200 + 300: ";
    std::cin >> a >> op >> b;
    if (op == "+") {
        std::cout << big_integer(a) + big_integer(b) << std::endl;
    } else if (op == "-") {
        std::cout << big_integer(a) - big_integer(b) << std::endl;
    } else if (op == "/") {
        std::cout << big_integer(a) / big_integer(b) << std::endl;
    } else if (op == "*") {
        std::cout << big_integer(a) * big_integer(b) << std::endl;
    } else if (op == "%") {
        std::cout << big_integer(a) % big_integer(b) << std::endl;
    }
    return 0;
}
