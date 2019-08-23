#include "dpll-basic.h"
#include "dpll-basic-defs.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <set>

Literal
negate_literal(Literal l)
{
  return (-1) * l;
}

Literal
choose_literal(const Clause_set& s, Literal_choosing_heuristic h)
{
  switch (h) {
    // TODO(ztf) all the missing heuristics
    case random_choice_heuristic:
      // TODO(ztf) this isn't random, its just the first one found
      return *(s.begin()->begin());

    case jerosolow_wang_heuristic: {
      std::map<Literal, float> variable_jerowang_heuristic_eval;
      for (Clause const& c : s) {
        for (Literal l : c) {
          if (l < 0) {
            l *= (-1);
          }
          // add 2^(-|c|) where |c| is clause size
          variable_jerowang_heuristic_eval[l] += std::pow(2, (-1) * c.size());
        }
      }
      return var_with_max_estimate(variable_jerowang_heuristic_eval);
    }

    default:
      // just return the first-best value, you find
      return *(s.begin()->begin());
  }
}

Literal
var_with_max_estimate(const std::map<Literal, float>& heuristic_estimates)
{
  return std::max_element(std::begin(heuristic_estimates),
                          std::end(heuristic_estimates),
                          [](auto l, auto r) { return l.second < r.second; })
    ->first;
}

bool
is_empty(const Clause_set& s)
{
  return s.empty();
}

bool
has_unit_clause(const Clause_set& s)
{
  for (Clause const& c : s) {
    if (c.size() == 1)
      return true;
  }
  return false;
}

bool
has_empty_clause(const Clause_set& s)
{
  for (Clause const& c : s) {
    if (c.empty())
      return true;
  }
  return false;
}

Clause_set
assign_literal(const Clause_set& s, Literal l)
{
  Clause new_clause = Clause();
  new_clause.insert(l);
  Clause_set extended_set = Clause_set(s);
  extended_set.insert(new_clause);
  return extended_set;
}

void
propagate_unit_clauses(Clause_set& s)
{
  std::set<Literal> unit_literals = std::set<Literal>();
  for (Clause const& c : s) {
    if (c.size() == 1) {
      unit_literals.insert(*(c.begin()));
    }
  }

  for (Literal unit_literal : unit_literals) {

    // erase any clause that contains the unit literal
    Clause_set clauses_containing_unit_literal = Clause_set();
    for (Clause const& c : s) {
      if (c.count(unit_literal) > 0) {
        clauses_containing_unit_literal.insert(c);
      }
    }
    for (Clause const& c : clauses_containing_unit_literal) {
      s.erase(c);
    }

    // erase -unit_literal from all clauses, cant be assigned
    Literal negated_unit_literal = (-1) * unit_literal;
    Clause_set clauses_to_reduce;
    for (Clause const& c : s) {
      if (c.count(negated_unit_literal) > 0) {
        clauses_to_reduce.insert(c);
      }
    }

    for (Clause c : clauses_to_reduce) {
      s.erase(c);
      c.erase(negated_unit_literal);
      s.insert(c);
    }
  }

  // TODO(ztf) could be optimized, basically loops once again here and also once
  //           at the top of the function.
  //           What i  should do is build the set at the top of the function,
  //           then check if it's empty (and if so, just return) and at the
  //           bottom just call propagate...() again.
  if (has_unit_clause(s)) {
    propagate_unit_clauses(s);
  }
}

void
eliminate_pure_literals(Clause_set& s)
{

  std::set<Literal> pure_literals = find_pure_literals(s);

  while (!pure_literals.empty()) {
    Clause_set clauses_to_eliminate;
    for (Clause const& c : s) {
      for (Literal l : c) {
        if (pure_literals.count(l) > 0) {
          clauses_to_eliminate.insert(c);
        }
      }
    }

    for (Clause const& c : clauses_to_eliminate) {
      s.erase(c);
    }

    pure_literals = find_pure_literals(s);
  }
}

std::set<Literal>
find_pure_literals(const Clause_set& s)
{
  std::set<Literal> positive_atoms;
  std::set<Literal> negated_atoms;
  for (Clause const& c : s) {
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

void
print_progress(const std::string& lead, const Clause_set& s)
{
  if (print_progress_basic_dpll) {
    std::cout << lead;
    print_clause_set(s);
  }
}

bool
dpll(Clause_set s)
{
  print_progress("DPLL for clause set:    ", s);

  propagate_unit_clauses(s);
  print_progress("  | unit-propagation => ", s);

  if (has_empty_clause(s))
    return false;

  eliminate_pure_literals(s);
  print_progress("  | pure lit. elim.  => ", s);

  if (is_empty(s))
    return true;

  // TODO(ztf) case splitting

  Literal l = choose_literal(s, heuristic_to_choose_by);
  Literal not_l = negate_literal(l);
  return dpll(assign_literal(s, l)) || dpll(assign_literal(s, not_l));
}
