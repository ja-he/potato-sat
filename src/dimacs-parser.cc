#include "dimacs-parser.h"
#include "dpll-basic-defs.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

bool
is_comment(const std::string& line)
{
  return (line.length() > 0 && line[0] == 'c');
}

bool
is_problem_line(const std::string& line)
{
  return (line.length() > 0 && line[0] == 'p');
}

void
parse_problem_line(std::string& line)
{
  /* TODO */
}

bool
ends_with_zero(const std::string& line)
{
  return line.length() > 0 && line.at(line.length() - 1) == '0';
}

DIMACS_line_type
parse_dimacs_line(std::string& line, Clause& clause_buf)
{
  if (is_comment(line)) {
    return comment;
  } else if (is_problem_line(line)) {
    parse_problem_line(line);
    return problem;
  } else if (!ends_with_zero(line)) {
    return unrecognized;
  } else {

    // break lines up at whitespaces
    std::istringstream iss(line);
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
          clause_buf.insert(prospective_literal);
        }
      } catch (...) {
        std::cerr << "error encountered: line (" << line << ") not recognized"
                  << std::endl;
        return unrecognized;
      }
    }

    return clause;
  }
}

bool
read_in_dimacs_file(std::string file_location, Clause_set& clause_set_buf)
{
  std::ifstream given_input_file(file_location, std::ios::in);

  // TODO(ztf) further error handling, probably...
  if (!given_input_file.is_open()) {
    std::cerr << "Error reading the provided file ('" << file_location << "')"
              << std::endl;
    return 1;
  }

  unsigned int line_nr = 0;
  std::string current_line;
  std::optional<Clause> current_clause;
  std::cout << "GIVEN A FILE, READING...\n";
  while (std::getline(given_input_file, current_line)) {
    Clause current_clause;
    DIMACS_line_type parse_result =
      parse_dimacs_line(current_line, current_clause);
    std::cout << ++line_nr << " [";
    switch (parse_result) {
      case clause:
        std::cout << "clause]: ";
        print_clause(current_clause);
        clause_set_buf.insert(current_clause);
        break;
      case comment:
        std::cout << "comment]";
        break;
      case problem:
        std::cout << "problem]";
        break;
      case unrecognized:
        std::cout << "unrecognized]";
        break;
    }
    std::cout << '\n';
  }
  std::cout << std::flush;

  return true;
}
