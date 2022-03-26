#include "Pipette.hpp"
#include "../Editor/Application.hpp"

Pipette::Pipette()
: Tool() 
{ 
	Tool::set_color(WHITE); 
}

void Pipette::apply(Full_texture *texture, const Vector_ll &parameters, const Vector_ll &position)
{
	// size_t width = to_apply->get_width();
	// size_t height = to_apply->get_height();
	size_t width = parameters.get_x();
	size_t height = parameters.get_y();

	// Vector_ll canvas_position = to_apply->get_position();

	size_t position_x = position.get_x();
	size_t position_y = position.get_y();
	
	// Tools::set_color(position_y * width + position_y);
	// Application::get_app()->get_tools()->set_color(to_apply[position_y * width + position_x]);
	
	Color *texture_data = Application::get_app()->get_renderer()->texture2data(texture->get_current_texture(), width, height);
	set_color(texture_data[position_y * width + position_x]);
}
