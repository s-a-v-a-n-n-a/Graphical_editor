#include "Vidget_container.hpp"
#include "Render.hpp"


Vidget_container::Vidget_container(const Visual_object::Config &par_base, PUPPY::Widget *par_ward)
: Visual_object(par_base), ward(par_ward)
{
	;
}

void Vidget_container::draw(Screen_information *screen)
{
	Visual_object::draw(screen);
	ward->on_render(app_translate_draw());
}

bool Vidget_container::on_mouse_click(const bool state, const size_t par_x, const size_t par_y)
{
	bool result = Visual_object::on_mouse_click(state, par_x, par_y);

	if (state)
	{
		ward->on_mouse_press(app_translate_mouse_press(par_x, par_y));
	}
	else
	{
		ward->on_mouse_release(app_translate_mouse_release(par_x, par_y));
	}

	return result;
}

bool Vidget_container::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	bool result = Visual_object::on_mouse_move(from, to);

	ward->on_mouse_move(app_translate_mouse_move(from, to));

	return result;
}

bool Vidget_container::on_key_pressed(const bool pressed_state, const unsigned key_mask)
{
	bool result = Visual_object::on_key_pressed(pressed_state, key_mask);

	if (pressed_state)
		ward->on_key_down(app_translate_key_down(key_mask));
	else
		ward->on_key_up(app_translate_key_up(key_mask));

	return result;
} 

bool Vidget_container::on_text_entered(const char symbol)
{
	bool result = Visual_object::on_text_entered(symbol);

	ward->on_text_enter(app_translate_text_enter(symbol));

	return result;
}

void Vidget_container::tick(const double delta)
{
	Visual_object::tick(delta);

	ward->on_tick(app_translate_tick(delta));
} 
