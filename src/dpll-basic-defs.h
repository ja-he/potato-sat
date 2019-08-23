#ifndef DPLL_BASIC_DEFS_H
#define DPLL_BASIC_DEFS_H

#include <set>

/**
 * A literal is a possible but not necessarily negated atom (which is a boolean
 * variable and could be thought of as an unsigned int in the context of this
 * implementation).
 * Negative integers represent the negations of the non-negative counterparts
 * (i.E. -4 is the negation of 4).
 */
using Literal = int;

/**
 * A clause is a set of literals which are joined through the boolean 'or'.
 */
using Clause = std::set<Literal>;

/**
 * A set of clauses represents a booean formula in conjunctive normal form.
 */
using Clause_set = std::set<Clause>;

/** Enumerates the possible heuristics for literal-choosing */
enum Literal_choosing_heuristic
{
  /** simply chooses a literal randomly */
  random_choice_heuristic,
  /** TODO */
  moms_heuristic,
  /** TODO */
  bohms_heuristic,
  /** TODO */
  jerosolow_wang_heuristic,
  /** TODO */
  dlcs_heuristic,
  /** TODO */
  dlis_heuristic,
  /** TODO */
  rdlcs_heuristic,
  /** TODO */
  rdlis_heuristic,
  /** TODO */
  lefv_heuristic
};

/**
 * Prints a given set of clauses.
 *
 * @param s the set of clauses
 */
void
print_clause_set(const Clause_set& s);

/**
 * Prints a given clause.
 *
 * @param c the clause
 */
void
print_clause(const Clause& c);

#endif
