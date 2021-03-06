#include "Thickness_window.hpp"
#include "Application.hpp"

Thickness_window::Thickness_window(const Visual_object::Config &par_base)
: Window(par_base)
{
	Change_thickness_non_fixedly *delegate = new Change_thickness_non_fixedly(DEFAULT_TOOL_SIZE);
	slider = create_slider(get_position() + Vector_ll(10, DEFAULT_BUTTON_HEIGHT + 10), get_width() - 20, get_height() - DEFAULT_BUTTON_HEIGHT - 20, delegate);
}

Slider *Thickness_window::create_slider(const Vector_ll &position, const size_t width, const size_t height, Button_delegate *par_delegate)
{
	Slider *slider = new Slider({this, (size_t)Vidget_type::SLIDER, position, NULL, TRANSPARENT, width, height}, par_delegate, 0, 100, true); // умные мысли преследовали её, но она была быстрее

	add_visual_object(slider);
	return slider;
}

void Thickness_window::tick(const double delta)
{
	Tool *current_tool = Application::get_app()->get_tools()->get_active_tool();
	size_t tool_size = current_tool->get_size();

	slider->get_slider()->set_x_relation((double)tool_size / 100.0);
}
