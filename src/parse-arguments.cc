#include "parse-arguments.h"
#include "cxxopts.h"

Potato_SAT_settings
parse(int argc, char** argv)
{
  Potato_SAT_settings settings; 
  try {
    cxxopts::Options options(argv[0], "[idk what to put here...?]");
    options.positional_help("[optional args]").show_positional_help();

    bool print_progress = false; 

    options
      .add_options()
      ("p,print-progress", "Print the progess of the solving process", 
       cxxopts::value<bool>(print_progress)) 
      ("h,heuristic", "Variable choosing heuristic", 
       cxxopts::value<std::string>()->default_value("random"),"<heuristic>")
      ("help", "Print help")
    ;

    options.parse_positional({"input", "output"});

    auto result = options.parse(argc, argv);


    if (result.count("help")) {
      std::cout << options.help({ "" }) << std::endl;
      settings.printed_help_msg = true; 
    }

    if (print_progress) {
      settings.print_progress = true; 
    }

    if (result.count("heuristic")) {
      std::cout << "Saw option ‘heuristic’" << std::endl;
      auto& heuristic = result["heuristic"].as<std::string>();
      std::cout << "–– gives: " << heuristic << std::endl;
    }

  } catch (const cxxopts::OptionException& e) {
    std::cout << "error parsing options: " << e.what() << std::endl;
    settings.parsing_error = true; 
  }
  return settings;
}


void
print_settings(Potato_SAT_settings& settings)
{
  std::cout << "Settings:" << '\n' 
            << "  * " 
            << (settings.print_progress ? "" : "not ") << "printing progress"
            // TODO(ztf) more settings
            << std::endl; 
}
