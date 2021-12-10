#include "Plugin_tool.hpp"

Plugin_tool::Plugin_tool(const PPluginInterface *par_plugin, const PAppInterface *interface, void *par_handle)
: Tool(), Plugin(par_handle, par_plugin)
{
	PPluginStatus result = plugin->general.init(interface);
	if (result != PPS_OK)
		printf("Could not initialize plugin tool\n");
} 

Plugin_tool::~Plugin_tool()
{
	plugin->general.deinit();
}

void Plugin_tool::on_mouse_move(const Vector_ll &from, const Vector_ll &to)
{
	if (pressed)
	{
		PVec2f mouse_pos = { (float)(to.get_x()), (float)(to.get_y()) };
		plugin->tool.on_press(mouse_pos);
	}
}

void Plugin_tool::on_mouse_press(Color *to_apply, const Vector_ll &parameters, const Vector_ll &position)
{
	Tool::on_mouse_press(to_apply, parameters, position);

	PVec2f mouse_pos = { (float)position.get_x(), (float)position.get_y() };
	plugin->tool.on_press(mouse_pos);
}

void Plugin_tool::on_mouse_release(const Vector_ll &position)
{
	if (pressed)
	{
		PVec2f mouse_pos = { (float)position.get_x(), (float)position.get_y() };
		plugin->tool.on_release(mouse_pos);

		pressed = false;
	}
}

void Plugin_tool::apply(Color *to_apply, const Vector_ll &parameters, const Vector_ll &position)
{
	;
}
