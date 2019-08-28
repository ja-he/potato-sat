#include "parse-arguments.h"
#include "cxxopts.h"

Potato_SAT_settings
parse(int argc, char** argv)
{

  Potato_SAT_settings settings;

  try {

    // we use cxxopts here to get the options, be able to print a help message
    // easily etc, but then we use the settings we find that way and store them
    // in our own format to return that back to main.

    cxxopts::Options options(argv[0], "`potato-sat` - a simple SAT solver");
    options.positional_help("[optional args]").show_positional_help();

    bool print_progress = false;

    options
      .add_options()
      ("p,print-progress", "Print the progess of the solving process", 
       cxxopts::value<bool>(print_progress)) 
      ("h,heuristic", "Variable choosing heuristic", 
       cxxopts::value<std::string>()->default_value("random"),"<heuristic>")
      ("i,input-file", "Read from a given <file> instead of STDIN", 
       cxxopts::value<std::string>(),"<file>") 
      ("help", "Print help")
    ;

    options.parse_positional({ "input", "output" });

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
      std::cout << options.help({ "" }) << std::endl;
      settings.printed_help_msg = true;
    }
    if (print_progress) {
      settings.print_progress = true;
    }
    if (result.count("heuristic")) {
      auto& heuristic_name = result["heuristic"].as<std::string>();

      // the switch stmt doesn't work on strings...? 
      // TODO(ztf) this needs to improved and extended
      if (heuristic_name == "r") {
        settings.heuristic = random_choice_heuristic; 
      } else if (heuristic_name == "j") {
        settings.heuristic = jerosolow_wang_heuristic;
      } else {
        settings.heuristic = random_choice_heuristic; 
      }
    }
    if (result.count("input-file")) {
      settings.read_file = true;
      settings.file_location = result["input-file"].as<std::string>();
    }

  } catch (const cxxopts::OptionException& e) {
    std::cout << "error parsing options: " << e.what() << std::endl;
    // If an error occurs, we set parsing_error.
    // This is the first thing we check in main, thus we don't have to worry
    // about using unintended other values that we didn't fill the struct with.
    settings.parsing_error = true;
  }
  return settings;
}

void
print_settings(Potato_SAT_settings& settings)
{
  std::cout << "Settings:" << '\n'
            << "  * " << (settings.print_progress ? "" : "not ")
            << "printing progress"
            // TODO(ztf) more settings
            << std::endl;
}
