#include<iostream>
#include "src/str.cpp"
#include "lib/catch_amalgamated.hpp"

int main() {
	str::Str a{"thing"};
	std::cout << a.c_str() << '\n';
	std::cout << "old size:" << a.size << '\n';
	a.insert("123", 3, 2);
	std::cout << "new size:" << a.size << '\n';
	std::cout << a.unbox() << '\n';
	std::cout << "123456789012345\n";
	std::cout << "at index " << a[11] << '\n';
	a += "Whatever";
	std::cout << a.unwrap() << '\n';
	std::cout << "substring, at 7, len=3: " << str::Str::substring(a.unpack(), 7, 3) << '\n';
}

// TODO:
// - Make the test run
// - Write more tests

TEST_CASE("All Constructors should create the same result") {
	REQUIRE( str::Str().equals(str::Str("", 0)) );

	char char_array_of_size_1[1] {'s'};
	REQUIRE( str::Str('s').equals(str::Str(char_array_of_size_1, 1)) );

	REQUIRE( str::Str(str::Str("some string", 11)).equals(str::Str("some string")) );
}

