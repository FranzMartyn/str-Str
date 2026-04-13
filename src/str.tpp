#pragma once
#include "str.hpp"

// The reason why this file exists is:
// https://stackoverflow.com/a/495056

// str.hpp includes this file at the very end

namespace str {
	// Claude told me that I can use a template for string literals
	// This makes `Str() += "string literal"` possible
	template<unsigned long long LENGTH>
	Str::Str(const char (&string)[LENGTH]) {
		data = new char[LENGTH - 1];
		for (int i = 0; i < LENGTH - 1; ++i) {
			data[i] = string[i];
		}
		size = LENGTH - 1;
		length = size;
	}

	template<unsigned long long LENGTH>
	void Str::append(const char (&string)[LENGTH]) {
		append(string, LENGTH); 
	}

	template<unsigned long long LENGTH>
	void Str::insert(const char (&string)[LENGTH], unsigned long long index_at) {
		insert(string, LENGTH, index_at);
	}

	template<unsigned long long STRING_LENGTH_1, unsigned long long STRING_LENGTH_2>
	void Str::replace(const char (&to_replace)[STRING_LENGTH_1], const char (&to_replace_with)[STRING_LENGTH_2]) {
		// TODO
	}

	template<unsigned long long LENGTH>
	Str Str::operator+(const char (&string)[LENGTH]) {
		char *temp = new char[this->size + LENGTH];

		// Eigentlich wäre hier memcpy() gut, aber ich will diese Klasse Abhängigkeitsfrei halten...
		for (int i = 0; i < size; ++i) {
			temp[i] = this->data[i];
		}
		for (int i = 0; i <= LENGTH; ++i) {
			temp[this->size+i] = string[i];
		}
		return Str(temp, this->size+LENGTH);
	}

	template<unsigned long long LENGTH>
	void Str::operator+=(const char (&string)[LENGTH]) {
		char *temp = data;
		this->data = new char[this->size + LENGTH];

		// Eigentlich wäre hier memcpy() gut, aber ich will diese Klasse Abhängigkeitsfrei halten...
		for (int i = 0; i < size; ++i) {
			this->data[i] = temp[i];
		}
		for (int i = 0; i <= LENGTH; ++i) {
			this->data[this->size+i] = string[i];
		}
		this->size += LENGTH;
		this->length = this->size;
	}

	template<unsigned long long LENGTH>
	void Str::operator=(const char (&string)[LENGTH]) {
		data = string;
		size = LENGTH;
		length = LENGTH;
	}

	// For string constants
	template<unsigned long long LENGTH>
	bool Str::operator==(const char (&right)[LENGTH]) {
		return array_equals(this->data, this->size, right.data, LENGTH);
	}

	template<unsigned long long LENGTH>
	bool Str::operator!=(const char (&string)[LENGTH]) {
		return !operator==(string);
	}
}
