#ifndef APPLICATION_H
#define APPLICATION_H

#include "../Utilities/Timer.hpp"

#include "../sfml_drawing/screen_functions.hpp"
#include "../GUI/Visual_object_base.hpp"

#include "Graphical_editor_main_page.hpp"

// ?????????????
#include "../Plugin/Plugin_manager.hpp"
// #include "../Plugin/plugin_std.hpp"

extern const size_t DEFAULT_SIZE;

class Application;

class Application_destroyer
{
private:
	Application *app;

public:
	~Application_destroyer();

	void initialize(Application *par_application);
};

class Application
{
private:
	static Application *app;
	static Application_destroyer destroyer;

	Plugin_manager *plugins;
	
	Visual_object *current_main;
	Visual_object *default_main;

	Timer timer;

protected:
	Application();
	friend class Application_destroyer;

public:
	Screen_information *graphics_wrapper;

	~Application();
	static Application *get_app();

	void add_plugin(const char *plugin_name);
	Plugin_manager *get_plugins();

	size_t get_time();
	
	Visual_object *get_default();
	Visual_object *get_main();

	void set_default();
	void set_main(Visual_object *object);

	void add_visual_object(Visual_object *object);

	void draw();
	void tick();

	void launch();
};

#endif // APPLICATION_H
