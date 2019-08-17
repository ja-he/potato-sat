#include <set> 
#include <iostream> 
#include "dpll-basic.h"

Literal negate_literal(Literal l) { return (-1)*l; } 

Literal choose_literal(const Clause_set& s, Literal_choosing_heuristic h) {
  // TODO: actually use the indicated heuristic 
  return *(s.begin()->begin());
}

bool is_empty(const Clause_set& s) { return s.empty(); }
bool has_empty_clause(const Clause_set& s) { 
  for (Clause c : s) {
    if (c.empty()) return true; 
  }
  return false; 
}

Clause_set assign_literal(const Clause_set& s, Literal l) {
  Clause new_clause = Clause(); 
  new_clause.insert(l); 
  Clause_set extended_set = Clause_set(s); 
  extended_set.insert(new_clause); 
  return extended_set; 
}

void propagate_unit_clauses(Clause_set& s) { 
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
  std::cout << "    final clause set: "; 
  print_clause_set(s);

}

void eliminate_pure_literals(Clause_set& s) {

  std::cout << "]]]]]]]]]] elim-pure-lits was give clause set ";
  print_clause_set(s); 
  
  std::set<Literal> pure_literals = find_pure_literals(s); 

  std::cout << "]]]]]]]]]] found pure lits "; 
  print_clause(pure_literals); 
  std::cout << std::endl; 
  
  Clause_set clauses_to_eliminate; 
  for (Clause c : s) {
    for (Literal l : c) {
      if (pure_literals.count(l) > 0) {
        clauses_to_eliminate.insert(c); 
      }
    }
  }

  for (Clause c : clauses_to_eliminate) {
    s.erase(c); 
  }

  /* TODO */ 
}

std::set<Literal> find_pure_literals(const Clause_set& s) {

  std::set<Literal> positive_atoms; 
  std::set<Literal> negated_atoms; 
  for (Clause c : s) {
    for (Literal l : c) {
      if (l > 0) {
        positive_atoms.insert(l); 
      } else {
        negated_atoms.insert(l); 
      }
    }
  }

  std::set<Literal> result; 
  for (Literal l : positive_atoms) {
    Literal not_l = negate_literal(l); 
    if (negated_atoms.count(not_l) == 0) {
      result.insert(l); 
    }
  }
  for (Literal not_l : negated_atoms) {
    Literal l = negate_literal(not_l); 
    if (positive_atoms.count(l) == 0) {
      result.insert(not_l); 
    }
  }

  return result; 

}

bool dpll(Clause_set s) {

  // DBG
  std::cout << "dpll for "; 
  print_clause_set(s); 

  // DBG
  std::cout << "  UNITPROP:" << std::endl; 

  propagate_unit_clauses(s); 

  // DBG
  std::cout << "  after: "; 
  print_clause_set(s); 

  if (has_empty_clause(s)) return false; 
  eliminate_pure_literals(s); 
  if (is_empty(s)) return true; 
  Literal l = choose_literal(s, random_choice_heuristic); 
  Literal not_l = negate_literal(l); 
  return dpll(assign_literal(s,     l)) 
      || dpll(assign_literal(s, not_l)); 
}

void print_clause(const Clause& c) {
  std::cout << "{ "; 
  for (Literal l : c) {
    std::cout << l << " "; 
  }
  std::cout << "} "; 
}

void print_clause_set(const Clause_set& s) {
  std::cout << "[ "; 
  for (Clause c : s) {
    print_clause(c);
  }
  std::cout << "] " << std::endl; 
} 
