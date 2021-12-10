#ifndef TEXT_STRING_H
#define TEXT_STRING_H

#include <cstdlib>

class Text_string
{
protected:
	char *string;
	size_t current_position;

	size_t size;
	size_t capacity;

public:
	Text_string(size_t par_size)
	: current_position(0), size(0), capacity(par_size)
	{
		string = new char[par_size];
		memset(string, 0, par_size);
	}

	void resize(size_t new_size)
	{
		char *new_string = new char[new_size];
		memset(new_string, 0, new_size);
		
		size_t limit = new_size > size ? size : new_size;
		for (size_t i = 0; i < limit; ++i)
		{
			new_string[i] = string[i];
		}

		delete [] string;

		string = new_string;
	}

	void set_position(const size_t par_position)
	{
		if (par_position > size)
			return;

		if (size + 1 >= capacity)
			resize(capacity * 2);

		current_position = par_position;
	}

	void add_symbol(const char symbol)
	{
		if (size + 1 >= capacity)
			resize(capacity * 2);

		size++;
		for (size_t i = current_position + 1; i < size; ++i)
		{
			string[i] = string[i - 1];
		}
		string[current_position] = symbol;

		set_position(current_position + 1);
	}

	void delete_symbol()
	{
		if (!current_position)
			return;

		for (size_t i = current_position + 1; i < size; ++i)
		{
			string[i - 1] = string[i];
		}
		size--;
		string[size] = 0;
		
		set_position(current_position - 1);
	}

	char *get_string()
	{
		return string;
	}

	size_t get_position()
	{
		return current_position;
	} 
};

#endif //TEXT_STRING_H
