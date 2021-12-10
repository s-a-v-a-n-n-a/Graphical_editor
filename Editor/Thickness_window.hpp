#ifndef THICKNESS_WINDOW_H
#define THICKNESS_WINDOW_H

#include "../GUI/Slider.hpp"

#include "Graphical_delegates.hpp"
#include "Window.hpp"

const size_t INDENT_SIZE = 10;

class Thickness_window : public Window 
{
private:
	Slider *slider;

public:
	Thickness_window(const Visual_object::Config &par_base)
	: Window(par_base)
	{
		Change_thickness_non_fixedly *delegate = new Change_thickness_non_fixedly(DEFAULT_PENCIL_SIZE);
		slider = create_slider(get_position() + Vector_ll(0, DEFAULT_BUTTON_HEIGHT), get_width(), get_height() - DEFAULT_BUTTON_HEIGHT, delegate);
	}

	Slider *create_slider(const Vector_ll &position, const size_t width, const size_t height, Button_delegate *par_delegate)
	{
		Slider *slider = new Slider({(size_t)Vidget_type::SLIDER, position, NULL, TRANSPARENT, width, height}, par_delegate, 0, 100, true); // умные мысли преследовали её, но она была быстрее

		add_visual_object(slider);
		return slider;
	}

	void tick(Screen_information *screen, const double delta_time) override
	{
		Tool *current_tool = Toolbar::get_instance()->get_active_tool();
		size_t tool_size = current_tool->get_size();

		slider->get_slider()->set_x_relation((double)tool_size / 100.0);
	}
};

#endif // THICKNESS_WINDOW_H
