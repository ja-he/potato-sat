#include "boolean-logic.h"

/* --- LITERAL -------------------------------------------------------------- */

Literal::Literal(Atom _atom, bool _negated) {
  atom    = _atom; 
  negated = _negated; 
}

Atom Literal::get_atom(void) const { return atom; }
bool Literal::is_negated(void) const { return negated; }

std::ostream& operator<<(std::ostream& output, const Literal& literal) {
  return output << ( (literal.is_negated()) ? "\u00ac" : " " )
                << literal.get_atom(); 
}

bool operator==(const Literal& lhs, const Literal& rhs) {
  return ( lhs.get_atom()   == rhs.get_atom()   ) 
      && ( lhs.is_negated() == rhs.is_negated() ); 
}

bool operator<(const Literal& lhs, const Literal& rhs) {
  int l = lhs.get_atom();
  l *= lhs.is_negated() ? -1 : 1; 
  int r = rhs.get_atom();
  r *= rhs.is_negated() ? -1 : 1; 
  return l < r; 
}















/* --- CLAUSE --------------------------------------------------------------- */

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
