#include "Color_selection.hpp"

Color_selection_window::Color_selection_window(const Visual_object::Config &par_base, const Color &color)
: Visual_object(par_base), chosen_color(color)
{
	size_t picker_size = (get_width() - 20) * 3 / 4;
	HSV hsv = get_hsv(color);
    Color picker_color = RED;
    if (hsv.h != 0)
    	picker_color = get_rgb({hsv.h, 255, 255});


	picker = create_color_picker(get_position() + Vector_ll(10, 20), picker_size, picker_size, picker_color);// new Color_picker((size_t)Vidget_type::COLOR_PICKER, par_position + Vector_ll(10, (offset + 30)), TRANSPARENT, MAX_COLOR_VALUE, MAX_COLOR_VALUE, par_pencil);
    gradient_bar = create_gradient_bar(get_position() + Vector_ll(10, 0), picker_size, 20, picker, hsv);// 
}

Color_picker *
Color_selection_window::create_color_picker(const Vector_ll &position, const size_t width, const size_t height, const Color &color)
{
	Visual_object::Config picker_base = { (size_t)Vidget_type::COLOR_PICKER, position, nullptr, TRANSPARENT, width, height };

	Color_picker *picker = new Color_picker(picker_base, color, &chosen_color);
	add_visual_object(picker);

	return picker;
}

Gradient_bar *
Color_selection_window::create_gradient_bar(const Vector_ll &position, const size_t width, const size_t height, Color_picker *picker, const HSV &hsv)
{
	Full_texture *texture = Resources::get_instance()->create_texture(GRADIENT_BAR_TEXTURE, width, height);
	Visual_object::Config gradient_base = { (size_t)Vidget_type::GRADIENT_BAR, position, texture, TRANSPARENT, width, height };

    Gradient_bar *gradient = new Gradient_bar(gradient_base, picker, hsv);
	add_visual_object(gradient);

	return gradient;
}
