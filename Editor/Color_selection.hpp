#ifndef TOOLS_VIDGET_H
#define TOOLS_VIDGET_H

#include "../GUI/Visual_object_base.hpp"

#include "Color_picker.hpp"
#include "Gradient_bar.hpp"

class Color_selection_window : public Visual_object
{
private:
	Color chosen_color;

	Color_picker *picker;
	Gradient_bar *gradient_bar;

public:
	Color_selection_window() = delete;
	Color_selection_window(const Visual_object::Config &par_base, const Color &color = DEFAULT_COLOR);
	~Color_selection_window() = default;

	Color_picker *create_color_picker(const Vector_ll &position, const size_t width, const size_t height, const Color &color = DEFAULT_COLOR);
	Gradient_bar *create_gradient_bar(const Vector_ll &position, const size_t width, const size_t height, Color_picker *picker, const HSV &hsv = DEFAULT_HSV);

	Color_picker *get_color_picker() { return picker; }
	Gradient_bar *get_gradient_bar() { return gradient_bar; }

	Color get_color() { return chosen_color; }
};

#endif // TOOLS_VIDGET_H
