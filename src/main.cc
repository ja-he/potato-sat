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
    return 1;
  } else if (settings.printed_help_msg) {
    return 0;
  }

  // print_settings(settings);

  Clause_set s;

  if (settings.read_file) {

    read_in_dimacs_file(settings.file_location, s); 

    /*
    */

  } else {
    // TODO(ztf) read STDIN
    return 0;
  }

  std::cout << ((dpll(s)) ? "SAT" : "UNSAT") << std::endl;

  return 0;
}
