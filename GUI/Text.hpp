#ifndef TEXT_CLASS
#define TEXT_CLASS

#include <cstring>

#include "Visual_object_base.hpp"

class Text : public Visual_object
{
private:
	// List<Visual_object*> objects;

	// Vector_ll position;
	// Color color;

	// size_t width;
	// size_t height;

	// bool active;

	// char *font_file; 
	bool was_drawn;
	size_t font_size; 

	char *text;

public:
	Text(const size_t par_type, const char *par_text, const size_t par_font_size, const Vector_ll &par_position, const Color &par_color)
	: Visual_object({par_type, par_position, nullptr, par_color, strlen(par_text), par_font_size})
	{
		set_color(par_color);

		font_size = par_font_size;

		text = new char[strlen(par_text) + 1];
		strcpy(text, par_text);

		was_drawn = false;
	}

	~Text()
	{
		delete [] text;
	}

	void set_text(const char *par_text)
	{
		strcpy(text, par_text);
	}

	void set_font_size(const size_t par_font_size) { font_size = par_font_size; }

	void draw(Screen_information *screen) override
	{
		screen->draw_text(text, get_position(), get_color(), font_size);
	}
};

#endif // TEXT_CLASS
