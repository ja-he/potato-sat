#include <set> 
#include <iostream> 

// using Atom    = unsigned int; 
using Literal = int; 
using Clause  = std::set<Literal>; 
using Clause_set = std::set<Clause>; 

// DECLARATIONS: 
Clause remove_literal(Clause c, Literal l); 
Clause    add_literal(Clause c, Literal l); 
Literal negate_literal(Literal l); 
Literal choose_literal(Clause_set s); 
bool dpll(std::set<Clause> s); 
Clause_set assign_literal(Clause_set s, Literal l); 
Clause_set propagate_unit_clauses(Clause_set); 
Clause_set eliminate_pure_literals(Clause_set); 
bool is_empty(Clause_set s); 
bool has_empty_clause(Clause_set s); 
void print_clause_set(Clause_set s); 
void print_clause(Clause c); 



// IMPLEMENTATIONS: 
Clause remove_literal(Clause c, Literal l) { c.erase(l); return c; }
Clause add_literal(Clause c, Literal l) { c.insert(l); return c; }
Literal negate_literal(Literal l) { return (-1)*l; } 

Literal choose_literal(Clause_set s) {
  return *(s.begin()->begin());
}

bool is_empty(Clause_set s) { return s.empty(); }
bool has_empty_clause(Clause_set s) { 
  for (Clause c : s) {
    if (c.empty()) return true; 
  }
  return false; 
}

Clause_set assign_literal(Clause_set s, Literal l) {
  Clause new_clause = Clause(); 
  new_clause.insert(l); 
  s.insert(new_clause); 
  return s; 
}

Clause_set propagate_unit_clauses(Clause_set s) { 
  // DBG
  std::cout << "    given clause set: "; 
  print_clause_set(s); 

  std::set<Literal> unit_literals = std::set<Literal>(); 
  for (Clause c : s) {
    if (c.size() == 1) {
      unit_literals.insert(*(c.begin()));
    }
  }

  // DBG
  std::cout << "    found unit literals: "; 
  print_clause(unit_literals);
  std::cout << std::endl; 

  for (Literal unit_literal : unit_literals) {

    // erase any clause that contains l
    Clause_set clauses_containing_unit_literal = Clause_set(); 
    for (Clause c : s) {
      if (c.count(unit_literal) > 0) {
        clauses_containing_unit_literal.insert(c); 
      }
    }
    for (Clause c : clauses_containing_unit_literal) {
      s.erase(c); 
    }
    
    // erase -l from all clauses, cant be assigned
    Literal negated_unit_literal = (-1)*unit_literal; 
    for (Clause c : s) {
      if (c.count(negated_unit_literal) > 0) {
        s.erase(c);
        c.erase(negated_unit_literal); 
        s.insert(c); 
      }
    }
  }

  // DBG
  std::cout << "    returing clause set: "; 
  print_clause_set(s);

  return s; 
}
Clause_set eliminate_pure_literals(Clause_set s) { return s; /* TODO */ }

bool dpll(Clause_set s) {

  // DBG
  std::cout << "dpll for "; 
  print_clause_set(s); 

  // DBG
  std::cout << "  UNITPROP:" << std::endl; 

  s = propagate_unit_clauses(s); 

  // DBG
  std::cout << "  after: "; 
  print_clause_set(s); 

  if (has_empty_clause(s)) return false; 
  s = eliminate_pure_literals(s); 
  if (is_empty(s)) return true; 
  Literal l = choose_literal(s); 
  Literal not_l = negate_literal(l); 
  return dpll(assign_literal(s,     l)) 
      || dpll(assign_literal(s, not_l)); 
}

void print_clause(Clause c) {
  std::cout << "{ "; 
  for (Literal l : c) {
    std::cout << l << " "; 
  }
  std::cout << "} "; 
}

void print_clause_set(Clause_set s) {
  std::cout << "[ "; 
  for (Clause c : s) {
    print_clause(c);
  }
  std::cout << "] " << std::endl; 
} 






int main() {
  Clause_set s { {-1,2}
               , {-1,3,9} 
               , {-2,-3,4} 
               , {-4,5,10} 
               , {-4,6,11} 
               , {-5,-6} 
               , {1,7,-12} 
               , {1,8} 
               , {-7,-8,-13} };
  std::cout << ((dpll(s)) ? "SAT" : "UNSAT") << std::endl; 
  return 0; 
}
