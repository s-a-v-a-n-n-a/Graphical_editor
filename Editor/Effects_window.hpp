#ifndef SPLINE_MANAGER_H
#define SPLINE_MANAGER_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Spline.hpp"

#include "Editor_delegates.hpp"

#include "Window_control_panel.hpp"

#include "Window.hpp"

class Effects_window : public Window
{
public:
	Effects_window(const Visual_object::Config &par_base, Canvas *canvas)
	: Window(par_base)
	{
		Red_component_changer *red_delegate = new Red_component_changer(canvas);
		Green_component_changer *green_delegate = new Green_component_changer(canvas);
		Blue_component_changer *blue_delegate = new Blue_component_changer(canvas);\
		
		Spline *spline_red = create_spline(get_position() + Vector_ll(0, DEFAULT_BUTTON_HEIGHT), get_width(), get_height() - DEFAULT_BUTTON_HEIGHT, RED, red_delegate, {MAX_COLOR_VALUE, MAX_COLOR_VALUE}, {0, 0});
		Spline *spline_green = create_spline(get_position() + Vector_ll(0, DEFAULT_BUTTON_HEIGHT), get_width(), get_height() - DEFAULT_BUTTON_HEIGHT, GREEN, green_delegate, {MAX_COLOR_VALUE, MAX_COLOR_VALUE}, {0, 0});
		Spline *spline_blue = create_spline(get_position() + Vector_ll(0, DEFAULT_BUTTON_HEIGHT), get_width(), get_height() - DEFAULT_BUTTON_HEIGHT, BLUE, blue_delegate, {MAX_COLOR_VALUE, MAX_COLOR_VALUE}, {0, 0});
	}
	~Effects_window() = default;

	Spline *create_spline(const Vector_ll &position, const size_t width, const size_t height, const Color &color, Button_delegate *par_delegate, Vector_ll high_limit, Vector_ll low_limit)
	{
		Visual_object::Config spline_base = { (size_t)Vidget_type::SPLINE, 
												position, 
												nullptr, 
												color,
												width,
												height};

		Spline *spline = new Spline(spline_base, par_delegate, high_limit, low_limit);
		add_visual_object(spline);

		return spline;
	}

	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override
	{
		Visual_object::on_mouse_click(state, par_x, par_y);

		if (point_inside(par_x, par_y))
			return true;
		else
			return false;
	}
};


#endif // SPLINE_MANAGER_H
