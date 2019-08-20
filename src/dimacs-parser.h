#ifndef DIMACS_PARSER_H
#define DIMACS_PARSER_H

#include "dpll-basic.h"
#include <optional>
#include <string>

// TODO(ztf):
//  This probably should be restructured and rethought to somewhat efficiently
//  parse the input, be able to give the user detailed information in case of
//  errors as well as warnings about non-conformance with the DIMACS format
//  even when we can handle it. 

/**
 * Tells for a given line of (supposedly) DIMACS whether it should be
 * considered a comment, meaning whether it starts with 'c'. 
 *
 * @param line  the line of DIMACS 
 * @return      whether the line is considered a comment 
 */
bool
dimacs_line_is_comment(const std::string& line); 

std::optional<Clause>
parse_clause(std::string& clausestr);

#endif
