#include "Editor_delegates.hpp"
#include "Application.hpp"
#include "Palette.hpp"

Create_canvas::Create_canvas(Canvas_manager_manager *par_manager)
{
	// pencil = par_pencil;
	manager = par_manager;

	// low_limits = par_low_limits;
	// high_limits = par_high_limits;
}

bool Create_canvas::on_mouse_click(const size_t par_x, const size_t par_y)
{
	// Canvas_manager *canvas = new Canvas_manager(pencil, low_limits, WHITE, high_limits.get_x(), high_limits.get_y());
	manager->add_canvas();

	return true;
}

Interactive_create_canvas::Interactive_create_canvas(Canvas_manager_manager *par_manager, Visual_object *par_to_interact)
: Create_canvas(par_manager), Interactive(par_to_interact)
{
	;
}

bool Interactive_create_canvas::on_mouse_move(const Vector_ll from, const Vector_ll to) 
{
	return Interactive::on_mouse_move(from, to);
}


Animating_create_canvas::Animating_create_canvas(Canvas_manager_manager *par_manager, Visual_object *par_to_animate)
: Create_canvas(par_manager), Animating(par_to_animate)
{
	;
}

bool Animating_create_canvas::on_mouse_click(const size_t par_x, const size_t par_y)
{
	Create_canvas::on_mouse_click(par_x, par_y);
	return Animating::on_mouse_click(par_x, par_y);
}

bool Animating_create_canvas::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	return Animating::on_mouse_move(from, to);
}


Canvas_keeper::Canvas_keeper(Visual_object *par_to_keep)
{
	to_keep = par_to_keep;
}

bool Canvas_keeper::on_mouse_click(const size_t par_x, const size_t par_y)
{
	to_keep->set_active_state(true);
	to_keep->set_visible(true);
	to_keep->set_reactive(true);

	return true;
}

// -----------------------------------------------------------------------------------------------------------------

bool Red_component_changer::on_mouse_click(const size_t par_x, const size_t par_y)
{
	// (Canvas*)to_change->set_red(par_x, par_y);
	effect->set_red(par_x, par_y);

	return true;
}

bool Red_component_changer::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	// (Canvas*)to_change->set_red(to.get_x(), to.get_y());
	effect->set_red(to.get_x(), to.get_y());

	return true;
}

// ----------------------------------------------------------------------------------------------------------------

bool Green_component_changer::on_mouse_click(const size_t par_x, const size_t par_y)
{
	// (Canvas*)to_change->set_green(par_x, par_y);
	effect->set_green(par_x, par_y);

	return true;
}

bool Green_component_changer::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	// (Canvas*)to_change->set_green(to.get_x(), to.get_y());
	effect->set_green(to.get_x(), to.get_y());

	return true;
}

// ----------------------------------------------------------------------------------------------------------------

bool Blue_component_changer::on_mouse_click(const size_t par_x, const size_t par_y)
{
	// (Canvas*)to_change->set_blue(par_x, par_y);
	effect->set_blue(par_x, par_y);

	return true;
}

bool Blue_component_changer::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	// (Canvas*)to_change->set_blue(to.get_x(), to.get_y());
	effect->set_blue(to.get_x(), to.get_y());

	return true;
}

// ----------------------------------------------------------------------------------------------------------------

Color_picker_creator::Color_picker_creator(const Vector_ll &par_position) : position(par_position) {}

bool Color_picker_creator::on_mouse_click(const size_t par_x, const size_t par_y)
{
	return true;
}
bool Color_picker_creator::on_mouse_release()
{
	Palette *palette = new Palette({(size_t)Vidget_type::PALETTE, position, nullptr, DARK_GREY, 600, 600}, Toolbar::get_instance()->get_color());

	Application::get_app()->set_main(palette);

	return true;
}

// ---------------------------------------------------------------------------------------------------------------

Plugin_input_creator::Plugin_input_creator(const Vector_ll &par_position)
: position(par_position) {}

bool Plugin_input_creator::on_mouse_click(const size_t par_x, const size_t par_y)
{
	return true;
}

bool Plugin_input_creator::on_mouse_release()
{
	Search_box *input = new Search_box({(size_t)Vidget_type::SEARCH_BOX, position, nullptr, DARK_GREY, 600, 300});

	Application::get_app()->set_main(input);

	return true;
}

// --------------------------------------------------------------------------------------------------------------

Animating_color_picker_creator::Animating_color_picker_creator(const Vector_ll &par_position, Visual_object *par_to_interact)
: Color_picker_creator(par_position), Animating(par_to_interact) {}

bool Animating_color_picker_creator::on_mouse_click(const size_t par_x, const size_t par_y)
{
	Color_picker_creator::on_mouse_click(par_x, par_y);
	return Animating::on_mouse_click(par_x, par_y);
}

bool Animating_color_picker_creator::on_mouse_release()
{
	Animating::reset();
	return Color_picker_creator::on_mouse_release();
}

bool Animating_color_picker_creator::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	return Animating::on_mouse_move(from, to);
}

// ---------------------------------------------------------------------------------------------------------------

Animating_plugin_input_creator::Animating_plugin_input_creator(const Vector_ll &par_position, Visual_object *par_to_interact)
: Plugin_input_creator(par_position), Animating(par_to_interact) {}

bool Animating_plugin_input_creator::on_mouse_click(const size_t par_x, const size_t par_y)
{
	Plugin_input_creator::on_mouse_click(par_x, par_y);
	return Animating::on_mouse_click(par_x, par_y);
}

bool Animating_plugin_input_creator::on_mouse_release()
{
	Animating::reset();
	return Plugin_input_creator::on_mouse_release();
}

bool Animating_plugin_input_creator::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	return Animating::on_mouse_move(from, to);
}


