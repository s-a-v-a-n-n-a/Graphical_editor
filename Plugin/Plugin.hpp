#ifndef PLUGIN_SUPPORT_HPP
#define PLUGIN_SUPPORT_HPP

#include <dlfcn.h>
#include "plugin_std.hpp"

#include "../GUI/Visual_object_base.hpp"

class Plugin
{
protected:
	void *handle;
	const PPluginInterface *plugin;
	Visual_object *surface;

public:
	Plugin(void *par_handle, const PPluginInterface *par_plugin)
	: handle(par_handle), plugin(par_plugin), surface(nullptr)
	{
		// Не забудь вызвать init
	}

	~Plugin()
	{
		// Не забудь вызвать deinit
		dlclose(handle);
	}

	const PPluginInterface *get_plugin() { return plugin; }
	Visual_object *get_surface() { return surface; }
	void set_surface(Visual_object *par_surface) { surface = par_surface; }
};

#endif // PLUGIN_SUPPORT_HPP
