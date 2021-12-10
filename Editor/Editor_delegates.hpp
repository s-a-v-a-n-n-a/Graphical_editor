#ifndef EDITOR_DELEGATES
#define EDITOR_DELEGATES

class Create_canvas;
class Canvas_keeper;

#include "../GUI/Button_delegate.hpp"
#include "Graphical_delegates.hpp"
#include "Canvas_manager_manager.hpp"

#include "Effects/Canvas_effects.hpp"
#include "Search_box.hpp"

class Create_canvas : virtual public Button_delegate
{
private:
	// Pencil *pencil;
	Canvas_manager_manager *manager;

public:
	Create_canvas(Canvas_manager_manager *par_manager);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
};

// -------------------------------------------------------------------------------------------------

class Interactive_create_canvas : public Create_canvas, public Interactive
{
public:
	Interactive_create_canvas(Canvas_manager_manager *par_manager, Visual_object *par_to_interact);

	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

// -------------------------------------------------------------------------------------------------

class Animating_create_canvas : public Create_canvas, public Animating
{
public:
	Animating_create_canvas(Canvas_manager_manager *par_manager, Visual_object *par_to_animate);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;

	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

// -------------------------------------------------------------------------------------------------

class Canvas_keeper : public Button_delegate
{
private:
	Visual_object *to_keep;

public:
	Canvas_keeper(Visual_object *par_to_keep);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
};

// -------------------------------------------------------------------------------------------------

class Effect_changer : public Button_delegate
{
protected:
	// Canvas *to_change;
	Affected<Canvas> *to_change;

public:
	// Effect_changer(Canvas *par_to_change) : to_change(par_to_change) {;}
	Effect_changer(Affected<Canvas> *par_to_change) : to_change(par_to_change) {;}

	// void set_changable(Canvas *par_to_change) { to_change = par_to_change; }
	void set_changable(Affected<Canvas> *par_to_change) { to_change = par_to_change; }

	bool on_mouse_click(const size_t par_x, const size_t par_y) override { return false; }
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override { return false; }
};

// -------------------------------------------------------------------------------------------------

class Red_component_changer : public Effect_changer
{
private:
	Red_effect *effect;

public:
	Red_component_changer(Affected<Canvas> *par_to_change) 
	: Effect_changer(par_to_change)
	{
		effect = new Red_effect((Canvas*)par_to_change);
		to_change->add_effect(effect);
	}

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

// -------------------------------------------------------------------------------------------------

class Green_component_changer : public Effect_changer
{
private:
	Green_effect *effect;

public:
	Green_component_changer(Affected<Canvas> *par_to_change) 
	: Effect_changer(par_to_change) 
	{
		effect = new Green_effect((Canvas*)par_to_change);
		to_change->add_effect(effect);
	}

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

// -------------------------------------------------------------------------------------------------

class Blue_component_changer : public Effect_changer
{
private:
	Blue_effect *effect;

public:
	Blue_component_changer(Affected<Canvas> *par_to_change) 
	: Effect_changer(par_to_change)
	{
		effect = new Blue_effect((Canvas*)par_to_change);
		to_change->add_effect(effect);
	}

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

// -------------------------------------------------------------------------------------------------

class Color_picker_creator : virtual public Button_delegate
{
private:
	Vector_ll position;

public:
	Color_picker_creator(const Vector_ll &par_position);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
};

// -------------------------------------------------------------------------------------------------

class Plugin_input_creator : virtual public Button_delegate
{
private:
	Vector_ll position;

public:
	Plugin_input_creator(const Vector_ll &par_position);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
};

// -------------------------------------------------------------------------------------------------

class Animating_color_picker_creator : public Color_picker_creator, public Animating
{
public:
	Animating_color_picker_creator(const Vector_ll &par_position, Visual_object *par_to_interact);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

// -------------------------------------------------------------------------------------------------

class Animating_plugin_input_creator : public Plugin_input_creator, public Animating
{
public:
	Animating_plugin_input_creator(const Vector_ll &par_position, Visual_object *par_to_interact);

	bool on_mouse_click(const size_t par_x, const size_t par_y) override;
	bool on_mouse_release() override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
};

#endif // EDITOR_DELEGATES