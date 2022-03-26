#include "Color_selection.hpp"
#include "Application.hpp"

Color_selection_window::Color_selection_window(const Visual_object::Config &par_base, const Color &color)
: Visual_object(par_base), chosen_color(color)
{
	size_t picker_size = (get_height() - 20); // * 3 / 4;
	picker_size = get_width() < picker_size ? get_width() : picker_size;
	HSV hsv = get_hsv(color);
    Color picker_color = RED;
    if (hsv.h != 0)
    	picker_color = get_rgb({hsv.h, 255, 255});


	picker = create_color_picker(get_position() + Vector_ll(10, 20), get_width() - 20, picker_size, picker_color);// new Color_picker(this, (size_t)Vidget_type::COLOR_PICKER, par_position + Vector_ll(10, (offset + 30)), TRANSPARENT, MAX_COLOR_VALUE, MAX_COLOR_VALUE, par_pencil);
    gradient_bar = create_gradient_bar(get_position() + Vector_ll(10, 0), get_width() - 20, 20, picker, hsv);// 
}

Color_picker *
Color_selection_window::create_color_picker(const Vector_ll &position, const size_t width, const size_t height, const Color &color)
{
	Visual_object::Config picker_base = { this, (size_t)Vidget_type::COLOR_PICKER, position, nullptr, TRANSPARENT, width, height };

	Color_picker *picker = new Color_picker(picker_base, color, &chosen_color);
	add_visual_object(picker);

	return picker;
}

Gradient_bar *
Color_selection_window::create_gradient_bar(const Vector_ll &position, const size_t width, const size_t height, Color_picker *picker, const HSV &hsv)
{
	Full_texture *texture = Application::get_app()->get_rescrs()->create_texture(GRADIENT_BAR_TEXTURE, width, height);
	Visual_object::Config gradient_base = { this, (size_t)Vidget_type::GRADIENT_BAR, position, texture, TRANSPARENT, width, height };

    Gradient_bar *gradient = new Gradient_bar(gradient_base, picker, hsv);
	add_visual_object(gradient);

	return gradient;
}

bool Color_selection_window::on_mouse_click(const bool state, const size_t par_x, const size_t par_y)
{
	return Visual_object::on_mouse_click(state, par_x, par_y);
}

void Color_selection_window::set_current_color(const Color &par_color)
{
	chosen_color = par_color;

	HSV hsv = get_hsv(chosen_color);
	Color picker_color = BLACK;
    if (hsv.h != 0)
    	picker_color = get_rgb({hsv.h, 255, 255});
	picker->set_main_color(picker_color);
	gradient_bar->set_current_position(picker_color);
}

