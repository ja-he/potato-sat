#include "dpll-basic.h"
#include <iostream>
#include <set>
#include "parse-arguments.h"



int
main(int argc, char** argv)
{

  Potato_SAT_settings settings = parse(argc,argv); 
  if (settings.parsing_error) {
    return 1;
  } else if (settings.printed_help_msg) {
    return 0; 
  }
  print_settings(settings); 

  /*
  Clause_set s{ { -1, 2 },     { -1, 3, 9 },  { -2, -3, 4 },
                { -4, 5, 10 }, { -4, 6, 11 }, { -5, -6 },
                { 1, 7, -12 }, { 1, 8 },      { -7, -8, -13 } };
  std::cout << ((dpll(s)) ? "SAT" : "UNSAT") << std::endl;
  */

  return 0;
}
