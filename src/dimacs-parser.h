#ifndef DIMACS_PARSER_H
#define DIMACS_PARSER_H

#include "dpll-basic.h"
#include <optional>
#include <string>

bool
dimacs_line_is_comment(std::string& line); 

std::optional<Clause>
parse_clause(std::string& clausestr);

#endif
