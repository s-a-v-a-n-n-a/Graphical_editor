#ifndef TOOLS_H 
#define TOOLS_H

#include "../simple_list/simple_list.hpp"
#include "../sfml_drawing/colors.hpp"
#include "../sfml_drawing/screen_functions.hpp"

// #include "../EditorCanvas.hpp"

const Color DEFAULT_TOOL_COLOR = BLACK;
const size_t DEFAULT_TOOL_SIZE = 20;

class Tool
{
protected:
	bool pressed;

	Color *data;
	Vector_ll data_params;

	Color color;
	size_t size;

	char *name;

public:
	Tool();
	Tool(const char *par_name);
	virtual ~Tool();

	virtual void set_color(const Color &par_color) { color = par_color; }
	virtual void set_size(const size_t par_size) { size = par_size; }

	virtual Color get_color() { return color; }
	virtual size_t get_size() { return size; }
	virtual char *get_name() { return name; }
	virtual Color *get_pixels() { return data; }
	virtual Vector_ll get_params() { return data_params; }

	// virtual void apply(Canvas *to_apply, const Vector_ll &position) = 0;
	virtual void apply(Color *to_apply, const Vector_ll &parameters, const Vector_ll &position) = 0;
	virtual void set_data(Color *to_apply, const Vector_ll &parameters);
	virtual void release_data();

	virtual void on_mouse_move(const Vector_ll &from, const Vector_ll &to);
	virtual void on_mouse_press(Color *to_apply, const Vector_ll &parameters, const Vector_ll &position);
	virtual void on_mouse_release(const Vector_ll &position);
};

#endif // TOOLS_H
