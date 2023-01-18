//
//  bigint.hpp
//  calculator-project
//
//  Created by mahdi farnia on 10/7/1401 AP.
//

#ifndef bigint_hpp
#define bigint_hpp

#include <string>
#include <string_view>

namespace bigint {
std::string sum(std::string_view, std::string_view);
std::string sub(std::string_view, std::string_view);
std::string multiply(std::string_view, std::string_view);
std::string divide(std::string_view, std::string_view, std::string * = nullptr);
}

#endif /* bigint_hpp */
