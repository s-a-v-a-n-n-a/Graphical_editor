#ifndef WINDOW_H
#define WINDOW_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Resource_manager.hpp"

#include "Window_control_panel.hpp"

class Window : public Visual_object
{
private:

public:
	Window(const Visual_object::Config &par_base)
	: Visual_object(par_base)
	{
		Window_control_panel *control = create_control_panel(this, get_position(), get_width(), DEFAULT_BUTTON_HEIGHT);
	}

	Window_control_panel *create_control_panel(Visual_object *parent, const Vector_ll &position, const size_t width, const size_t height)
	{
		Full_texture *texture = Resources::get_instance()->create_texture(WINDOW_HEADER, width, height);
		Visual_object::Config panel_base = { (size_t)Vidget_type::WINDOW_CONTROL_PANEL, 
												position, 
												texture, 
												TRANSPARENT,
												width,
												height};

		Window_control_panel *control = new Window_control_panel(panel_base, parent);
		add_visual_object(control);

		return control;
	}
};

class Closing_window : public Visual_object
{
private:

public:
	Closing_window(const Visual_object::Config &par_base)
	: Visual_object(par_base)
	{
		Closing_window_control_panel *control = create_control_panel(this, get_position(), get_width(), DEFAULT_BUTTON_HEIGHT);
	}

	Closing_window_control_panel *create_control_panel(Visual_object *parent, const Vector_ll &position, const size_t width, const size_t height)
	{
		Full_texture *texture = Resources::get_instance()->create_texture(WINDOW_HEADER, width, height);
		Visual_object::Config panel_base = { (size_t)Vidget_type::WINDOW_CONTROL_PANEL, 
												position, 
												texture, 
												TRANSPARENT,
												width,
												height};

		Closing_window_control_panel *control = new Closing_window_control_panel(panel_base, parent);
		add_visual_object(control);

		return control;
	}
};

#endif // WINDOW_H
