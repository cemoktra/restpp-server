#include "utils.hpp"

namespace restpp::utils {
  std::queue<std::string_view> split(std::string_view str, std::string_view delim)
  {
    std::queue<std::string_view> output;
    size_t lastPos = 0;

    while (lastPos < str.size())
    {
        const auto pos = str.find_first_of(delim, lastPos);

        if (pos == std::string_view::npos)
          break;

        output.push(str.substr(lastPos, pos - lastPos));
        lastPos = pos + 1;
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