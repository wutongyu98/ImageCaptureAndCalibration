//
// Created by anacreon on 7/23/20.
//

#ifndef CTR_WS_INPUT_ARG_PARSER_H
#define CTR_WS_INPUT_ARG_PARSER_H

#include <algorithm>
#include <string>
#include <vector>

class InputParser {
 public:
  InputParser(int& argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
      this->tokens_.emplace_back(std::string(argv[i]));
    }
  }
  /// @author iain
  auto GetCmdOption(const std::string& option) const -> const std::string& {
    std::vector<std::string>::const_iterator itr;
    itr = std::find(this->tokens_.begin(), this->tokens_.end(), option);
    if (itr != this->tokens_.end() && ++itr != this->tokens_.end()) {
      return *itr;
    }
    static const std::string kEmptyString;
    return kEmptyString;
  }
  /// @author iain
  auto CmdOptionExists(const std::string& option) const -> bool {
    return std::find(this->tokens_.begin(), this->tokens_.end(), option) != this->tokens_.end();
  }

 private:
  std::vector<std::string> tokens_;
};

#endif  // CTR_WS_INPUT_ARG_PARSER_H
