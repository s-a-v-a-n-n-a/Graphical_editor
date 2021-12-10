#ifndef PALETTE_H
#define PALETTE_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button_manager.hpp"
#include "../GUI/Resource_manager.hpp"
// #include "../GUI/Button.hpp"

#include "Graphical_delegates.hpp"
#include "Window.hpp"

// #include "Color_picker.hpp"
// #include "Gradient_bar.hpp"
#include "Color_selection.hpp"

class Palette : public Closing_window
{
private:
	Color chosen_color;

	// Color_picker *picker;
	// Gradient_bar *gradient_bar;
	Color_selection_window *color_picker;

	Button *old_color;
	Button *new_color;
	Button *ok_button;

public:
	Palette(const Visual_object::Config &par_base, const Color &par_chosen_color = DEFAULT_COLOR);

	// Color_picker *create_color_picker(const Vector_ll &position, const size_t width, const size_t height, const Color &color = DEFAULT_COLOR);
	// Gradient_bar *create_gradient_bar(const Vector_ll &position, const size_t width, const size_t height, Color_picker *picker, const HSV &hsv = DEFAULT_HSV);

	Color_selection_window *create_color_selection_widget(const Vector_ll &position, const size_t width, const size_t height, const Color &color = DEFAULT_COLOR);

	void draw(Screen_information *screen) override;
	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

#endif // PALETTE_H
