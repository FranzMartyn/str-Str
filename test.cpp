#include<iostream>
#include "src/str.cpp"

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
	//std::cout << "substring, at 7, len=3: " << str::Str::substring(a.unpack(), 7, 3) << '\n';
}
