#include "Plugin_tool.hpp"

Plugin_tool::Plugin_tool(PUPPY::PluginInterface *par_plugin, const PUPPY::AppInterface *interface, void *par_handle, const char *name)
: Tool(name), Plugin(par_handle, par_plugin)
{
	// PPluginStatus result = plugin->general.init(interface);
	// printf("[Application message]: initialization ended\n");	
	// if (result != PPS_OK)
	// 	printf("Could not initialize plugin tool\n");
	;
} 

Plugin_tool::~Plugin_tool()
{
	plugin->deinit();
}

void Plugin_tool::on_mouse_move(const Vector_ll &from, const Vector_ll &to)
{
	if (pressed)
	{
		// Tool::on_mouse_move(from, to);
		// printf("my %lld %lld\n", to.get_x(), to.get_y());

		PUPPY::Vec2f mouse_from = { (float)(from.get_x()), (float)(from.get_y()) };
		PUPPY::Vec2f mouse_to = { (float)(to.get_x()), (float)(to.get_y()) };
		
		// printf("moving %f %f\n", mouse_to.x, mouse_to.y);
		plugin->tool_on_move(mouse_from, mouse_to);
	}
}

void Plugin_tool::on_mouse_press(Full_texture *texture, const Vector_ll &parameters, const Vector_ll &position)
{
	Tool::on_mouse_press(texture, parameters, position);

	PUPPY::Vec2f mouse_pos = { (float)position.get_x(), (float)position.get_y() };
	plugin->tool_on_press(mouse_pos);
}

void Plugin_tool::on_mouse_release(const Vector_ll &position)
{
	if (pressed)
	{
		PUPPY::Vec2f mouse_pos = { (float)position.get_x(), (float)position.get_y() };
		plugin->tool_on_release(mouse_pos);

		pressed = false;
	}
}

void Plugin_tool::apply(Full_texture *texture, const Vector_ll &parameters, const Vector_ll &position)
{
	;
}
