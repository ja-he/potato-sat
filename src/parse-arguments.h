#ifndef PARSE_ARGUMENTS_H
#define PARSE_ARGUMENTS_H

#include "cxxopts.h"
#include "settings.h"

/**
 * Creates a set of settings corresponding to the the user's given input.
 *
 * @param argc  the argument count as it comes from main()
 * @param argv  the argumens as they come from main()
 * @return      the settings corresponding to the user arguments
 */
Potato_SAT_settings
parse(int argc, char** argv);

/**
 * Prints out the settings it is given.
 *
 * @param settings the settings
 */
void
print_settings(Potato_SAT_settings& settings);

#endif
