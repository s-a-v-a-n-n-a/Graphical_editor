#ifndef GRADIENT_BAR_H
#define GRADIENT_BAR_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"

#include "../GUI/Resource_manager.hpp"

#include "Color_picker.hpp"

extern const size_t PICKER_SIZE;

const size_t BAR_DEFAULT_WIDTH = 30;
const size_t DEFAULT_COLORS_AMOUNT = 7;
const Color COLOR_SEQUENCE[] = { BLACK, RED, FUCHSIA, BLUE, CYAN, GREEN, YELLOW };
const HSV DEFAULT_HSV = { 0, MAX_COLOR_VALUE, MAX_COLOR_VALUE };
const Color DEFAULT_COLOR = RED;

class Gradient_bar : public Visual_object
{
private:
	Color_picker *to_control;

	Magnetic *picker;

	// Color color_array[BAR_DEFAULT_WIDTH * MAX_COLOR_VALUE];
	size_t current_position;

public:
	Gradient_bar(const Visual_object::Config &par_base, Color_picker *par_to_control, const HSV &position_hsv = DEFAULT_HSV);

	Color get_color();

	void set_current_position(const Color &main_color);

	HSV get_hsv(const Color &rgb);

	// HSV_d get_hsv(const Color &rgb);

	Color get_rgb(const HSV &hsv);

	// Color get_rgb(HSV_d &hsv);

	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;

	void draw(Screen_information *screen) override;
	
	void tick(Screen_information *screen, const double delta_time) override;
};

#endif // GRADIENT_BAR_H
