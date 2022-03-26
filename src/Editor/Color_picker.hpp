#ifndef COLOR_TABLE_H
#define COLOR_TABLE_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"
#include "../GUI/Resource_manager.hpp"

#include "Graphical_delegates.hpp"

extern const size_t DEFAULT_POINTER_RADIUS;

class Color_picker : public Visual_object
{
private:
	// Gradient_bar *hues;
	Color *to_set;

	Magnetic *picker;

	Color *color_array;
	Color main_color;

	Vector_ll current_position;

public:
	Color_picker(const Visual_object::Config &par_base, const Color &par_main_color = RED, Color *par_to_set = NULL);
	~Color_picker();

	void set_main_color(const Color &par_main);
	// void set_hues_bar(Gradient_bar *par_hues);

	Color get_color();
	void set_color();

	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
	void draw(Screen_information *screen) override;
};

#endif // COLOR_TABLE_H
