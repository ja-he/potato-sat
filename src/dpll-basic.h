#ifndef DPLL_BASIC_H
#define DPLL_BASIC_H

#include <map>
#include <set>
#include "settings.h"
#include "dpll-basic-defs.h"

/**
 * Negates a given literal.
 *
 * @param l the literal
 * @return  the negation of l
 */
Literal
negate_literal(Literal l);

/**
 * Chooses a Literal from the given set of clauses via a given heuristic
 * function.
 *
 * @param s   a set of clauses from which to choose a literal
 * @param h   a heuristic by which to choose a literal
 * @return    a literal
 */
Literal
choose_literal(const Clause_set& s, Literal_choosing_heuristic h);

/**
 * Selects the variable (from a given mapping of variables to their respective
 * heuristic estimates) that has the highest estimate, i.E. the one that
 * ought to be selected according to the heuristic.
 *
 * @param heuristic_estimates   a mapping of variables to heuristic estimates
 *                              (this mapping should not have any negated
 *                               variables, i.E. those less than 0, in it)
 */
Literal
var_with_max_estimate(const std::map<Literal, float>& heuristic_estimates);

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
Clause_set
assign_literal(const Clause_set& s, Literal l);

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
std::set<Literal>
find_pure_literals(const Clause_set& s);

/**
 * Returns whether a given set of clauses is empty, i.E. contains no clauses.
 *
 * @param s the set of clauses
 * @return  whether s is empty
 */
bool
is_empty(const Clause_set& s);

/**
 * Returns whether a given set of clauses contains an empty clause.
 *
 * @param s the set of clauses
 * @return  whether {} in s
 */
bool
has_empty_clause(const Clause_set& s);

/**
 * Returns whether a given set of clauses contains a unit clause.
 *
 * @param s the set of clauses
 * @return  whether {l} in s
 */
bool
has_unit_clause(const Clause_set& s);

/**
 * Prints the given lead followed by the given set of clauses to allow us to
 * print the progress of the solving  process.
 *
 * @param lead  the string that ought to precede the clause set (generally this
 *              means the context that 'print_progress()' is called from)
 * @param s     the set of clauses
 */
void
print_progress(const std::string& lead, const Clause_set& s);

#endif
