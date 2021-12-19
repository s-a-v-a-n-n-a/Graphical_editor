#ifndef PLUGIN_TOOL_H
#define PLUGIN_TOOL_H

#include "Plugin.hpp"
#include "plugin_std_2.hpp"

#include "../GUI/Visual_object_base.hpp"
#include "../Tools/Tools.hpp"

class Plugin_tool : public Plugin, public Tool
{
private:

public:
	Plugin_tool(PUPPY::PluginInterface *par_plugin, const PUPPY::AppInterface *interface, void *par_handle, const char *name = nullptr);
	~Plugin_tool();

	void on_mouse_move(const Vector_ll &from, const Vector_ll &to) override;
	void on_mouse_press(Full_texture *texture, const Vector_ll &parameters, const Vector_ll &position) override;
	void on_mouse_release(const Vector_ll &position) override;

	void apply(Full_texture *texture, const Vector_ll &parameters, const Vector_ll &position) override;
};

#endif // PLUGIN_TOOL_H
