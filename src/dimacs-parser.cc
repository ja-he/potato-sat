#include "dimacs-parser.h"
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

bool
dimacs_line_is_comment(const std::string& line)
{
  return (line.length() > 0 && line[0] == 'c');
}

std::optional<Clause>
parse_clause(std::string& clausestr)
{
  std::optional<Clause> result;
  Clause prospective_clause;
  bool error_while_parsing = false;

  std::istringstream iss(clausestr);
  std::vector<std::string> prospective_literals{
    std::istream_iterator<std::string>{ iss },
    std::istream_iterator<std::string>{},
  };

  for (std::string& prospective_literal_str : prospective_literals) {
    int prospective_literal;
    try {
      prospective_literal = std::stoi(prospective_literal_str);
      if (prospective_literal == 0) {
        // end of line (according to DIMACS)
        break;
      } else {
        prospective_clause.insert(prospective_literal);
      }
    } catch (...) {
      std::cerr << "error encountered" << std::endl;
      error_while_parsing = true;
      break;
    }
  }

  if (!error_while_parsing) {
    result.emplace(prospective_clause);
  }

  return result;
}
