#ifndef SETTINGS_H
#define SETTINGS_H

#include "dpll-basic-defs.h"

inline bool print_progress_basic_dpll;

inline Literal_choosing_heuristic heuristic_to_choose_by;

/**
 * Encapsulates the settings that the user may or may not set.
 */
struct Potato_SAT_settings
{
public:
  /** Whether a parsing error occurred (and thus main() should exit) */
  bool parsing_error = false;
  /** Whether the progress of the solving process is to be printed to STDOUT */
  bool print_progress = false;
  /** Whether a help message was printed (and thus main() should exit) */
  bool printed_help_msg = false;
  /** Whether the reading of a file was requested */
  bool read_file = false;
  /** The location of the requested file (empty if no file read requested) */
  std::string file_location;
  /** The heuristic by which to choose literals */
  Literal_choosing_heuristic heuristic = random_choice_heuristic;
  // TODO(ztf) lots missing here, gotta think up all the proper options etc
};

#endif
