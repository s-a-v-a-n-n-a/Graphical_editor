#include "Tools_window.hpp"

#include "../GUI/Text.hpp"

Tools_window::Tools_window(const Visual_object::Config &par_base)
: Window(par_base)
{
	text_size = 10;
	icon_size = get_width()/3;
	icons_in_line = 3;

	size_t default_tools_amount = Toolbar::get_instance()->get_tools_amount();
	std::vector<Tool*> tools = Toolbar::get_instance()->get_tools();

	size_t y_offset = DEFAULT_BUTTON_HEIGHT;
	for (size_t i = 0; i < default_tools_amount; i += icons_in_line)
	{
		for (size_t j = 0; j < icons_in_line; ++j)
		{
			if (i + j < default_tools_amount)
			{
				create_pick_button(get_position() + Vector_ll(icon_size * j, y_offset), icon_size, icon_size, TOOLS_BUTTONS[i + j], ACTIVE_TOOLS_BUTTONS[i + j], tools[i + j]);
				// maybe create plugin name?
			}
		}

		y_offset += icon_size;
	}
	if (default_tools_amount % 3)
		y_offset -= icon_size;	

	Animating_texture *color_texture = Resources::get_instance()->create_texture(COLOR_BUTTON, icon_size, icon_size, ACTIVE_COLOR_BUTTON, NULL);

	Color_button *color_button = new Color_button({(size_t)Vidget_type::BUTTON, get_position() + Vector_ll((default_tools_amount % icons_in_line) * icon_size, y_offset), color_texture, Toolbar::get_instance()->get_color(), icon_size, icon_size}, NULL, "");
	Animating_color_picker_creator *color_creator = new Animating_color_picker_creator({300, 300}, color_button);
	color_button->set_delegate(color_creator);
	add_visual_object(color_button);

	tools_amount = default_tools_amount + 1;
}

Button *Tools_window::create_pick_button(const Vector_ll &position, const size_t width, const size_t height, const char *texture_name, const char *move_texture_name, Tool *tool)
{
	// Full_texture *texture = Resources::get_instance()->create_texture(texture_name, width, height);
	Animating_texture *texture = Resources::get_instance()->create_texture(texture_name, width, height, move_texture_name, NULL);

	Button *pick_button = new Button({(size_t)Vidget_type::BUTTON, position, texture, TRANSPARENT, width, height}, NULL, "");
	Animating_pick_tool *picker = new Animating_pick_tool(tool, pick_button); // &tools,
	pick_button->set_delegate(picker); 

	add_visual_object(pick_button);

	return pick_button;
}

void Tools_window::add_tool(Tool *tool)
{
	Animating_texture *texture = Resources::get_instance()->create_texture(UNKNOWN_TOOL, icon_size, icon_size, UNKNOWN_TOOL_ACTIVE, NULL);

	Vector_ll position = get_position() + Vector_ll((tools_amount % icons_in_line) * icon_size, DEFAULT_BUTTON_HEIGHT + (tools_amount / icons_in_line) * icon_size);

	Button *pick_button = new Button({(size_t)Vidget_type::BUTTON, position, texture, TRANSPARENT, icon_size, icon_size}, NULL, "");
	Animating_pick_tool *picker = new Animating_pick_tool(tool, pick_button); // &tools,
	pick_button->set_delegate(picker); 

	add_visual_object(pick_button);

	tools_amount++;
}

void Tools_window::tick(Screen_information *screen, const double delta_time)
{
	Visual_object::tick(screen, delta_time);

	size_t current_tools_amount = Toolbar::get_instance()->get_tools_amount();
	if (current_tools_amount != (tools_amount - 1))
	{
		for (size_t i = tools_amount - 1; i < current_tools_amount; ++i)
		{
			Tool *add = Toolbar::get_instance()->get_tools()[i];
			add_tool(add);
		}
	}
}


