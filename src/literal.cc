#include "literal.h"

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
