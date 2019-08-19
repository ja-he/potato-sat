#define CATCH_CONFIG_MAIN

#include "../src/dpll-basic.h"
#include "catch2/catch.h"

TEST_CASE("propagate should remove unit clause", "[propagate_unit_clauses]")
{
  Clause_set input{ { 1 }, { 2, 3 }, { 4, 5, 6 } };
  Clause_set result{ { 2, 3 }, { 4, 5, 6 } };
  propagate_unit_clauses(input);
  REQUIRE(input == result);
}

TEST_CASE("propagate on empty should return empty", "[propagate_unit_clauses]")
{
  Clause_set input{ };
  Clause_set result{ }; 
  propagate_unit_clauses(input);
  REQUIRE(input == result);
}
