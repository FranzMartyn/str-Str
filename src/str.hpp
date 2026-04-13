#pragma once

namespace str {
	class Str {
	
public:
		unsigned long long length;
		unsigned long long size;
	
		Str();
		Str(char c);
		Str(char string[], unsigned long long size);
		Str(const char string[], unsigned long long size);
		template<unsigned long long LENGTH>
		Str(const char (&string)[LENGTH]);
		Str(Str& str);
		~Str();

	
		void append(char c);
		void append(char *string, unsigned long long length);
		template<unsigned long long LENGTH>
		void append(const char (&string)[LENGTH]);
		void append(Str string);
	
		char get(unsigned long long index);
	
		char* c_str();
		char* unpack();
		char* unbox();
		char *unwrap();
	
		void clear();
	
		unsigned long long find(char c);

		void insert(char c, unsigned long long index_at);
		template<unsigned long long LENGTH>
		void insert(const char (&string)[LENGTH], unsigned long long index_at);
		void insert(const char *string, unsigned long long length, unsigned long long index_at);
		void insert(Str string, unsigned long long index_at);
	
		static char *substring(char *string, unsigned long long start_index, unsigned long long length);
		static Str substring(Str string, unsigned long long start_index, unsigned long long length);
		Str substring(unsigned long long start_index, unsigned long long length);

		bool equals(char *string, unsigned long long length);
		bool equals(Str string);
		
		void replace(char to_replace, char to_replace_with);
		template<unsigned long long STRING_LENGTH_1, unsigned long long STRING_LENGTH_2>
		void replace(const char (&to_replace)[STRING_LENGTH_1], const char (&to_replace_with)[STRING_LENGTH_2]);
		void replace(Str to_replace, Str to_replace_with);
	
		Str operator+(char c);
		template<unsigned long long LENGTH>
		Str operator+(const char (&string)[LENGTH]);
		Str operator+(Str string);
	
		void operator+=(char c);

		template<unsigned long long LENGTH>
		void operator+=(const char (&string)[LENGTH]);

		void operator+=(Str string);
	
		char operator[](unsigned long long index);

		template<unsigned long long LENGTH>
		void operator=(const char (&string)[LENGTH]);
		void operator=(Str string);

		bool operator==(char c);
		bool operator==(Str right);
		template<unsigned long long LENGTH>
		bool operator==(const char (&right)[LENGTH]);

		bool operator!=(char c);
		template<unsigned long long LENGTH>
		bool operator!=(const char (&string)[LENGTH]);
		bool operator!=(Str string);
	
		// if (Str("abc")) 
		operator bool();
	
		// Str("abc") * 3 == "abcabcabc"
		Str operator*(unsigned long long times);
	
private:
		char *data;
		
		static bool array_equals(char *arr1, unsigned long long arr1_size, char *arr2, unsigned long long arr2_size);
	};
}

#include "str.tpp"
