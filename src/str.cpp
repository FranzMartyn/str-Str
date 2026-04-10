#pragma once
#include<iostream>

// TODO: Create my own "memcopy" and "memoryalloc"

// Nebenziel: Diese Klasse frei von Abhängigkeiten zu bekommen

/* Notiz 
 * Weil es schwierig ist die länge eines char pointers herauszufinden, werden templates benutzt,
 * um zumindestens string literals benutzen zu können
 * Grund: Es kann sein, dass ein Nullterminator am Anfang oder mitten im string ist.
 */

namespace str {
	class Str {
	
public:
	
		unsigned long long length;
		unsigned long long size;
	
		Str() {
			data = new char {};
			length = 0;
			size = 0;
		}
	
		Str(char c) {
			data = new char[1] {c};
			length = 1;
			size = 1;
		}
	
		Str(char string[], unsigned long long size) {
			data = string;
			this->size = size;
			this->length = size;
		} 

		// String literals. Like `"this"`. Not variables.
		Str(const char string[], unsigned long long size) {
			data = new char[size];
			for (int i = 0; i < size; ++i) {
				data[i] = string[i];
			}
			this->size = size;
			this->length = size;
		} 

		// Claude told me that I can use a template for string literals
		// This makes `Str() += "string literal"` possible
		template<unsigned long long LENGTH>
		Str(const char (&string)[LENGTH]) {
			data = new char[LENGTH - 1];
			for (int i = 0; i < LENGTH - 1; ++i) {
				data[i] = string[i];
			}
			size = LENGTH - 1;
			length = size;
		}
	
		Str (Str &str) {
			this->data = str.data;
			this->size = str.size;
			this->length = str.length;
		}

		// Delete data
		~Str() {
		    delete[] data;
		}

	
		void append(char c) {
			operator+=(c);
		}
	
		 void append(char *string, unsigned long long length) {
			char *temp = data;
			this->data = new char[this->size + length];
	
			for (int i = 0; i < size; ++i) {
				this->data[i] = temp[i];
			}
			for (int i = 0; i < length; ++i) {
				this->data[this->size+i] = string[i];
			}
			++this->size;
			++this->length;
		 }

		template<unsigned long long LENGTH>
		void append(const char (&string)[LENGTH]) {
			append(string, LENGTH);
		}
	
		void append(Str string) {
			operator+=(string);
		}
	
		char get(unsigned long long index) {
			return data[index];
		}
	
		char* c_str() {
			return data;
		}
	
		char* unpack() {
			return data;
		}

		char* unbox() {
			return data;
		}

		char *unwrap() {
			return data;
		}
	
		void clear() {
			data = new char[0]{};
			size = 0;
			length = 0;
		}
	
		unsigned long long find(char c) {
			for (int i = 0; i < size; ++i) {
				if (data[i] == i) {
					return i;
				}
			}
			return -1;
		}
	
		void insert(char c, unsigned long long index_at) {
			char *old = this->data;
			data = new char[this->size+1];
			int offset = 0;
			for (int i = 0; i < this->size+1; ++i) {
				if (i == index_at) {
					data[i] = c;
					offset = 1;
					continue;
				}
				data[i+offset] = old[i];
			}
		}

		template<unsigned long long LENGTH>
		void insert(const char (&string)[LENGTH], unsigned long long index_at) {
			insert(string, LENGTH, index_at);
		}

		void insert(const char *string, unsigned long long length, unsigned long long index_at) {
			char *old = this->data;
			this->data = new char[this->size+length];
			int offset = 0;
			for (int i = 0; i < this->size+1; ++i) {
				if (i == index_at) {
					for (int j = 0; j < length; ++j) {
						this->data[i+j] = string[j];
						std::cout << "this->data == " << this->data << '\n';
					}
					offset = length;
				}
				std::cout << "old=" << old << '\n';
				this->data[i+offset] = old[i];
				std::cout << "this->data == " << this->data << "| i = " << i << "; i+offset=" << i+offset << '\n';
			}
			this->size += length;
			this->length = this->size;
		}
	
		void insert(Str string, unsigned long long index_at) {
			char *old = this->data;
			this->data = new char[this->size+string.size];
			int offset = 0;
			for (int i = 0; i < this->size+1; ++i) {
				if (i == index_at) {
					for (int j = 0; j < string.size; ++j) {
						data[i+j] = string[j];
						++offset;
					}
				}
				data[i+offset] = old[i];
			}
			this->size += string.size;
			this->length = size;
		}
	
		// Assuming that both start_index and length are valid.
		// This one is not dropped because the length is given.
		static char *substring(char *string, unsigned long long start_index, unsigned long long length) {
			char *temp = new char[length];
			for (int i = 0; i < length; ++i) {
				temp[i] = string[start_index+i];
			}
			return temp;
		}
	
		static Str substring(Str string, unsigned long long start_index, unsigned long long length) {
			return Str(substring(string.data, start_index, length), length);
		}

		Str substring(unsigned long long start_index, unsigned long long length) {
			return Str(substring(*this, start_index, length));
		}

		bool equals(char *string, unsigned long long length) {
			return array_equals(this->data, this->size, string, length);
		}
	
		bool equals(Str string) {
			return operator==(string);
		}
		
		void replace(char to_replace, char to_replace_with) {
			for (int i = 0; i < size; ++i) {
				if (data[i] == to_replace) {
					data[i] = to_replace_with;
				}
			}
		}

		template<unsigned long long STRING_LENGTH_1, unsigned long long STRING_LENGTH_2>
		void replace(const char (&to_replace)[STRING_LENGTH_1], const char (&to_replace_with)[STRING_LENGTH_2]) {
			// TODO
		}
	
		void replace(Str to_replace, Str to_replace_with) {
			for (int i = 0; i < size; ++i) {
				if (substring(*this, i, to_replace.size) == substring(to_replace, i, to_replace.size)) {
					// TODO
				}
			}
		}
	
		Str operator+(char c) {
			char *temp = new char[this->size + 1];
			int i;
			for (i = 0; i < size; ++i) {
				temp[i] = this->data[i];
			}
			temp[i] = c;
			return Str(temp, size+1);
		}
	
		template<unsigned long long LENGTH>
		Str operator+(const char (&string)[LENGTH]) {
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
	
		Str operator+(Str string) {
			char *temp = new char[this->size + string.size];
	
			// Eigentlich wäre hier memcpy() gut, aber ich will diese Klasse Abhängigkeitsfrei halten...
			for (int i = 0; i < size; ++i) {
				temp[i] = this->data[i];
			}
			for (int i = 0; i <= string.size; ++i) {
				temp[this->size+i] = string[i];
			}
			return Str(temp, this->size + string.size);
		}
	
		void operator+=(char c) {
			char *temp = data;
			this->data = new char[this->size + 1];
	
			int i;
			for (i = 0; i < size; ++i) {
				this->data[i] = temp[i];
			}

			this->data[i] = c;
			++(this->size);
			++(this->length);
		}
	
		template<unsigned long long LENGTH>
		void operator+=(const char (&string)[LENGTH]) {
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
	
		void operator+=(Str string) {
			char *temp = data;
			this->data = new char[this->size + string.size];
	
			// Eigentlich wäre hier memcpy() gut, aber ich will diese Klasse Abhängigkeitsfrei halten...
			for (int i = 0; i < this->size; ++i) {
				this->data[i] = temp[i];
			}
			for (int i = 0; i <= string.size; ++i) {
				this->data[this->size+i] = string[i];
			}

			this->size += string.size;
			this->length = this->size;
		}
	
		char operator[](unsigned long long index) {
			return data[index];
		}

		template<unsigned long long LENGTH>
		bool operator=(const char (&string)[LENGTH]) {
			data = string;
			size = LENGTH;
			length = LENGTH;
		}
	
		void operator=(Str string) {
			this->data = string.data;
			this->size = string.size;
			this->length = string.length;
		}
	
		bool operator==(char c) {
			if (size != 1) {
				return false;
			}
			return data[0] == c;
		}

		bool operator==(Str right) {
			return array_equals(this->data, this->size, right.data, right.size);
		}

		// For string constants
		template<unsigned long long LENGTH>
		bool operator==(const char (&right)[LENGTH]) {
			return array_equals(this->data, this->size, right.data, LENGTH);
		}

		bool operator!=(char c) {
			return data[0] != c;
		}

		template<unsigned long long LENGTH>
		bool operator!=(const char (&string)[LENGTH]) {
			return !operator==(string);
		}
		
		bool operator!=(Str string) {
			return !operator==(string);
		}
	
		// if (Str("abc")) 
		operator bool() {
			return size >= 1;
		}
	
		// Str("abc").times(3).c_str() == "abcabcabc"
		Str operator*(unsigned long long times) {
			char *old = data;
			data = new char[size*times];
			int newest_index = 0;
			for (int iteration = 0; iteration < times; ++iteration) {
				for (int i = 0; i < size; ++i, ++newest_index) {
					data[newest_index] = old[i];
				}
			}
			size *= times;
			length *= times;
			return *this;
		}
	
private:
		char *data;

		static bool array_equals(char *arr1, unsigned long long arr1_size, char *arr2, unsigned long long arr2_size) {
			if (arr1_size != arr2_size) {
				return false;
			}
	
			for (int i = 0; i < arr1_size; ++i) {
				if (arr1[i] != arr2[i]) {
					return false;
				}
			}
			return true;
		}
	
	};
}
