#include "dimacs-parser.h"
#include <iostream>
#include <iomanip>
#include <iterator>
#include <optional>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

bool
dimacs_line_is_comment(const std::string& line)
{
  return (line.length() > 0 && line[0] == 'c');
}

// TODO(ztf)
//   thinking about having parse_dimacs_line() instead of parse_clause be
//   called by read_in_dimacs_file() and then return a pair or struct  of two 
//   values where one is of type 
//        enum line_type { comment, p-line, clause, error }
//   and the other of type 
//        Clause
//   and is potentially empty (unless the former == clause). 

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

bool
read_in_dimacs_file(std::string file_location, Clause_set& clause_set_buf) 
{
  std::ifstream given_input_file(file_location, std::ios::in);

  // TODO(ztf) further error handling, probably...
  if (!given_input_file.is_open()) {
    std::cerr << "Error reading the provided file ('"
              << file_location << "')" << std::endl;
    return 1;
  }

  std::string current_line;
  std::optional<Clause> current_clause;
  std::cout << "GIVEN A FILE, READING...\n";
  while (std::getline(given_input_file, current_line)) {
    if (!dimacs_line_is_comment(current_line)) {
      current_clause = parse_clause(current_line);
      if (current_clause.has_value()) {
        std::cout << std::setw(30) << " | ";
        print_clause(current_clause.value());
        clause_set_buf.insert(current_clause.value());
      } else {
        std::cout << std::setw(30) << " | seems to have had no value...";
      }
      std::cout << '\r' << current_line << '\n';
    }
  }
  std::cout << std::flush;

  return true;
}
