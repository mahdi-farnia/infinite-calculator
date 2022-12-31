//
//  bigint.cpp
//  calculator-project
//
//  Created by mahdi farnia on 10/7/1401 AP.
//

#include "bigint.hpp"
#include "misc.hpp"

/** NOTE
 * Operations indicate based on number signs not function call:
 * -1 & +100 => sub
 * -1 & -100 => sum
 */

namespace {
inline std::string makeZero(size_t count) {
    std::string result;

    for (size_t i{}; i < count; ++i) result += '0';
    
    return result;
}
};

std::string bigint::sum(std::string_view greaterNumber, std::string_view lessNumber) {
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

std::string bigint::sub(std::string_view greaterView, std::string_view lessView) {
    if (hasEqualSign(greaterView, lessView))
        return bigint::sum(greaterView, lessView);

    // extra lookup for sorting in case of => greater = 33, less = 44
    if (removeSign(greaterView) < removeSign(lessView))
        greaterView.swap(lessView);
    
    bool hasSign = greaterView[0] == '-';

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

std::string bigint::multiply(std::string_view greaterNumber, std::string_view lessNumber) {
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

std::string bigint::divide(std::string_view lhs, std::string_view rhs) {
    bool resultIsPositive = hasEqualSign(lhs, rhs);

    // Do not sort numbers. order is important!
    lhs = removeSign(lhs);
    rhs = removeSign(rhs);

    if (rhs[0] == '0')
        return "ZeroDivisionError: could not divide by zero!";
    if (lhs[0] == '0') // Floating point numbers are not supported yet!
        return "0";
    
    std::string result;
    
    for (size_t i = 0, count = lhs.size() / rhs.size(); true; ++i) {
        if (i == count) {
            // check for remain
            break;
        }
        
        // TODO: Complete this!
        std::string_view part = lhs.substr(rhs.size() * i, rhs.size() * (i + 1));
        if (part < rhs) {
        }
    }

    return result;
}
