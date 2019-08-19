#include "cxxopts.h"
#include "dpll-basic.h"
#include <iostream>
#include <set>





cxxopts::ParseResult
parse(int argc, char* argv[])
{
  try {
    cxxopts::Options options(argv[0], " - example command line options");
    options.positional_help("[optional args]").show_positional_help();

    bool print_progress = false; 

    options
      .add_options()
      ("p,print-progress", "Print the progess of the solving process", 
       cxxopts::value<bool>(print_progress)) 
      ("h,heuristic", "Variable choosing heuristic", 
       cxxopts::value<std::string>()->default_value("random"),"<heuristic>")
      ("f, file", "File", cxxopts::value<std::string>(), "FILE")
      ("i,input", "Input", cxxopts::value<std::string>())
      ("o,output", "Output file", cxxopts::value<std::string>()
          ->default_value("a.out")->implicit_value("b.def"), "BIN")
      ("help", "Print help")
    ;

    options.parse_positional({"input", "output"});

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
      std::cout << options.help({ "" }) << std::endl;
      exit(0);
    }

    if (print_progress) {
      std::cout << "printing progress..." << std::endl;
    }

    if (result.count("heuristic")) {
      std::cout << "Saw option ‘heuristic’" << std::endl;
      auto& heuristic = result["heuristic"].as<std::string>();
      std::cout << "–– gives: " << heuristic << std::endl;
    }

    if (result.count("f")) {
      auto& ff = result["f"].as<std::string>();
      std::cout << "Files" << std::endl;
      std::cout << ff << std::endl;
    }

    if (result.count("input")) {
      std::cout << "Input = " << result["input"].as<std::string>() << std::endl;
    }

    if (result.count("output")) {
      std::cout << "Output = " << result["output"].as<std::string>()
                << std::endl;
    }

    return result;

  } catch (const cxxopts::OptionException& e) {
    std::cout << "error parsing options: " << e.what() << std::endl;
    exit(1);
  }
}



int
main(int argc, char* argv[])
{

  auto result = parse(argc, argv);
  auto arguments = result.arguments();
  std::cout << "Saw " << arguments.size() << " arguments" << std::endl;

  /*
  Clause_set s{ { -1, 2 },     { -1, 3, 9 },  { -2, -3, 4 },
                { -4, 5, 10 }, { -4, 6, 11 }, { -5, -6 },
                { 1, 7, -12 }, { 1, 8 },      { -7, -8, -13 } };
  std::cout << ((dpll(s)) ? "SAT" : "UNSAT") << std::endl;
  */

  return 0;
}
