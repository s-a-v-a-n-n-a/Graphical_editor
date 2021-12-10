#ifndef GRAPHICAL_EDITOR_MAIN_PAGE
#define GRAPHICAL_EDITOR_MAIN_PAGE

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button.hpp"
#include "../GUI/Button_manager.hpp"

#include "../GUI/Resource_manager.hpp"
// #include "../GUI/Resource_manager.hpp"

#include "Vidget_types.hpp"

#include "Canvas_manager_manager.hpp"
#include "Color_selection.hpp"
#include "Brush_size_selection.hpp"
#include "Effects_window.hpp"
#include "Thickness_window.hpp"
#include "Tools_window.hpp"
#include "../GUI/Input_string.hpp"

#include "Test.hpp"

// #define WITH_SPLINE

class Editor_control_panel;
class Palette;
class Canvas_manager_manager;

class Graphical_editor_main_page : public Visual_object
{
private:
	Canvas_manager_manager *canvases;

public:
	Graphical_editor_main_page(const Visual_object::Config &par_base);
	// Graphical_editor_main_page(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height);
	// Graphical_editor_main_page(const size_t par_type, const Vector_ll &par_position, Texture *texture, const size_t par_width = 0, const size_t par_height = 0);
	~Graphical_editor_main_page();

	// Color get_pencil_color() { return pencil.get_color(); }
	
	void set_pencil_color(const Color &par_color) { Toolbar::get_instance()->set_color(par_color); }

	// void draw(Screen_information *screen) override;
	// bool on_mouse(const double par_x, const double par_y) override;
	bool on_key_pressed(const bool pressed_state, const unsigned key_state) override;

	Thickness_window *create_thickness_slider(const Vector_ll &position, const size_t width, const size_t height);
	Effects_window *create_effects_window(const Vector_ll &position, const size_t width, const size_t height, Canvas *active_canvas);

	Tools_window *create_tools_window(const Vector_ll &position, const size_t width, const size_t height);
	Button_manager *create_button_panel(const Vector_ll &position, const size_t width, const size_t height);
	Canvas_manager_manager *create_canvas_manager(const Vector_ll &position, const size_t width, const size_t height);
	Button *create_restore_button(Button_manager *panel, Visual_object *to_restore, const char *text, const size_t width, const size_t height);
	Button *create_canvas_creator(Button_manager *panel, Canvas_manager_manager *canvas_manager, const char *text, const size_t width, const size_t height);
	Color_selection_window *create_color_vidget(const Vector_ll &position, const size_t width, const size_t height);
	Brush_size_selection_window *create_size_vidget(const Vector_ll &position, const size_t width, const size_t height);
	Button *create_plugin_info_button(Button_manager *panel, const char *text, const size_t width, const size_t height);

	Canvas *get_active_canvas();
	// test
	Test_button *create_test_button(const Vector_ll &position, const char *text, const size_t width, const size_t height);
};


#endif // GRAPHICAL_EDITOR_MAIN_PAGE
