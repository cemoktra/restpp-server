#include "utils.hpp"
#include <algorithm>

namespace restpp::utils {
  std::queue<std::string_view> split(std::string_view str, std::string_view delim)
  {
    std::queue<std::string_view> output;

    for (auto first = str.data(), second = str.data(), last = first + str.size(); second != last && first != last; first = second + 1) {
      second = std::find_first_of(first, last, std::cbegin(delim), std::cend(delim));

      output.emplace(first, second - first);
    }

    return output;
  }

  std::pair<std::string, std::string> split_keyValue(std::string_view str)
  {
    const auto pos = str.find_first_of(": ", 0);

    return std::make_pair<>(
      std::string(str.substr(0, pos)),
      std::string(str.substr(pos + 2))
    );
  }

  bool str_compare(std::string_view str1, std::string_view str2)
  {
    // return true;
    return ((str1.size() == str2.size()) && 
      std::equal(str1.begin(), str1.end(), str2.begin(), 
      [] (const char c1, const char c2) {
        return (c1 == c2 || std::toupper(c1) == std::toupper(c2));
      })
    );
  }   
}