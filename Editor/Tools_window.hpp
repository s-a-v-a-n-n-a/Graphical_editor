#ifndef TOOLS_WINDOW_H
#define TOOLS_WINDOW_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"

#include "../Tools/Toolbar.hpp"

#include "Window.hpp"
#include "Editor_delegates.hpp"
#include "Graphical_delegates.hpp"

class Color_button : public Button 
{
public:
	Color_button(const Visual_object::Config &par_base, Button_delegate *par_click, const char *par_text)
	: Button(par_base, par_click, par_text) {}

	void tick(Screen_information *screen, const double delta_time) override
	{
		set_color(Toolbar::get_instance()->get_color());
		
		Button::tick(screen, delta_time);
	}
};

class Tools_window : public Window
{
private:
	size_t icon_size;
	size_t text_size;
	long long icons_in_line;
	long long tools_amount;

public:
	Tools_window(const Visual_object::Config &par_base);

	Button *create_pick_button(const Vector_ll &position, const size_t width, const size_t height, const char *texture_name, const char *move_texture_name, Tool *tool);

	void add_tool(Tool *tool);

	void tick(Screen_information *screen, const double delta_time) override;
};

#endif // TOOLS_WINDOW_H
