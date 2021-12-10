#ifndef GRAPHICAL_DELEGATES
#define GRAPHICAL_DELEGATES

#include "../GUI/Button_delegate.hpp"
#include "../sfml_drawing/Animating_texture.hpp"
#include "../GUI/Animations.hpp"
#include "../Tools/Toolbar.hpp"
// #include "Canvas_manager.hpp"

// create cpp version

class Canvas_manager;

class Interactive
{
private:
	Visual_object *to_interact;

public:
	Interactive(Visual_object *par_to_interact);

	bool on_mouse_move(const Vector_ll from, const Vector_ll to);

	void set_interactive(Visual_object *par_to_interact);
};

// --------------------------------------------------------------------------------------------------------------------------

class Animating : virtual public Button_delegate
{
private:
	Visual_object *to_animate;

	Animation *move_in;
	long long move_in_index;

	Animation *move_out;
	long long move_out_index;

public:
	Animating(Visual_object *par_to_animate);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;

	void reset();

	void set_animating(Visual_object *par_to_animate);
};

class Restore_delegate : virtual public Button_delegate
{
private:
	Visual_object *to_restore;

public:
	Restore_delegate(Visual_object *par_to_restore);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
};

// --------------------------------------------------------------------------------------------------------------------------

class Animating_restore_delegate : public Restore_delegate, public Animating
{
public:
	Animating_restore_delegate(Visual_object *par_to_restore, Visual_object *par_to_interact);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

class Restore_interactive_delegate : public Restore_delegate, public Interactive
{
public:
	Restore_interactive_delegate(Visual_object *par_to_restore, Visual_object *par_to_interact);

	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

// --------------------------------------------------------------------------------------------------------------------------

// class Magnetic : public Button_delegate
// {
// protected:
// 	Visual_object *to_control;

// 	Vector_ll left_bound;
// 	Vector_ll right_bound;

// 	bool pressed;

// public:
// 	Magnetic(Visual_object *par_to_control, const Vector_ll &par_left_bound, const Vector_ll &par_right_bound) 
// 	: to_control(par_to_control), left_bound(par_left_bound), right_bound(par_right_bound), pressed(false)
// 	{ ; }

// 	bool in_bounds(const size_t par_x, const size_t par_y);

// 	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
// 	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
// };

// --------------------------------------------------------------------------------------------------------------------------

class Roll_up_delegate : virtual public Button_delegate
{
private: 
	Visual_object *to_roll_up;

public:
	Roll_up_delegate(Visual_object *par_to_roll_up);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
	Visual_object *get_roll_up();
};

// --------------------------------------------------------------------------------------------------------------------------

class Animating_roll_up_delegate : public Roll_up_delegate, public Animating
{
public:
	Animating_roll_up_delegate(Visual_object *par_to_roll_up, Visual_object *par_to_interact);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

// --------------------------------------------------------------------------------------------------------------------------

class Close_delegate : virtual public Button_delegate
{
private: 
	Visual_object *to_close;

public:
	Close_delegate(Visual_object *par_to_close);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
};

class Close_interactive_delegate : public Close_delegate
{
private:
	Visual_object *to_interact;

public:
	Close_interactive_delegate(Visual_object *par_to_close, Visual_object *par_to_interact);

	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

class Animating_close_delegate : public Close_delegate, public Animating
{
private:
	Visual_object *to_interact;

public:
	Animating_close_delegate(Visual_object *par_to_close, Visual_object *par_to_interact);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

// --------------------------------------------------------------------------------------------------------------------------

// такого шоб я тут не видела 
class Change_color : public Button_delegate
{
private:
	Color color;

public:
	Change_color(const Color &par_color);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
};

// --------------------------------------------------------------------------------------------------------------------------

class Change_thickness : public Button_delegate
{
private:
	size_t size;

public:
	Change_thickness(const size_t par_size);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
};

// --------------------------------------------------------------------------------------------------------------------------

class Change_thickness_non_fixedly : public Button_delegate
{
private:
	size_t current_size;

public:
	Change_thickness_non_fixedly(const size_t par_size);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
};

// --------------------------------------------------------------------------------------------------------------------------

class Drag_and_drop_delegate : public Button_delegate
{
private:
	Visual_object *to_change_place;

	bool clicked;

	Vector_ll first_position;
	Vector_ll last_position;

public:
	Drag_and_drop_delegate(Visual_object *par_to_change_place);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

// --------------------------------------------------------------------------------------------------------------------------

class One_dim_move : public Button_delegate
{
private:
	Visual_object *to_change_place;

	bool clicked;
	bool x_dimension;

	Vector_ll first_position;
	Vector_ll last_position;

public:
	One_dim_move(Visual_object *par_to_change_place, const bool par_x_dimension);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

// --------------------------------------------------------------------------------------------------------------------------

class Change_fixedly : virtual public Button_delegate
{
private:
	Visual_object *to_control;

	long long delta;
	bool change_x;

public:
	Change_fixedly(Visual_object *par_to_control, const long long par_delta, const bool par_change_x);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
};

// --------------------------------------------------------------------------------------------------------------------------

class Animating_change_fixedly : public Change_fixedly, public Animating
{
public:
	Animating_change_fixedly(Visual_object *par_to_control, const long long par_delta, const bool par_change_x, Visual_object *par_to_animate);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
}; 

// --------------------------------------------------------------------------------------------------------------------------

class Magnet_control : public Button_delegate
{
private:
	Visual_object *to_control;

public:
	Magnet_control(Visual_object *par_to_control)
	: to_control(par_to_control)
	{
		;
	}

	bool on_mouse_click(const size_t par_x, const size_t par_y) override
	{
		return to_control->on_mouse_click(true, par_x, par_y);
	}
	bool on_mouse_release() override
	{
		return to_control->on_mouse_click(false, to_control->get_position().get_x(), to_control->get_position().get_y());
	}
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override
	{
		return to_control->on_mouse_move(from, to);
	}
};

// --------------------------------------------------------------------------------------------------------------------------

class Pick_tool : virtual public Button_delegate
{
private:
	Tool *tool;
	// Toolbar *toolbar;

public:
	Pick_tool(Tool *par_tool);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
};

// --------------------------------------------------------------------------------------------------------------------------

class Animating_pick_tool : public Pick_tool, public Animating
{
public:
	Animating_pick_tool(Tool *par_tool, Visual_object *par_to_animate);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

// --------------------------------------------------------------------------------------------------------------------------

class Roll_up_confirmation : virtual public Button_delegate
{
private:
	Visual_object *to_roll_up;

public:
	Roll_up_confirmation(Visual_object *par_roll_up);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
};

// --------------------------------------------------------------------------------------------------------------------------

class Popup_color_confirmation : public Roll_up_confirmation
{
private:
	Color *color;

public:
	Popup_color_confirmation(Visual_object *par_roll_up, Color *to_set)
	: Roll_up_confirmation(par_roll_up), color(to_set)
	{}

	bool on_mouse_click(const size_t par_x, const size_t par_y) override
	{
		Roll_up_confirmation::on_mouse_click(par_x, par_y);

		return true;
	}
	bool on_mouse_release() override
	{
		Roll_up_confirmation::on_mouse_release();
		Toolbar::get_instance()->set_color(*color);
		
		return true;
	}
};

// --------------------------------------------------------------------------------------------------------------------------

class Popup_text_confirmation : public Roll_up_confirmation
{
private:
	char **text;

public:
	Popup_text_confirmation(Visual_object *par_roll_up, char **par_text);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
};

// --------------------------------------------------------------------------------------------------------------------------

// class Open_file : public Button_delegate
// {
// public:
// 	Popup_text_confirmation(const char *filename);

// 	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
// 	bool on_mouse_release() override;
// };

#endif // GRAPHICAL_DELEGATES
