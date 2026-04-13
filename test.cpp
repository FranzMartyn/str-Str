#include<iostream>
#include "src/str.hpp"

#include "lib/catch_amalgamated.hpp"

// TODO:
// - Write more tests

TEST_CASE("Constructors") {
	std::cout << "RUNNING THE 'Constructors' TEST_CASES!!!!\n";
	REQUIRE( str::Str().equals(str::Str("", 0)) );
	//REQUIRE( str::Str().equals(str::Str("a", 1)) );  // This should fail
	REQUIRE( str::Str('s').equals(str::Str( new char[1] {'s'} , 1)) );
	REQUIRE( str::Str(str::Str("some string", 11)).equals(str::Str("some string")) );
}

