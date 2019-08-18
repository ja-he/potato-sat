#include "dpll-basic.h"
#include <iostream>
#include <set>

int
main()
{
  Clause_set s{ { -1, 2 },     { -1, 3, 9 },  { -2, -3, 4 },
                { -4, 5, 10 }, { -4, 6, 11 }, { -5, -6 },
                { 1, 7, -12 }, { 1, 8 },      { -7, -8, -13 } };
  std::cout << ((dpll(s)) ? "SAT" : "UNSAT") << std::endl;
  return 0;
}
