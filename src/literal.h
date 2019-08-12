#ifndef LITERAL_H
#define LITERAL_H

#include <iostream>
#include "atom.h"

/**
 * A `Literal` is a possibly negated atom. 
 */
class Literal {

  private: 
    /** The atom that is part of this literal */ 
    Atom atom; 
    /** Whether this literal is the atom or the negated atom */ 
    bool negated; 

  public:
    /** 
     * Constructor of a `Literal` for a given `Atom` and a boolean value
     * indicating whether it should be negated. 
     */
    Literal(Atom _atom, bool _negated); 

    /**
     * Getter for the underlying atom. 
     *
     * @return  the `Atom` of this literal. 
     */
    Atom get_atom(void) const; 

    /**
     * Getter for the negation. 
     *
     * @return  whether this `Literal` is a negation of the atom. 
     */
    bool is_negated(void) const;
};

/**
 * Overload `==` to compare `Literal`s.
 *
 * @param lhs the left side of the equality comparison 
 * @param rhs the right side of the equality comparison 
 * @return    whether two given `Literal`s are considered equal 
 */
bool operator==(const Literal& lhs, const Literal& rhs);

/**
 * Overload of ordering relation `<`. 
 *
 * @whether the left literal is smaller than the right
 */
bool operator<(const Literal& lhs, const Literal& rhs);

/**
 * Overload `<<` to directly put a `Literal` to an `std::ostream` 
 * (such as `std::cout`). 
 *
 * @param output  the `std::ostream` prior to putting the `Literal` to it
 * @param literal the `Literal` to be put to the `std::ostream` 
 * @return        the `std::ostream` with the given `Literal` added to it
 */
std::ostream& operator<<(std::ostream& output, const Literal& literal);

#endif
