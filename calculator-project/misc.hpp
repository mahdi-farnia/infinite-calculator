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

/** Remove extra 0 behind number */
constexpr void normalizeNumber(std::string &num) {
    size_t i{};
    while (num[i] == '0') i++;

    auto end = num.begin() + i;

    // don't trim all number => 000 -> 0
    num.erase(num.begin(), end == num.end() ? end - 1 : end);
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

#endif /* misc_hpp */
