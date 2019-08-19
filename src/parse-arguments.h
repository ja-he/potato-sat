#ifndef PARSE_ARGUMENTS_H
#define PARSE_ARGUMENTS_H

#include "cxxopts.h"
#include "dpll-basic.h"

struct Potato_SAT_settings
{
public:
  bool print_progress = false; 
  Literal_choosing_heuristic h = random_choice_heuristic; 
  // TODO(ztf) lots missing here, gotta think up all the proper options etc
};

cxxopts::ParseResult
parse(int, char**);

Potato_SAT_settings
find_settings(int, char**);

void
print_settings(Potato_SAT_settings& settings);

#endif
