#define CATCH_CONFIG_MAIN

#include "../src/dpll-basic.h"
#include "catch2/catch.h"

TEST_CASE("propagate removes a unit clause", "[propagate_unit_clauses]")
{
  Clause_set input{ { 1 }, { 2, 3 }, { 4, 5, 6 } };
  Clause_set result{ { 2, 3 }, { 4, 5, 6 } };
  propagate_unit_clauses(input);
  REQUIRE(input == result);
}

TEST_CASE("propagate on empty returns empty", "[propagate_unit_clauses]")
{
  Clause_set input{};
  Clause_set result{};
  propagate_unit_clauses(input);
  REQUIRE(input == result);
}

TEST_CASE("unit propagation propagates until no unit-clauses remain",
          "[propagate_unit_clauses]")
{
  Clause_set input = {
    { 1, 2, 3, 4, 5 }, { 1, 2, 3, 4 }, { 1, 2, 3 }, { 1, 2 }, { 1 }
  };
  Clause_set result{};
  propagate_unit_clauses(input);
  REQUIRE(input == result);
}

TEST_CASE("larger test that used to cause a segfault", "[dpll]")
{
  Clause_set segfault_provoker = {
    { -4, -3, -2, -1 },   { -3, -1, 2, 4 },    { -4, -2, 1, 3 },
    { 1, 2, 3, 4 },       { -10, -9, -2, -1 }, { -9, -1, 2, 10 },
    { -10, -2, 1, 9 },    { 1, 2, 9, 10 },     { -6, -5, -2, -1 },
    { -5, -1, 2, 6 },     { -6, -2, 1, 5 },    { 1, 2, 5, 6 },
    { -18, -17, -2, -1 }, { -17, -1, 2, 18 },  { -18, -2, 1, 17 },
    { 1, 2, 17, 18 },     { -8, -7, -2, -1 },  { -7, -1, 2, 8 },
    { -8, -2, 1, 7 },     { 1, 2, 7, 8 },      { -26, -25, -2, -1 },
    { -25, -1, 2, 26 },   { -26, -2, 1, 25 },  { 1, 2, 25, 26 }
  };
  REQUIRE(dpll(segfault_provoker));
}

TEST_CASE("clause set with unit clause is correctly identified",
          "[has_unit_clause]")
{
  REQUIRE(has_unit_clause({ { 1, 2 }, { 3 }, { 4, 5 } }));
}

TEST_CASE("empty clause is not misidentified for unit clause",
          "[has_unit_clause]")
{
  REQUIRE(!has_unit_clause({ { 1, 2 }, {}, { 4, 5 } }));
}

TEST_CASE("clause set without unit clause is correctly identified",
          "[has_unit_clause]")
{
  REQUIRE(!has_unit_clause({ { 1, 2 }, { 3, 4 }, { 4, 5 } }));
}

TEST_CASE("empty clause set is correctly identified", "[has_unit_clause]")
{
  REQUIRE(!has_unit_clause({}));
}

TEST_CASE("elimination of pure literals", "[eliminate_pure_literals]")
{
  {
    Clause_set input{};
    Clause_set expectation{};
    eliminate_pure_literals(input);
    REQUIRE(input == expectation);
  }
  {
    Clause_set input{ {} };
    Clause_set expectation{ {} };
    eliminate_pure_literals(input);
    REQUIRE(input == expectation);
  }
  {
    Clause_set input{ { 1 } };
    Clause_set expectation{};
    eliminate_pure_literals(input);
    REQUIRE(input == expectation);
  }
  {
    Clause_set input{ { -1 } };
    Clause_set expectation{};
    eliminate_pure_literals(input);
    REQUIRE(input == expectation);
  }
  {
    Clause_set input{ { 1 }, { 2, 3 } };
    Clause_set expectation{};
    eliminate_pure_literals(input);
    REQUIRE(input == expectation);
  }
  {
    Clause_set input{ { 1 }, { -1 }, { 2 } };
    Clause_set expectation{ { 1 }, { -1 } };
    eliminate_pure_literals(input);
    REQUIRE(input == expectation);
  }
  {
    Clause_set input{ { 1 }, { -1, 2 }, { -2 } };
    Clause_set expectation{ { 1 }, { -1, 2 }, { -2 } };
    eliminate_pure_literals(input);
    REQUIRE(input == expectation);
  }
  {
    Clause_set input{ { -13, -8, -7 }, { -12, 1, 7 }, { -6, -5 },
                      { -4, 5, 10 },   { -4, 6, 11 }, { -3, -2, 4 },
                      { -1, 2 },       { -1, 3, 9 },  { 1, 8 } };
    Clause_set expectation{};
    eliminate_pure_literals(input);
    REQUIRE(input == expectation);
  }
}
