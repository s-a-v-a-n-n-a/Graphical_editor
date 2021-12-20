#include "Tools_window.hpp"

#include "Application.hpp"
#include "../GUI/Text.hpp"

void Color_button::tick(const double delta)
{
	set_color(Application::get_app()->get_tools()->get_color());
	
	Button::tick(delta);
}

Tools_window::Tools_window(const Visual_object::Config &par_base)
: Window(par_base)
{
	text_size = 50;
	icon_size = get_width()/2;
	icons_in_line = 2;

	size_t default_tools_amount = Application::get_app()->get_tools()->get_tools_amount();
	std::vector<Tool*> tools = Application::get_app()->get_tools()->get_tools();

	size_t y_offset = DEFAULT_BUTTON_HEIGHT;
	for (size_t i = 0; i < default_tools_amount; i += icons_in_line)
	{
		for (size_t j = 0; j < icons_in_line; ++j)
		{
			if (i + j < default_tools_amount)
			{
				create_pick_button(get_position() + Vector_ll(icon_size * j, y_offset), icon_size, icon_size, TOOLS_BUTTONS[i + j], ACTIVE_TOOLS_BUTTONS[i + j], tools[i + j]);
				// maybe create plugin name?
				// if (tools[i]->get_name())
				// {

				// }
			}
		}

		y_offset += icon_size + text_size;
	}
	if (default_tools_amount % icons_in_line)
		y_offset -= icon_size + text_size;	

	Animating_texture *color_texture = Application::get_app()->get_rescrs()->create_texture(COLOR_BUTTON, icon_size, icon_size, ACTIVE_COLOR_BUTTON, NULL);

	Color_button *color_button = new Color_button({this, (size_t)Vidget_type::BUTTON, get_position() + Vector_ll((default_tools_amount % icons_in_line) * icon_size, y_offset), color_texture, Application::get_app()->get_tools()->get_color(), icon_size, icon_size}, NULL, "");
	Animating_color_picker_creator *color_creator = new Animating_color_picker_creator({300, 300}, color_button);
	color_button->set_delegate(color_creator);
	add_visual_object(color_button);

	tools_amount = default_tools_amount + 1;
}

Button *Tools_window::create_pick_button(const Vector_ll &position, const size_t width, const size_t height, const char *texture_name, const char *move_texture_name, Tool *tool)
{
	// Full_texture *texture = Application::get_app()->get_rescrs()->create_texture(texture_name, width, height);
	Animating_texture *texture = Application::get_app()->get_rescrs()->create_texture(texture_name, width, height, move_texture_name, NULL);

	Button *pick_button = new Button({this, (size_t)Vidget_type::BUTTON, position, texture, TRANSPARENT, width, height}, NULL, "");
	Animating_pick_tool *picker = new Animating_pick_tool(tool, pick_button); // &tools,
	pick_button->set_delegate(picker); 

	add_visual_object(pick_button);

	if (tool->get_name())
	{
		Button *text_button = new Button({this, (size_t)Vidget_type::BUTTON, position + Vector_ll(0, height), nullptr, TRANSPARENT, width, text_size}, nullptr, tool->get_name());
		add_visual_object(text_button);
	}

	return pick_button;
}

void Tools_window::add_tool(Tool *tool)
{
	Animating_texture *texture = Application::get_app()->get_rescrs()->create_texture(UNKNOWN_TOOL, icon_size, icon_size, UNKNOWN_TOOL_ACTIVE, NULL);

	Vector_ll position = get_position() + Vector_ll((tools_amount % icons_in_line) * icon_size, DEFAULT_BUTTON_HEIGHT + (tools_amount / icons_in_line) * (icon_size + text_size));

	Button *pick_button = new Button({this, (size_t)Vidget_type::BUTTON, position, texture, TRANSPARENT, icon_size, icon_size}, NULL, "");
	Animating_pick_tool *picker = new Animating_pick_tool(tool, pick_button); // &tools,
	pick_button->set_delegate(picker); 

	add_visual_object(pick_button);

	if (tool->get_name())
	{
		Button *text_button = new Button({this, (size_t)Vidget_type::BUTTON, position + Vector_ll(0, icon_size), nullptr, TRANSPARENT, icon_size, text_size}, nullptr, tool->get_name());
		add_visual_object(text_button);
	}

	tools_amount++;
}

void Tools_window::tick(const double delta)
{
	Visual_object::tick(delta);

	size_t current_tools_amount = Application::get_app()->get_tools()->get_tools_amount();
	if (current_tools_amount != (tools_amount - 1))
	{
		for (size_t i = tools_amount - 1; i < current_tools_amount; ++i)
		{
			Tool *add = Application::get_app()->get_tools()->get_tools()[i];
			add_tool(add);
		}
	}
}


