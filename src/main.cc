#include "dimacs-parser.h"
#include "dpll-basic.h"
#include "parse-arguments.h"
#include <iostream>
#include <set>

int
main(int argc, char** argv)
{

  Potato_SAT_settings settings = parse(argc, argv);

  // immmediate stops to further program execution
  if (settings.parsing_error) {
    return EXIT_FAILURE;
  } else if (settings.printed_help_msg) {
    return EXIT_SUCCESS;
  }

  // print_settings(settings);

  Clause_set s;

  if (settings.read_file) {
    if (read_in_dimacs_file(settings.file_location, s)) {
      std::cout << "successfully read in file" << std::endl;
    } else {
      std::cerr << "error reading file as DIMACS cnf" << std::endl; 
      return EXIT_FAILURE; 
    }
  } else {
    // TODO(ztf) read STDIN
    return EXIT_SUCCESS; // this will be removed
  }

  if (settings.print_progress) {
    print_progress_basic_dpll = true; 
  }
  heuristic_to_choose_by = settings.heuristic; 

  std::cout << ((dpll(s)) ? "SAT" : "UNSAT") << std::endl;

  return EXIT_SUCCESS;
}
