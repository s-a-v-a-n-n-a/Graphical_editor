#include "Vidget_button_container.hpp"

Vidget_button_container::Vidget_button_container(const Visual_object::Config &par_base, Button_delegate *par_delegate, const char *text, PUPPY::Button *par_ward)
: Button(par_base, par_delegate, text), ward(par_ward)
{
	;
}

Vidget_button_container::Vidget_button_container(const Visual_object::Config &par_base, Button_delegate *par_delegate, PUPPY::Button *par_ward)
: Button(par_base, par_delegate), ward(par_ward)
{
	;
}

bool Vidget_button_container::on_mouse_click(const bool state, const size_t par_x, const size_t par_y)
{
	bool was_pressed = get_pressed();
	bool result = Button::on_mouse_click(state, par_x, par_y);

	if (!state)
	{
		auto vidget_handler = ward->get_handler();
		if (was_pressed && vidget_handler)
		{
			vidget_handler();
		}
	}

	return result;
}

bool Vidget_button_container::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	bool was_pressed = get_pressed();
	bool result = Button::on_mouse_move(from, to);

	// auto vidget_handler = ward->get_handler();
	// if (was_pressed && vidget_handler)
	// {
	// 	printf("here\n");
	// 	vidget_handler();
	// }

	return result;
}

