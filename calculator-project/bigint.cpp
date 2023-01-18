//
//  bigint.cpp
//  calculator-project
//
//  Created by mahdi farnia on 10/7/1401 AP.
//

#include "bigint.hpp"
#include "misc.hpp"

namespace {
inline std::string makeZero(size_t count) {
    std::string result;
    
    for (size_t i{}; i < count; ++i) result += '0';
    
    return result;
}
};

namespace bigint {

std::string sum(std::string_view greaterNumber, std::string_view lessNumber) {
    if (!hasEqualSign(greaterNumber, lessNumber))
        return bigint::sub(greaterNumber, lessNumber);
    
    bool hasSign = greaterNumber[0] == '-';
    
    sortAndRemoveSign(greaterNumber, lessNumber);
    
    std::string result;
    uint8_t remain{};
    
    for (long less_index = lessNumber.size() - 1, greater_index = greaterNumber.size() - 1; true; --less_index, --greater_index) {
        if (greater_index == -1) {
            if (remain)
                push_front_char(result, digitToChar(remain));
            break;
        }
        
        uint8_t a = charToDigit(less_index < 0 ? '0' : lessNumber[less_index]), b = charToDigit(greaterNumber[greater_index]);
        
        uint8_t sum = a + b + remain;
        remain = sum / 10;
        push_front_char(result, digitToChar(sum % 10));
    }
    
    if (hasSign) result.insert(0, 1, '-');
    
    return result;
}

std::string sub(std::string_view greaterView, std::string_view lessView) {
    if (!hasEqualSign(greaterView, lessView))
        return bigint::sum(greaterView, revertSign(lessView));
    
    bool hasSign = StringedNumberCompare(removeSign(greaterView), <, removeSign(lessView));

    if (hasSign)
        greaterView.swap(lessView);

    greaterView = removeSign(greaterView);
    lessView = removeSign(lessView);
    
    std::string result{greaterView};
    
    for (long less_index = lessView.size() - 1, greater_index = result.size() - 1; less_index >= 0; --less_index, --greater_index) {
        uint8_t a = charToDigit(less_index < 0 ? '0' : lessView[less_index]), b = charToDigit(result[greater_index]);
        
        if (b < a) {
            for (long i = greater_index - 1; i >= 0; --i) {
                if (charToDigit(result[i]) != 0) {
                    result[i] = digitToChar(charToDigit(result[i]) - 1);
                    break;
                }
                result[i] = '9';
            }
            b += 10;
        }
        
        result[greater_index] = digitToChar(b - a);
    }
    
    normalizeNumber(result);
    
    if (hasSign) result.insert(0, 1, '-');
    
    return result;
}

std::string multiply(std::string_view greaterNumber, std::string_view lessNumber) {
    bool resultIsPositive = hasEqualSign(greaterNumber, lessNumber);
    
    sortAndRemoveSign(greaterNumber, lessNumber);
    
    if (lessNumber[0] == '0' || greaterNumber[0] == '0') // edge cases should be checked after signs were removed!
        return "0";
    
    std::string result = "0";
    
    for (long i = lessNumber.size() - 1, firstDigitCount{}; i != -1; --i, ++firstDigitCount) {
        for (long j = greaterNumber.size() - 1, secondDigitCount{}; j != -1; --j, ++secondDigitCount) {
            auto mul = std::to_string(charToDigit(greaterNumber[j]) * charToDigit(lessNumber[i])).append(makeZero(firstDigitCount + secondDigitCount));
            result = sum(result, mul);
        }
    }
    
    return resultIsPositive ? result : revertSign(result);
}

std::string divide(std::string_view lhs, std::string_view rhs, std::string *resultRemain /* default: nullptr */) {
    bool resultIsPositive = hasEqualSign(lhs, rhs);
    
    // Do not sort numbers. order is important!
    lhs = removeSign(lhs);
    rhs = removeSign(rhs);
    
    if (rhs[0] == '0')
        return "ZeroDivisionError: could not divide by zero!";
    if (lhs[0] == '0') // Floating point numbers are not supported yet!
        return "0";
    
    std::string result;
    std::string remain;
    
    size_t count = lhs.size() / rhs.size() + (lhs.size() % rhs.size() != 0); // ceil operation
    for (size_t i = 0; true;) {
        remain.append(lhs.substr(rhs.size() * i, rhs.size()));
        normalizeNumber(remain); // in case of 0034

        size_t coefficient{};
        while (StringedNumberCompare(remain, >=, rhs)) {
            remain = sub(remain, rhs);
            ++coefficient;
        }
        
        result.append(std::to_string(coefficient));
        
        if (++i >= count) {
            if (result.back() == '0') result.pop_back();
            break;
        }
    }
    
    if (resultRemain != nullptr) *resultRemain = remain;
    normalizeNumber(result);

    return resultIsPositive ? result : revertSign(result);
}
