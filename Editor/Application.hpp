#ifndef APPLICATION_H
#define APPLICATION_H

#include "../Utilities/Timer.hpp"

#include "../sfml_drawing/screen_functions.hpp"
#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Resource_manager.hpp"

#include "Graphical_editor_main_page.hpp"

// ?????????????
#include "../Plugin_support/Plugin_manager.hpp"
#include "../Tools/Toolbar.hpp"
#include "../GUI/Animations.hpp"
#include "Effects/Canvas_effects_manager.hpp"
// #include "../Plugin_support/plugin_std.hpp"

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

	Resources *resources;

	Animation_manager *animations;
	Plugin_manager *plugins;
	Effect_manager *effects;
	Toolbar *tools;
	
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
	void add_effect(Effect<Canvas> *effect);
	void add_tool(Tool *tool);
	
	Animation_manager *get_animations();
	Plugin_manager *get_plugins();
	Effect_manager *get_effects();
	Toolbar *get_tools();
	Resources *get_rescrs();

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
