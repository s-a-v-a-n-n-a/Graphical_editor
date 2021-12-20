#include "Plugin_manager.hpp"

#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>

#include "../Editor/Application.hpp"
#include "../sfml_drawing/screen_functions.hpp"
#include "../math_structures/math_functions.hpp"



// PRGBA *app_get_pixels()
// {
// 	if (!((Graphical_editor_main_page*)Application::get_app()->get_default())->get_active_canvas())
// 		return nullptr;

// 	size_t width = ((Graphical_editor_main_page*)Application::get_app()->get_default())->get_active_canvas()->get_width();
// 	size_t height = ((Graphical_editor_main_page*)Application::get_app()->get_default())->get_active_canvas()->get_height();

// 	Color *data = ((Graphical_editor_main_page*)Application::get_app()->get_default())->get_active_canvas()->get_drawing();

// 	PRGBA *pixels = new	PRGBA[width * height];
// 	for (size_t i = 0; i < width * height; ++i)
// 		pixels[i] = *((PRGBA*)&(data[i]));

// 	return pixels;
// }

// void app_get_size(size_t *width, size_t *height)
// {
// 	Vector_ll params = Application::get_app()->get_tools()->get_active_tool()->get_params();

// 	(*width) = (size_t)params.get_x(); 
// 	(*height) = (size_t)params.get_y(); 
// }

// double app_get_absolute_time()
// {
// 	return Application::get_app()->get_time();
// }

// void app_log(const char *fmt, ...)
// {
// 	va_list arg;
// 	va_start(arg, fmt);

// 	printf(fmt, arg);
// 	printf("\n");

// 	va_end(arg);
// }

// void app_release_pixels(PRGBA *pixels)
// {
// 	delete [] pixels;
// }

// PRGBA app_get_current_color()
// {
// 	Color color = Application::get_app()->get_tools()->get_color();

// 	return *((PRGBA*)&(color));
// }

// float app_get_current_size()
// {
// 	return (float)Application::get_app()->get_tools()->get_active_tool()->get_size();
// }

// void app_circle(PVec2f position, float radius, PRGBA color, const PRenderMode *render_mode)
// {
// 	Vector_ll pos = Vector_ll((long long)position.x, (long long)position.y);
// 	Color app_color = { color.r, color.g, color.b, color.a };

// 	size_t pencil_size = Application::get_app()->get_tools()->get_active_tool()->get_size() / 2;
// 	// Color pencil_color = Application::get_app()->get_tools()->get_color();

// 	Blend_mode mode = app_translate_mode(render_mode->blend);

// 	size_t begin_x = (pos.get_x() - radius) > 0 ? (pos.get_x() - radius) : 0;
// 	size_t begin_y = (pos.get_y() - radius) > 0 ? (pos.get_y() - radius) : 0;

// 	size_t width = Application::get_app()->get_tools()->get_active_tool()->get_params().get_x();
// 	size_t height = Application::get_app()->get_tools()->get_active_tool()->get_params().get_y();

// 	size_t end_x = (pos.get_x() + radius) < width ? (pos.get_x() + radius) : width;
// 	size_t end_y = (pos.get_y() + radius) < height ? (pos.get_y() + radius) : height;

// 	Vector_ll center = pos;
// 	Color *to_apply = Application::get_app()->get_tools()->get_active_tool()->get_pixels();

// 	for (size_t i = begin_y; i < end_y; ++i)
// 		for (size_t j = begin_x; j < end_x; ++j)
// 		{
// 			if ((i - center.get_y()) * (i - center.get_y()) + (j - center.get_x()) * (j - center.get_x()) <= (long long)(radius * radius))
// 			{
// 				size_t index = i * width + j;

// 				to_apply[index] = app_color;
// 			}
// 		}
// 	// Application::get_app()->graphics_wrapper->draw_circle(pos, (double)radius, app_color, app_color, mode);
// }

// void app_rectangle(PVec2f p1, PVec2f p2, PRGBA color, const PRenderMode *render_mode)
// {
// 	long long x_pos = p1.x < p2.x ? p1.x : p2.x;
// 	long long y_pos = p1.y < p2.y ? p1.y : p2.y;

// 	Vector_ll position = Vector_ll(x_pos, y_pos);
// 	Color local_color = { color.r, color.g, color.b, color.a };

// 	size_t pencil_size = Application::get_app()->get_tools()->get_active_tool()->get_size() / 2;
// 	Color pencil_color = Application::get_app()->get_tools()->get_color();

// 	size_t width = (size_t)((fabs)(p2.x - p1.x));
// 	size_t height = (size_t)((fabs)(p2.y - p1.y));

// 	size_t begin_x = x_pos > pencil_size ? x_pos - pencil_size : x_pos;
// 	size_t begin_y = y_pos > pencil_size ? y_pos - pencil_size : y_pos;

// 	size_t end_x = x_pos + pencil_size < width ? x_pos + pencil_size : x_pos;
// 	size_t end_y = y_pos + pencil_size < height ? y_pos + pencil_size : y_pos;

// 	Color *to_apply = Application::get_app()->get_tools()->get_active_tool()->get_pixels();

// 	for (size_t i = begin_y; i < end_y; ++i)
// 		for (size_t j = begin_x; j < end_x; ++j)
// 		{
// 			size_t index = i * width + j;

// 			to_apply[index] = local_color;
// 		}

// 	Blend_mode mode = app_translate_mode(render_mode->blend);
// 	// Application::get_app()->graphics_wrapper->draw_rectangle(position, width, height, local_color, local_color, mode);
// }

// void app_triangle(PVec2f p1, PVec2f p2, PVec2f p3, PRGBA color, const PRenderMode *render_mode)
// {
// 	Vector_ll point1 = Vector_ll((long long)p1.x, (long long)p1.y);
// 	Vector_ll point2 = Vector_ll((long long)p2.x, (long long)p2.y);
// 	Vector_ll point3 = Vector_ll((long long)p3.x, (long long)p3.y);

// 	Color local_color = { color.r, color.g, color.b, color.a };

// 	size_t begin_x = p1.x < p2.x ? (p1.x < p3.x ? p1.x : p3.x) : (p2.x < p3.x ? p2.x : p3.x);
// 	size_t begin_y = p1.y < p2.y ? (p1.y < p3.y ? p1.y : p3.y) : (p2.y < p3.y ? p2.y : p3.y);

// 	size_t end_x = p1.x > p2.x ? (p1.x > p3.x ? p1.x : p3.x) : (p2.x > p3.x ? p2.x : p3.x);
// 	size_t end_y = p1.y > p2.y ? (p1.y > p3.y ? p1.y : p3.y) : (p2.y > p3.y ? p2.y : p3.y);

// 	size_t width = Application::get_app()->get_tools()->get_active_tool()->get_params().get_x();
// 	size_t height = Application::get_app()->get_tools()->get_active_tool()->get_params().get_y();
// 	Color *to_apply = Application::get_app()->get_tools()->get_active_tool()->get_pixels();

// 	for (size_t i = begin_y; i < end_y; ++i)
// 	{
// 		for (size_t j = begin_x; j < end_x; ++j)
// 		{
// 			if (i >= 0 && i < height && j >= 0 && j < width && is_inside_triangle({(long long)j, (long long)i}, point1, point2, point3))
// 			{
// 				size_t index = i * width + j;

// 				to_apply[index] = local_color;
// 			}
// 		}
// 	}

// 	Blend_mode mode = app_translate_mode(render_mode->blend);
// 	// Application::get_app()->graphics_wrapper->draw_triangle(point1, point2, point3, local_color, local_color, mode);
// }

// void app_line(PVec2f start, PVec2f end, PRGBA color, const PRenderMode *render_mode)
// {
// 	Vector_ll point1 = Vector_ll((long long)start.x, (long long)start.y);
// 	Vector_ll point2 = Vector_ll((long long)end.x, (long long)end.y);

// 	Color local_color = { color.r, color.g, color.b, color.a };

// 	Blend_mode mode = app_translate_mode(render_mode->blend);
// 	Application::get_app()->graphics_wrapper->draw_line(point1, point2, local_color, mode);
// }

// void app_pixels(PVec2f position, const PRGBA *data, size_t width, size_t height, const PRenderMode *render_mode)
// {
// 	Vector_ll pos = Vector_ll(position.x, position.y);

// 	Blend_mode mode = app_translate_mode(render_mode->blend);
// 	((Graphical_editor_main_page*)Application::get_app()->get_default())->get_active_canvas()->apply((Color*)data, mode);
// }

// void app_create_surface(const PPluginInterface *self, size_t width, size_t height)
// {
// 	// запомнить, какому плагину принадлежит это диалоговое окно
// 	Plugin *plugin = Application::get_app()->get_plugins()->get_plugin(self);
// 	plugin->set_surface(create_dialog_window(3 * width, 3 * height, self->general.get_info()->name));
// }

// void app_destroy_surface(const PPluginInterface *self)
// {
// 	Plugin *plugin = Application::get_app()->get_plugins()->get_plugin(self);
// 	destroy_dialog_window((Dialog*)plugin->get_surface());

// 	plugin->set_surface(nullptr);
// }

// void *app_add(const PPluginInterface *self, PSettingType type, const char *name)
// {
// 	Plugin *plugin = Application::get_app()->get_plugins()->get_plugin(self);
// 	// destroy_dialog_window((Dialog*)plugin->get_surface());

// 	if (!strcmp(type, PST_SLIDER_1D))
// 	{
// 		return ((Dialog*)plugin->get_surface())->create_slider(name);
// 	}

// 	if (!strcmp(type, PST_COLOR_PICKER))
// 	{
// 		return ((Dialog*)plugin->get_surface())->create_color_picker(name);
// 	}

// 	if (!strcmp(type, PST_TEXT_LINE))
// 	{
// 		return ((Dialog*)plugin->get_surface())->create_input_string(name);
// 	}

// 	return nullptr;
// }

// void app_get(const PPluginInterface *self, void *handle, void *answer)
// {
// 	Plugin *plugin = Application::get_app()->get_plugins()->get_plugin(self);

// 	if (((Visual_object*)handle)->get_type() == (size_t)Vidget_type::SLIDER)
// 	{
// 		*((float*)answer) = ((Dialog*)plugin->get_surface())->get_fraction((Slider*)handle);
// 		return;
// 	}

// 	if (((Visual_object*)handle)->get_type() == (size_t)Vidget_type::COLOR_SELECTION)
// 	{
// 		Color color = ((Dialog*)(plugin->get_surface()))->get_color((Color_selection_window*)handle);
// 		*((PRGBA*)answer) = *((PRGBA*)&(color));
// 		return;
// 	}

// 	if (((Visual_object*)handle)->get_type() == (size_t)Vidget_type::INPUT_STRING)
// 	{
// 		((PTextFieldSetting*)answer)->text = ((Dialog*)plugin->get_surface())->get_text((Input_string*)handle);
// 		return;
// 	}
// }

// // Plugin_manager::log = nullptr;
// // void (*Plugin_manager::log)(const char *fmt, ...) = nullptr;

// const PPluginInterface *(*get_plugin_interface)() = nullptr;

// Blend_mode (*Plugin_manager::translate_mode)(PBlendMode mode) = nullptr;

// PRGBA *(*Plugin_manager::get_pixels)() = nullptr;
// void (*Plugin_manager::get_size)(size_t *width, size_t *height) = nullptr;

// void (*Plugin_manager::log)(const char *fmt, ...) = nullptr;

// double (*Plugin_manager::get_absolute_time)() = nullptr;

// void (*Plugin_manager::release_pixels)(PRGBA *pixels) = nullptr;

// PRGBA (*Plugin_manager::get_current_color)() = nullptr;

// float (*Plugin_manager::get_current_size)() = nullptr;

// void (*Plugin_manager::circle)(PVec2f position, float radius, PRGBA color, const PRenderMode *render_mode) = nullptr;		

// void (*Plugin_manager::rectangle)(PVec2f p1, PVec2f p2, PRGBA color, const PRenderMode *render_mode) = nullptr;

// void (*Plugin_manager::triangle)(PVec2f p1, PVec2f p2, PVec2f p3, PRGBA color, const PRenderMode *render_mode) = nullptr;

// void (*Plugin_manager::line)(PVec2f start, PVec2f end, PRGBA color, const PRenderMode *render_mode) = nullptr;

// void (*Plugin_manager::pixels)(PVec2f position, const PRGBA *data, size_t width, size_t height, const PRenderMode *render_mode) = nullptr;

// void  (*Plugin_manager::create_surface)(const PPluginInterface *self, size_t width, size_t height) = nullptr;

// void  (*Plugin_manager::destroy_surface)(const PPluginInterface *self) = nullptr;

// void *(*Plugin_manager::add)(const PPluginInterface *self, PSettingType type, const char *name) = nullptr;

// void  (*Plugin_manager::get)(const PPluginInterface *self, void *handle, void *answer) = nullptr;

PUPPY::PluginInterface *(*get_plugin_interface)();

Plugin_manager::Plugin_manager()
: plugins()
{
	// translate_mode = &app_translate_mode;
	// get_pixels = &app_get_pixels;
	// get_size = &app_get_size;
	// log = &app_log;
	// get_absolute_time = &app_get_absolute_time;
	// release_pixels = &app_release_pixels;
	// get_current_color = &app_get_current_color;
	// get_current_size = &app_get_current_size;
	// circle = &app_circle;
	// rectangle = &app_rectangle;
	// triangle = &app_triangle;
	// line = &app_line;
	// pixels = &app_pixels;

	// gAppInterface->general.feature_level & PFL_SETTINGS_SUPPORT	
	// create_surface = &app_create_surface;
	// destroy_surface = &app_destroy_surface;
	// add = &app_add;
	// get = &app_get;

	// render = new Render();
	app_interface = new Interface();

	// app_interface = create_app_interface();

	// load_from_dir("Plugins_self/");
}

Plugin_manager::~Plugin_manager()
{
	size_t plugins_amount = plugins.size();

	for (long long i = plugins_amount - 1; i >= 0; --i)
	{
		plugins.pop_back();
	}

	delete app_interface;
}

char *Plugin_manager::create_path(const char *filename)
{
	char *path = new char[strlen(filename) + 6];
	path[0] = '.'; path[1] = '/';
	memcpy(path + 2, filename, strlen(filename));

	size_t index = 2 + strlen(filename);
	path[index] = '.'; path[index + 1] = 's'; path[index + 2] = 'o'; path[index + 3] = '\0';

	printf("%s\n", path);

	return path;
}

void Plugin_manager::delete_path(char *path)
{
	delete [] path;
}

PUPPY::AppInterface *Plugin_manager::create_app_interface()
{
	// PUPPY::AppInterface *interface = new PUPPY::AppInterface();

	// interface->extensions.enable = nullptr;
	// interface->extensions.get_func = nullptr;

	// interface->general.feature_level = PFL_SETTINGS_SUPPORT;

	// interface->general.log = log;
	// interface->general.get_absolute_time = get_absolute_time;
	// interface->general.release_pixels = release_pixels;
	// interface->general.get_color = get_current_color;
	// interface->general.get_size = get_current_size;

	// interface->target.get_pixels = get_pixels;
	// interface->target.get_size = get_size;

	// interface->render.circle = circle;
	// interface->render.line = line;
	// interface->render.triangle = triangle;
	// interface->render.rectangle = rectangle;
	// interface->render.pixels = pixels;

	// interface->settings.create_surface = create_surface;
	// interface->settings.destroy_surface = destroy_surface;
	// interface->settings.add = add;
	// interface->settings.get = get;

	// interface->shader.apply = nullptr;
	// interface->shader.compile = nullptr;
	// interface->shader.release = nullptr;
	// interface->shader.set_uniform_int = nullptr;
	// interface->shader.set_uniform_int_arr = nullptr;
	// interface->shader.set_uniform_float = nullptr;
	// interface->shader.set_uniform_float_arr = nullptr;

	return app_interface;
}

void Plugin_manager::load_from_dir(const char *path)
{
	DIR *directory = opendir(path);

	struct dirent *to_read = nullptr;

    char extension[] = ".so";
    size_t extension_length = strlen(extension);

    size_t path_length = strlen(path);

    while ((to_read = readdir(directory)) != NULL) 
    {
        size_t dir_name_length = strlen(to_read->d_name);
 
        printf("%s\n", to_read->d_name);
        
        if (strcmp(extension, to_read->d_name + dir_name_length - extension_length) != 0) 
        	continue;
        // printf("%s\n", to_read->d_name);

        char *libname = new char[path_length + dir_name_length + 1];
        sprintf(libname, "%s%s", path, to_read->d_name);
        libname[path_length + dir_name_length] = '\0';
        // printf("%s\n", libname);

        add_plugin(libname, true);

        delete [] libname;
    }

    (void)closedir(directory);
}

char *Plugin_manager::find_plugin(const char *path)
{
	DIR *directory = opendir(path);

	struct dirent *to_read = nullptr;

    char extension[] = ".so";
    size_t extension_length = strlen(extension);

    size_t path_length = strlen(path);

    while ((to_read = readdir(directory)) != NULL) 
    {
        size_t dir_name_length = strlen(to_read->d_name);
 
        if (strcmp(extension, to_read->d_name + dir_name_length - extension_length) != 0) 
        	continue;

        char *libname = new char[path_length + dir_name_length + 1];
        sprintf(libname, "%s%s", path, to_read->d_name);
        libname[path_length + dir_name_length] = '\0';
        
        
    	(void)closedir(directory);
        return libname;
    }

    return nullptr;
}

char *Plugin_manager::find_folder(const char *filename)
{
	size_t path_len = strlen(filename);

	size_t index = path_len - 1;
	while(index)
	{
		if (filename[index] == '.') // '/'
		{
			index--;
			break;
		}

		index--;
	}

	char *folder_path = new char[index + 1];
	strncpy(folder_path, filename, index + 1);
	folder_path[index + 1] = '\0';

	return folder_path;
}

void Plugin_manager::add_plugin(const char *filename, bool is_path)
{
	PUPPY::AppInterface *app_interface = create_app_interface();
	char *folder_path = nullptr;
	
	void *handle = nullptr;
	if (!is_path)
	{
		char *path = create_path(filename);
		handle = dlopen(path, RTLD_LAZY);
		if (!handle)
		{
			fprintf(stderr, "%s\n", dlerror());			
			return;
		}
		else
			printf("[Application message]: found plugin (congratulations!)\n");
		delete_path(path);

		folder_path = find_folder(filename);
	
		printf("folder_path %s\n", folder_path);
	}
	else
	{
		char *plugin_file = find_folder(filename);
		handle = dlopen(filename, RTLD_LAZY);
		if (!handle)
		{
			fprintf(stderr, "%s\n", dlerror());			
			return;
		}
		else
			printf("[Application message]: found plugin (congratulations!)\n");
		
		// delete [] plugin_file;

		folder_path = new char[strlen(plugin_file)];
		sprintf(folder_path, "%s", plugin_file);

		printf("folder_path %s\n", folder_path);
	}
	
	get_plugin_interface = (PUPPY::PluginInterface *(*)())dlsym(handle, PUPPY::GET_INTERFACE_FUNC);
	PUPPY::PluginInterface *plugin = get_plugin_interface();

	PUPPY::PluginType type = plugin->get_info()->type;
	if (type == PUPPY::TOOL)
	{
		add_tool(plugin, app_interface, handle, folder_path);
	}
	else if (type == PUPPY::EFFECT)
	{
		add_effect(plugin, app_interface, handle, folder_path);
	}
	else
	{
		// Plugin *extension = new Plugin(handle, plugin);

		// PUPPY::Status result = plugin->init(app_interface, folder_path); // , path
		// plugins.push_back(extension);
		;
	}

	delete [] folder_path;
}

void Plugin_manager::add_tool(PUPPY::PluginInterface *plugin, const PUPPY::AppInterface *app_interface, void *par_handle, const char *path)
{
	Plugin_tool *tool = nullptr;
	const char *name = plugin->get_info()->name;
	if (name)
		tool = new Plugin_tool(plugin, app_interface, par_handle, name);
	else
		tool = new Plugin_tool(plugin, app_interface, par_handle);

	plugins.push_back(tool);

	std::filesystem::path tool_path = path;
	PUPPY::Status result = plugin->init(app_interface, path); // , path

	if (result != PUPPY::OK)
		printf("Could not initialize plugin tool\n");

	Application::get_app()->get_tools()->add_tool(tool);
}

void Plugin_manager::add_effect(PUPPY::PluginInterface *plugin, const PUPPY::AppInterface *app_interface, void *par_handle, const char *path)
{
	Plugin_effect *effect = nullptr;
	const char *name = plugin->get_info()->name;
	if (name)
		effect = new Plugin_effect(plugin, app_interface, par_handle, ((Graphical_editor_main_page*)(Application::get_app()->get_default()))->get_active_canvas(), name);
	else
		effect = new Plugin_effect(plugin, app_interface, par_handle, ((Graphical_editor_main_page*)(Application::get_app()->get_default()))->get_active_canvas());

	plugins.push_back(effect);
	
	PUPPY::Status result = plugin->init(app_interface, path); // , path
	if (result != PUPPY::OK)
		printf("Could not initialize plugin effect\n");

	Application::get_app()->get_effects()->add_effect(effect);
}

Plugin *Plugin_manager::get_plugin(const PUPPY::PluginInterface *self)
{
	size_t plugins_amount = plugins.size();

	for (size_t i = 0; i < plugins_amount; ++i)
	{
		if (plugins[i]->get_plugin() == self)
		{
			return plugins[i];
		}
	}

	return nullptr; 
}

void Plugin_manager::tick(const double delta)
{
	size_t plugins_amount = plugins.size();

	for (size_t i = 0; i < plugins_amount; ++i)
	{
		plugins[i]->tick(delta);
	}
}
