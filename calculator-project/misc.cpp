//
//  misc.cpp
//  calculator-project
//
//  Created by mahdi farnia on 10/7/1401 AP.
//

#include "misc.hpp"

namespace {
constexpr void normalizeFloatPart(std::string &num, size_t dotPos) {
    size_t i = num.size();
    while (num[i - 1] == '0' && i - 1 > dotPos + 1) --i;
    num.erase(i);
}
};

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

void normalizeNumber(std::string &num) {
    char sign = getSign(num);
    num = removeSign(num);
    
    size_t dotPos = getDotPosition(num),
    numLength = num.size();

    if (dotPos == 0) { // .98 -> 0.98
        num.insert(0, 1, '0');
        ++dotPos;
    } else if (dotPos == numLength) { // 123 -> 123.0
        num.append(".0");
    } else if (dotPos == numLength - 1) { // 123. -> 123.0
        num.append("0");
    }

    dotPos -= normalizeFractionPart(num, dotPos);
    normalizeFloatPart(num, dotPos);
    
    if (sign == '-')
        num = revertSign(num);
}

