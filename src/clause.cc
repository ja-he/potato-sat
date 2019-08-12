#include "clause.h"

Clause::Clause(void) {
  literals = std::set<Literal>(); 
}

void Clause::add(Literal literal) {
  literals.insert(literal); 
}

std::set<Literal> Clause::get_literals(void) const { return literals; }

bool operator==(const Clause& lhs, const Clause& rhs) {
  return (lhs.get_literals() == rhs.get_literals()); 
}

std::ostream& operator<<(std::ostream& output, const Clause& clause) {
  output << '{';
  std::set<Literal> literals = clause.get_literals(); 
  int count = literals.size(); 
  for (Literal literal : literals) {
    output << ' ' 
           << literal 
           << ((--count > 0) ? ',' : ' '); 
  }
  output << '}';
  return output; 
}
