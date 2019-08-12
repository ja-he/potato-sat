#include <iostream> 
#include "atom.h"
#include "literal.h"
#include "clause.h"

int main() {
  std::cout << "welcome to potato-sat! :)" 
            << std::endl; 
  Atom a = 12; 
  Literal neg_a = Literal(a, true); 
  Literal jst_a = Literal(a, false);
  Clause c = Clause(); 
  c.add(neg_a); 
  c.add(jst_a); 
  std::cout << "a = " << a << std::endl; 
  std::cout << "neg a = " << neg_a << std::endl; 
  std::cout << "    a = " << jst_a << std::endl; 
  std::cout << "cl. c = " << c << std::endl; 
  return 0; 
}
