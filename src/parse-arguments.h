#ifndef PARSE_ARGUMENTS_H
#define PARSE_ARGUMENTS_H

#include "cxxopts.h"
#include "dpll-basic.h"

struct Potato_SAT_settings
{
public:
  bool parsing_error = false; 
  bool print_progress = false;
  bool printed_help_msg = false;
  Literal_choosing_heuristic h = random_choice_heuristic;
  // TODO(ztf) lots missing here, gotta think up all the proper options etc
};

Potato_SAT_settings
parse(int, char**);

void
print_settings(Potato_SAT_settings& settings);

#endif
