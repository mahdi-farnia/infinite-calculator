//
//  main.cpp
//  calculator-project
//
//  Created by mahdi farnia on 10/7/1401 AP.

#include <iostream>
#include <string>
#include <string_view>
#include "bigint.hpp"
#include "misc.hpp"

static inline std::string evaluate(std::string_view lhs, char opt, std::string_view rhs) {
    switch (opt) {
        case '-':
            return bigint::sub(lhs, revertSign(rhs));

        case '+':
            return bigint::sum(lhs, rhs);

        case '*':
            return bigint::multiply(lhs, rhs);

        case '/':
            return bigint::divide(lhs, rhs);

        default: {
            std::string err{"Unknown operator used in expression: "};
            err += opt;
            return err;
        }
    }
}

int main(int argc, const char * argv[]) {
    std::string lhs, rhs;
    char opt;

    while (true) {
        std::cout << "$: ";
        std::cin >> lhs >> opt >> rhs;

        std::cout << evaluate(lhs, opt, rhs) << '\n';
    }

    return 0;
}
