#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <stdarg.h>
#include <filesystem>

#include "plugin_std_2.hpp"
#include "Plugin_tool.hpp"
#include "Plugin_effect.hpp"
#include "Interface.hpp"
// #include "Render.hpp"

#include "../Tools/Toolbar.hpp"
#include "../simple_list/simple_list.hpp"
#include "../Editor/Dialog_window.hpp"

#if 0
get_render_target needed
#endif



// PRGBA *app_get_pixels();
// void app_get_size(size_t *width, size_t *height);
	
// void app_log(const char *fmt, ...);
// double app_get_absolute_time();

// void app_release_pixels(PRGBA *pixels);

// PRGBA app_get_current_color();
// float app_get_current_size();

// void app_circle(PVec2f position, float radius, PRGBA color, const PRenderMode *render_mode);
// void app_rectangle(PVec2f p1, PVec2f p2, PRGBA color, const PRenderMode *render_mode);
// void app_triangle(PVec2f p1, PVec2f p2, PVec2f p3, PRGBA color, const PRenderMode *render_mode);
// void app_line(PVec2f start, PVec2f end, PRGBA color, const PRenderMode *render_mode);

// void app_pixels(PVec2f position, const PRGBA *data, size_t width, size_t height, const PRenderMode *render_mode);

// // надо сделатб
// // struct Settings
// // {
// void  app_create_surface(const PPluginInterface *self, size_t width, size_t height);
// void  app_destroy_surface(const PPluginInterface *self);

// void *app_add(const PPluginInterface *self, PSettingType type, const char *name);
// void  app_get(const PPluginInterface *self, void *handle, void *answer);

class Plugin_manager
{
private:
	// Visual_object *surface;

	std::vector<Plugin*> plugins; // надо ли? надо
	// PUPPY::AppInterface *app_interface;
	Interface *app_interface;
	// Render *render;

public:
	Plugin_manager();
	~Plugin_manager();

	char *create_path(const char *filename);
	void delete_path(char *path);

	PUPPY::AppInterface *create_app_interface();

	void load_from_dir(const char *path);
	char *find_plugin(const char *path);
	char *find_folder(const char *filename);	
	
	void add_plugin(const char *filename, bool is_path = false);

	void add_tool(PUPPY::PluginInterface *plugin, const PUPPY::AppInterface *app_interface, void *par_handle, const char *path);
	void add_effect(PUPPY::PluginInterface *plugin, const PUPPY::AppInterface *app_interface, void *par_handle, const char *path);

	Plugin *get_plugin(const PUPPY::PluginInterface *self);

	void tick(const double delta);
};

#endif // PLUGIN_MANAGER_H
