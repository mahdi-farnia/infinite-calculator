//
//  main.cpp
//  calculator-project
//
//  Created by mahdi farnia on 10/7/1401 AP.

#include <iostream>
#include <string>
#include "bigint.hpp"
#include "misc.hpp"

static inline std::string evaluate(std::string &lhs, char opt, std::string &rhs) {
    switch (opt) {
        case '*':
            return bigint::multiplyFloating(lhs, rhs);

        case '/':
            return bigint::divideFloating(lhs, rhs);

        default: {
            std::string err{"Unknown operator used in expression: "};
            err += opt;
            throw err;
        }
    }
}

int main(int argc, const char * argv[]) {
    std::string lhs, rhs, result;
    char opt;

    while (true) {
        std::cout << "$: ";

        std::cin >> lhs >> opt >> rhs;

        normalizeNumber(lhs);
        normalizeNumber(rhs);
        
        try {
            result = evaluate(lhs, opt, rhs);

            normalizeNumber(result);
            formatNumber(result);
        } catch (std::string &err) {
            result = err;
        }

        std::cout << result << '\n';
    }

    return 0;
}
