#ifndef DPLL_BASIC_H
#define DPLL_BASIC_H

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
 * Negates a given literal.
 *
 * @param l the literal
 * @return  the negation of l
 */
auto
negate_literal(Literal l) -> Literal;

/**
 * Chooses a Literal from the given set of clauses via a given heuristic
 * function.
 *
 * @param s   a set of clauses from which to choose a literal
 * @param h   a heuristic by which to choose a literal
 * @return    a literal
 */
auto
choose_literal(const Clause_set& s, Literal_choosing_heuristic h) -> Literal;

/**
 * Performs a basic variant of the Davis-Putnam-Logemann-Loveland (or DPLL)
 * algorithm recursively on the given set of clauses.
 *
 * @param s   the set of clauses
 * @return    whether the set of clauses (the boolean formula it represents)
 *            is satisfiable
 */
bool
dpll(Clause_set s);

/**
 * Returns for a given clause set and a literal a clause set that has the unit
 * clause with that literal added to it (thus assigning the literal to
 * necessarily be true for the clause set to be satisfiable).
 *
 * @param s   the clause set
 * @param l   the literal
 * @return    another clause set extended by the unit clause {l}
 */
auto
assign_literal(const Clause_set& s, Literal l) -> Clause_set;

/**
 * Deletes all unit clauses in the clause set as well as any other clauses
 * containing the literals from the unit clauses.
 * Removes the negations of the literals from the unit clauses from any other
 * clause.
 *
 * @param s   the clause set
 */
void
propagate_unit_clauses(Clause_set&);

/**
 * Eliminates all clauses  that involve pure literals in the given clause set.
 * (A literal is considered pure if it only occurs non-negated, e.g. the
 *  literal l is only pure if no clause {-l, ...} is in the clause set.)
 *
 * @param s   the clause set
 */
void
eliminate_pure_literals(Clause_set& s);

/**
 * Finds all pure literals in a given set of clauses.
 *
 * @param s   the set of clauses
 * @return    all pure literals in the set of clauses
 */
auto
find_pure_literals(const Clause_set& s) -> std::set<Literal>;

/**
 * Returns whether a given set of clauses is empty, i.E. contains no clauses.
 *
 * @param s the set of clauses
 * @return  whether s is empty
 */
auto
is_empty(const Clause_set& s) -> bool;

/**
 * Returns whether a given set of clauses contains an empty clause.
 *
 * @param s the set of clauses
 * @return  whether {} in s
 */
auto
has_empty_clause(const Clause_set& s) -> bool;

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
