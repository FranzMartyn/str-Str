#include "str.hpp"

// TODO: Create my own "memcopy" and "memoryalloc"

// Nebenziel: Diese Klasse frei von Abhängigkeiten zu bekommen

/* Notiz 
 * Weil es schwierig ist die länge eines char pointers herauszufinden, werden templates benutzt,
 * um zumindestens string literals benutzen zu können.
 * Grund: Es kann sein, dass ein Nullterminator am Anfang oder Mitten im string ist.
 */

namespace str {

	Str::Str() {
		data = new char {};
		length = 0;
		size = 0;
	}

	Str::Str(char c) {
		data = new char[1] {c};
		length = 1;
		size = 1;
	}

	Str::Str(char string[], unsigned long long size) {
		data = string;
		this->size = size;
		this->length = size;
	} 

	// String literals. Like `"this"`. Not variables.
	Str::Str(const char string[], unsigned long long size) {
		data = new char[size];
		for (int i = 0; i < size; ++i) {
			data[i] = string[i];
		}
		this->size = size;
		this->length = size;
	} 

	Str::Str(Str& str) {
		this->data = str.data;
		this->size = str.size;
		this->length = str.length;
	}

	// Delete data
	Str::~Str() {
	    delete[] data;
	}


	void Str::append(char c) {
		operator+=(c);
	}

	 void Str::append(char *string, unsigned long long length) {
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

	void Str::append(Str string) {
		operator+=(string);
	}

	char Str::get(unsigned long long index) {
		return data[index];
	}

	char* Str::c_str() {
		return data;
	}

	char* Str::unpack() {
		return data;
	}

	char* Str::unbox() {
		return data;
	}

	char* Str::unwrap() {
		return data;
	}

	void Str::clear() {
		data = new char[0]{};
		size = 0;
		length = 0;
	}

	unsigned long long Str::find(char c) {
		for (int i = 0; i < size; ++i) {
			if (data[i] == i) {
				return i;
			}
		}
		return -1;
	}

	void Str::insert(char c, unsigned long long index_at) {
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

	void Str::insert(const char *string, unsigned long long length, unsigned long long index_at) {
		char *old = this->data;
		this->data = new char[this->size+length];
		int offset = 0;
		for (int i = 0; i < this->size+1; ++i) {
			if (i == index_at) {
				for (int j = 0; j < length; ++j) {
					this->data[i+j] = string[j];
				}
				offset = length;
			}
			this->data[i+offset] = old[i];
		}
		this->size += length;
		this->length = this->size;
	}

	void Str::insert(Str string, unsigned long long index_at) {
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
	char* Str::substring(char *string, unsigned long long start_index, unsigned long long length) {
		char *temp = new char[length];
		for (int i = 0; i < length; ++i) {
			temp[i] = string[start_index+i];
		}
		return temp;
	}

	Str Str::substring(Str string, unsigned long long start_index, unsigned long long length) {
		return Str(substring(string.data, start_index, length), length);
	}

	Str Str::substring(unsigned long long start_index, unsigned long long length) {
		return Str(substring(*this, start_index, length));
	}

	bool Str::equals(char *string, unsigned long long length) {
		return array_equals(this->data, this->size, string, length);
	}

	bool Str::equals(Str string) {
		return operator==(string);
	}
	
	void Str::replace(char to_replace, char to_replace_with) {
		for (int i = 0; i < size; ++i) {
			if (data[i] == to_replace) {
				data[i] = to_replace_with;
			}
		}
	}

	void Str::replace(Str to_replace, Str to_replace_with) {
		for (int i = 0; i < size; ++i) {
			if (substring(*this, i, to_replace.size) == substring(to_replace, i, to_replace.size)) {
				// TODO
			}
		}
	}

	Str Str::operator+(char c) {
		char *temp = new char[this->size + 1];
		int i;
		for (i = 0; i < size; ++i) {
			temp[i] = this->data[i];
		}
		temp[i] = c;
		return Str(temp, size+1);
	}

	Str Str::operator+(Str string) {
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

	void Str::operator+=(char c) {
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

	void Str::operator+=(Str string) {
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

	char Str::operator[](unsigned long long index) {
		return data[index];
	}

	void Str::operator=(Str string) {
		this->data = string.data;
		this->size = string.size;
		this->length = string.length;
	}

	bool Str::operator==(char c) {
		if (size != 1) {
			return false;
		}
		return data[0] == c;
	}

	bool Str::operator==(Str right) {
		return array_equals(this->data, this->size, right.data, right.size);
	}

	bool Str::operator!=(char c) {
		if (size != 1) {
			return false;
		}
		return data[0] != c;
	}
	
	bool Str::operator!=(Str string) {
		return !operator==(string);
	}

	// if (Str("abc")) 
	Str::operator bool() {
		return size >= 1;
	}

	// Str("abc").times(3).c_str() == "abcabcabc"
	Str Str::operator*(unsigned long long times) {
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

	bool Str::array_equals(char *arr1, unsigned long long arr1_size, char *arr2, unsigned long long arr2_size) {
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
}
