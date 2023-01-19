//
//  bigint.cpp
//  calculator-project
//
//  Created by mahdi farnia on 10/7/1401 AP.
//

#include "bigint.hpp"
#include "misc.hpp"

#define MAX_PRECISION 6

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
    
    normalizeFractionPart(result, result.size());
    
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

/** lhs should always be greater than rhs, two numbers are normalized completely */
std::string divide(std::string_view lhs, std::string_view rhs, std::string *resultRemain /* default: nullptr */) {
    std::string result, remain, temp_remain;
    size_t coefficient{};

    for(size_t i{}, len = lhs.size() - rhs.size() + 1; i < len; ++i) {
        // Slice lhs by rhs length first time and then go 1 by 1
        remain += i == 0 ? lhs.substr(0, rhs.size()) : lhs.substr(rhs.size() + (i - 1), 1);
        
        normalizeFractionPart(remain, remain.size());

        coefficient = 0;
        temp_remain = sub(remain, rhs);

        if (temp_remain[0] != '-') { // if picked range is less than rhs -> put zero otherwise do division
            remain = temp_remain;
            ++coefficient; // count previous subtract

            while (StringedNumberCompare(remain, >=, rhs)) {
                remain = sub(remain, rhs);
                ++coefficient;
            }
        }
        
        result += std::to_string(coefficient);
    }
    
    if (resultRemain != nullptr)
        *resultRemain = remain;
    
    normalizeFractionPart(result, result.size());
    return result;
}

std::string multiplyFloating(std::string &lhs, std::string &rhs) {
    size_t finalPos = removeDot(lhs) + removeDot(rhs);
    std::string result = multiply(lhs, rhs);
    
    if (result != "0") result.insert(result.size() - finalPos, ".");

    return result;
}

std::string divideFloating(std::string &lhs, std::string &rhs, std::string *resultRemain) {
    long finalPos = removeDot(lhs) - removeDot(rhs);

    if (rhs == "0")
        throw std::string("ZeroDivisionError: could not divide by zero");
    if (lhs == "0")
        return "0.0";
    
    if (finalPos < 0) { // multiply lhs and rhs by 10 ^ |finalPos|
        lhs.append(makeZero(-finalPos));
        finalPos = 0;
    }
    
    bool resultIsNegative = !hasEqualSign(lhs, rhs);

    lhs = removeSign(lhs);
    rhs = removeSign(rhs);

    std::string remain = lhs, result;
    long precision = -1; // do not count the first division

    for (; precision < MAX_PRECISION; ++precision) {
        if (StringedNumberCompare(remain, >=, rhs))
            result += divide(remain, rhs, &remain);
        else result += "0";

        ++finalPos;
        if (remain == "0") break;
        
        remain += "0";
    }

    if (result != "0") {
        long index = result.size() - (finalPos - 1);
        
        // In case of result is less than 0 and we should put dot behind the number
        if (index < 0) {
            result.insert(0, makeZero(-index));
            index = 0;
        }

        result.insert(index, ".");
    }
    
    return resultIsNegative ? revertSign(result) : result;
}
}
