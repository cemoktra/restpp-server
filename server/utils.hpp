#pragma once

#include <queue>
#include <string>
#include <string_view>

namespace restpp::utils {
    // TODO: consider using C++ 20 coroutine generator
    std::queue<std::string_view> split(std::string_view str, std::string_view delim);
    std::pair<std::string, std::string> split_keyValue(std::string_view str);
    bool str_compare(std::string_view str1, std::string_view str2);
}