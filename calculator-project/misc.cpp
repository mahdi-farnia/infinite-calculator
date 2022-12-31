//
//  misc.cpp
//  calculator-project
//
//  Created by mahdi farnia on 10/7/1401 AP.
//

#include "misc.hpp"

std::string revertSign(std::string_view num) {
    std::string reverted{num};

    switch (num[0]) {
        case '+':
            reverted[0] = '-';
            break;
            
        case '-':
            num.remove_prefix(1);
            return std::string(num);
            
        default:
            reverted.insert(reverted.begin(), 1, '-');
            break;
    }

    return reverted;
}
