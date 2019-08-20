#include "dimacs-parser.h"
#include "dpll-basic.h"
#include "parse-arguments.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>

int
main(int argc, char** argv)
{

  Potato_SAT_settings settings = parse(argc, argv);

  // immmediate stops to further program execution
  if (settings.parsing_error) {
    return 1;
  } else if (settings.printed_help_msg) {
    return 0;
  }

  // print_settings(settings);

  Clause_set s;

  if (settings.read_file) {

    std::ifstream given_input_file(settings.file_location, std::ios::in);

    // TODO(ztf) further error handling, probably...
    if (!given_input_file.is_open()) {
      std::cerr << "Error reading the provided file ('"
                << settings.file_location << "')" << std::endl;
      return 1;
    }

    std::string current_line;
    std::optional<Clause> current_clause;
    std::cout << "GIVEN A FILE, READING...\n";
    while (std::getline(given_input_file, current_line)) {
      current_clause = parse_clause(current_line);
      if (current_clause.has_value()) {
        std::cout << std::setw(30) << " | ";
        print_clause(current_clause.value());
        s.insert(current_clause.value());
      } else {
        std::cout << std::setw(30) << " | seems to have had no value...";
      }
      std::cout << '\r' << current_line << '\n';
    }
    std::cout << std::flush;

  } else {
    // TODO(ztf) read STDIN
    s = { { -1, 2 },     { -1, 3, 9 },  { -2, -3, 4 },
          { -4, 5, 10 }, { -4, 6, 11 }, { -5, -6 },
          { 1, 7, -12 }, { 1, 8 },      { -7, -8, -13 } };

    /*
    s = { { -4, -3, -2, -1 },   { -3, -1, 2, 4 },    { -4, -2, 1, 3 },
          { 1, 2, 3, 4 },       { -10, -9, -2, -1 }, { -9, -1, 2, 10 },
          { -10, -2, 1, 9 },    { 1, 2, 9, 10 },     { -6, -5, -2, -1 },
          { -5, -1, 2, 6 },     { -6, -2, 1, 5 },    { 1, 2, 5, 6 },
          { -18, -17, -2, -1 }, { -17, -1, 2, 18 },  { -18, -2, 1, 17 },
          { 1, 2, 17, 18 },     { -8, -7, -2, -1 },  { -7, -1, 2, 8 },
          { -8, -2, 1, 7 },     { 1, 2, 7, 8 },      { -26, -25, -2, -1 },
          { -25, -1, 2, 26 },   { -26, -2, 1, 25 },  { 1, 2, 25, 26 } };
    */
  }

  std::cout << ((dpll(s)) ? "SAT" : "UNSAT") << std::endl;

  return 0;
}
