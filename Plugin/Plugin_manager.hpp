#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <stdarg.h>

#include "Plugin_tool.hpp"
#include "Plugin_effect.hpp"
#include "plugin_std.hpp"

#include "../Tools/Toolbar.hpp"

#include "../simple_list/simple_list.hpp"

#include "../Editor/Dialog_window.hpp"

extern const PPluginInterface *(*get_plugin_interface)();

// struct App_interface
// {
// 	namespace Extensions
// 	{
// 		bool  enable(const char *name);
//         void *get_func(const char *name);
// 	}

// 	namespace General
// 	{
// 		int feature_level;

//         void log(const char *fmt, ...);
//         double get_absolute_time();

//         void release_pixels(PRGBA *pixels);

//         PRGBA (*get_color)();
//         float (*get_size)();
// 	}
// };

Blend_mode app_translate_mode(PBlendMode mode);

PRGBA *app_get_pixels();
void app_get_size(size_t *width, size_t *height);
	
void app_log(const char *fmt, ...);
double app_get_absolute_time();

void app_release_pixels(PRGBA *pixels);

PRGBA app_get_current_color();
float app_get_current_size();

void app_circle(PVec2f position, float radius, PRGBA color, const PRenderMode *render_mode);
void app_rectangle(PVec2f p1, PVec2f p2, PRGBA color, const PRenderMode *render_mode);
void app_triangle(PVec2f p1, PVec2f p2, PVec2f p3, PRGBA color, const PRenderMode *render_mode);
void app_line(PVec2f start, PVec2f end, PRGBA color, const PRenderMode *render_mode);

void app_pixels(PVec2f position, const PRGBA *data, size_t width, size_t height, const PRenderMode *render_mode);

// надо сделатб
// struct Settings
// {
void  app_create_surface(const PPluginInterface *self, size_t width, size_t height);
void  app_destroy_surface(const PPluginInterface *self);

void *app_add(const PPluginInterface *self, PSettingType type, const char *name);
void  app_get(const PPluginInterface *self, void *handle, void *answer);

class Plugin_manager
{
private:
	// Visual_object *surface;

	List<Plugin*> plugins; // надо ли? надо
	// List<Plugin_tool*> tools; // надо ли? надо
	// List<Plugin_effect*> effects; // надо ли? надо
	PAppInterface *app_interface;

	static Blend_mode (*translate_mode)(PBlendMode mode);

	// struct Target
	// {
	static PRGBA *(*get_pixels)();
    static void (*get_size)(size_t *width, size_t *height);
	// };

	// struct General
	// {	
	static void (*log)(const char *fmt, ...);
    static double (*get_absolute_time)();

	static void (*release_pixels)(PRGBA *pixels);

	static PRGBA (*get_current_color)();
    static float (*get_current_size)();

	// };

	// struct Render
	// {
	static void (*circle)(PVec2f position, float radius, PRGBA color, const PRenderMode *render_mode);		
	static void (*rectangle)(PVec2f p1, PVec2f p2, PRGBA color, const PRenderMode *render_mode);
	static void (*triangle)(PVec2f p1, PVec2f p2, PVec2f p3, PRGBA color, const PRenderMode *render_mode);
	static void (*line)(PVec2f start, PVec2f end, PRGBA color, const PRenderMode *render_mode);

	static void (*pixels)(PVec2f position, const PRGBA *data, size_t width, size_t height, const PRenderMode *render_mode);
	// };

// надо сделатб
	// struct Settings
	// {
	static void  (*create_surface)(const PPluginInterface *self, size_t width, size_t height);
    static void  (*destroy_surface)(const PPluginInterface *self);

    static void *(*add)(const PPluginInterface *self, PSettingType type, const char *name);
    static void  (*get)(const PPluginInterface *self, void *handle, void *answer);
	// };

public:
	Plugin_manager();
	~Plugin_manager();

	char *create_path(const char *filename);
	void delete_path(char *path);

	PAppInterface *create_app_interface();

	void load_from_dir(const char *path);
	
	void add_plugin(const char *filename, bool is_path = false);

	void add_tool(const PPluginInterface *plugin, const PAppInterface *app_interface, void *par_handle);
	void add_effect(const PPluginInterface *plugin, const PAppInterface *app_interface, void *par_handle);

	Plugin *get_plugin(const PPluginInterface *self);
};

#endif // PLUGIN_MANAGER_H
