#ifndef CLAUSE_H 
#define CLAUSE_H

#include <set>
#include <iostream>
#include "literal.h"

/**
 * A `Clause` is set of `Literal`s implicitly connected by the logical "or". 
 */
class Clause {
  private:
    /** The set of literals making up the clause */ 
    std::set<Literal> literals; 
  public:
    /** 
     * Constructor for a new empty clause. 
     */ 
    Clause(void);
    /** 
     * Getter for the set of literals. 
     *
     * @return  the set of literals
     */
    std::set<Literal> get_literals(void) const;
    /**
     * Adds a literal to this clause. 
     * If this clause already contains that literal, it remains as-is.
     * 
     * @param   the (possibly new) `Literal`
     */
    void add(Literal literal); 
};

/**
 * Overload of the operator `==` to allow for equality comparisons of two
 * `Clause`s.
 *
 * @param lhs the left side of the equality comparison 
 * @param rhs the right side of the equality comparison 
 * @return    whether two given `Clause`s are considered equal
 */
bool operator==(const Clause& lhs, const Clause& rhs); 

/**
 * Overload `<<` to directly put a `Clause` to an `std::ostream` 
 * (such as `std::cout`). 
 *
 * @param output  the `std::ostream` prior to putting the `Literal` to it
 * @param clause  the `Clause` to be put to the `std::ostream` 
 * @return        the `std::ostream` with the given `Clause` added to it
 */
std::ostream& operator<<(std::ostream& output, const Clause& clause);

#endif 
