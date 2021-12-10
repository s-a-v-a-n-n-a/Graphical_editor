#include "Input_string.hpp"

Input_string::Input_string(const Visual_object::Config &base)
: Visual_object(base), string(get_width()), uppercase(false), pressed(false) {}

char *Input_string::get_message()
{
	return string.get_string();
}

bool Input_string::on_key_pressed(const bool pressed_state, const unsigned key_mask)
{
	if (pressed)
		if (pressed_state)
		{
			if (key_mask == (size_t)Key::LSHIFT)
				uppercase = true;

			if (key_mask <= (size_t)Key::Z)
			{
				char begin_symbol = 'a';
				if (uppercase)
					begin_symbol = 'A';
				string.add_symbol(begin_symbol + key_mask - (size_t)Key::A);

				return true;
			}
			else if (key_mask >= (size_t)Key::NUM0 && key_mask <= (size_t)Key::NUM9)
			{
				string.add_symbol('0' + key_mask - (size_t)Key::NUM0);

				return true;
			}
			else if (key_mask == (size_t)Key::BACKSPACE)
			{
				string.delete_symbol();

				return true;
			}

			return false;
		}
		else
		{
			if (key_mask == (size_t)Key::LSHIFT)
				uppercase = false;

			return false;
		}
	else
		return false;
}

bool Input_string::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	bool result = false;

	bool from_in = point_inside(from.get_x(), from.get_y());
	bool to_in = point_inside(to.get_x(), to.get_y());

	if (from_in || to_in)
	{
		result = true;
	}
	else
	{
		result = false;
	}

	if (!to_in)
		pressed = false;

	return result;
}

bool Input_string::on_mouse_click(const bool state, const size_t par_x, const size_t par_y)
{
	if (point_inside(par_x, par_y))
	{
	    if (state)
    	{
    		pressed = true;
    	}
   //  	else if (pressed)
   //  	{
			// set_active_state(true);
   //  		pressed = false;
   //  	}

	    return true;
	}
	else
		return false;
}

void Input_string::draw(Screen_information *screen)
{
	Visual_object::draw(screen);

	Vector_ll position = get_position() + Vector_ll(20, 5);
	screen->draw_text(string.get_string(), position, BLACK, get_height() - 10, false);
}
