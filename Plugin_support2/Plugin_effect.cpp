#include "Plugin_effect.hpp"

Plugin_effect::Plugin_effect(const PPluginInterface *par_plugin, const PAppInterface *interface, void *par_handle, Canvas *canvas, const char *name)
: Plugin(par_handle, par_plugin), Effect(canvas, name) 
{
	// PPluginStatus result = plugin->general.init(interface);
	// if (result != PPS_OK)
	// 	printf("Could not initialize plugin effect\n");
	;
	set_appliable(false);
}

Plugin_effect::~Plugin_effect()
{
	plugin->general.deinit();
	// delete plugin;
}

void Plugin_effect::apply()
{
	set_appliable(true);
	plugin->effect.apply();
	set_appliable(false);
}
