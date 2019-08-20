#ifndef DIMACS_PARSER_H
#define DIMACS_PARSER_H

#include "dpll-basic.h"
#include <optional>
#include <string>

inline int variable_number; 
inline int clause_number; 

// TODO(ztf):
//  This probably should be restructured and rethought to somewhat efficiently
//  parse the input, be able to give the user detailed information in case of
//  errors as well as warnings about non-conformance with the DIMACS format
//  even when we can handle it.

enum DIMACS_line_type
{
  comment,
  problem,
  clause,
  unrecognized
};

/**
 * Tells for a given line of (supposedly) DIMACS whether it should be
 * considered a comment, meaning whether it starts with 'c'.
 *
 * @param line  the line of DIMACS
 * @return      whether the line is considered a comment
 */
bool
is_comment(const std::string& line);

bool
is_problem_line(const std::string& line);

void
parse_problem_line(std::string& line); 

DIMACS_line_type
parse_dimacs_line(std::string& clausestr, Clause& clause_buf);

bool
read_in_dimacs_file(std::string file_location, Clause_set& clause_set_buf);

#endif
