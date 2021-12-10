#ifndef PLUGIN_TOOL_H
#define PLUGIN_TOOL_H

#include "Plugin.hpp"
#include "plugin_std.hpp"

#include "../GUI/Visual_object_base.hpp"
#include "../Tools/Tools.hpp"

class Plugin_tool : public Plugin, public Tool
{
private:

public:
	Plugin_tool(const PPluginInterface *par_plugin, const PAppInterface *interface, void *par_handle);
	~Plugin_tool();

	void on_mouse_move(const Vector_ll &from, const Vector_ll &to) override;
	void on_mouse_press(Color *to_apply, const Vector_ll &parameters, const Vector_ll &position) override;
	void on_mouse_release(const Vector_ll &position) override;

	void apply(Color *to_apply, const Vector_ll &parameters, const Vector_ll &position) override;
};

#endif // PLUGIN_TOOL_H
