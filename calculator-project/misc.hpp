//
//  misc.hpp
//  calculator-project
//
//  Created by mahdi farnia on 10/7/1401 AP.
//

#ifndef misc_hpp
#define misc_hpp

#include <string>
#include <string_view>
#include <cstdint> // uint8_t
#include <cctype> // isdigit

#define StringedNumberCompare(num1, op, num2) (num1.size() == num2.size() ? num1 op num2 : num1.size() op num2.size())

constexpr uint8_t charToDigit(char ch) {
    return ch ? ch - '0' : 0;
}

constexpr char digitToChar(uint8_t dig) {
    return dig + '0';
}

constexpr char getSign(std::string_view num) {
    return num[0] == '-' ? '-' : '+';
}

constexpr bool hasEqualSign(std::string_view lhs, std::string_view rhs) {
    return !(getSign(lhs) - getSign(rhs)); // returns !0 = true for equal sign and !1 = false for different sign
}

/**
 * Remove extra 0 behind number
 * In the floating version, calls to this function is limited to inputs and outputs and not in calculations
 */
void normalizeNumber(std::string &);

/* returns delete count */
constexpr size_t normalizeFractionPart(std::string &num, size_t dotPos) {
    size_t i{};
    while (num[i] == '0' && i < dotPos - 1) i++;
    num.erase(0, i);
    return i;
}

constexpr size_t getDotPosition(std::string_view num) {
    size_t i{};
    while (num[i] != '.' && i < num.size()) ++i;
    return i;
}

[[nodiscard]] std::string revertSign(std::string_view);

constexpr void push_front_char(std::string &str, char ch) {
    str.insert(0, 1, ch);
}

[[nodiscard]] constexpr std::string_view removeSign(std::string_view number) {
    if (number[0] == '-' || number[0] == '+')
        number.remove_prefix(1);
    return number;
}

/** Sort base on length */
constexpr void sortAndRemoveSign(std::string_view &greaterNumber, std::string_view &lessNumber) {
    greaterNumber = removeSign(greaterNumber);
    lessNumber = removeSign(lessNumber);
    
    if (greaterNumber.size() < lessNumber.size())
        greaterNumber.swap(lessNumber);
}

constexpr void formatNumber(std::string &num) {
    size_t count = num.size() - 1 - getDotPosition(num);

    if (count == 1 && num.back() == '0')
        num.erase(num.end() - 2, num.end());
    
    if (num[0] == '-' && num == "0")
        num = revertSign(num);
}

constexpr size_t removeDot(std::string &num) {
    size_t pos = getDotPosition(num);

    num.erase(pos, 1);
    
    size_t res = num.size() - pos;
    
    if (res == 1 && num.back() == '0') { // DO NOT CALCULATE THE LAST EXTRA ZERO AS A FLOATING -> 5.0 => 5
        num.pop_back();
        return 0;
    }
    
    return res;
}

#endif /* misc_hpp */
