#include "dpll-basic-defs.h"
#include <iostream>

void
print_clause(const Clause& c)
{
  std::cout << "{ ";
  for (Literal l : c) {
    std::cout << l << " ";
  }
  std::cout << "} ";
}

void
print_clause_set(const Clause_set& s)
{
  std::cout << "[ ";
  for (Clause const& c : s) {
    print_clause(c);
  }
  std::cout << "] " << std::endl;
}
