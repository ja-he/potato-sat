#ifndef DPLL_BASIC_H
#define DPLL_BASIC_H

#include <set> 

// using Atom    = unsigned int; 
using Literal = int; 
using Clause  = std::set<Literal>; 
using Clause_set = std::set<Clause>; 

// DECLARATIONS: 
Clause remove_literal(Clause c, Literal l); 
Clause    add_literal(Clause c, Literal l); 
Literal negate_literal(Literal l); 
Literal choose_literal(const Clause_set& s); 
bool dpll(std::set<Clause> s); 
Clause_set assign_literal(const Clause_set& s, Literal l); 
void propagate_unit_clauses(Clause_set&); 
void eliminate_pure_literals(Clause_set&); 
std::set<Literal> find_pure_literals(const Clause_set&); 
bool is_empty(const Clause_set& s); 
bool has_empty_clause(const Clause_set& s); 
void print_clause_set(const Clause_set& s); 
void print_clause(const Clause& c); 

#endif 
