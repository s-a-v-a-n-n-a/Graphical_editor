#include "Search_box.hpp"

const size_t DEFAULT_MESSAGE_SIZE = 10;

Search_box::Search_box(const Visual_object::Config &par_base)
: Closing_window(par_base)
{
	message = new char[DEFAULT_MESSAGE_SIZE];

	size_t offset = 10;
	size_t vertical_offset = DEFAULT_BUTTON_HEIGHT;
	field = create_input_string(get_position() + Vector_ll(offset, DEFAULT_BUTTON_HEIGHT + vertical_offset), get_width() - offset * 2, DEFAULT_BUTTON_HEIGHT);

	Popup_text_confirmation *delegate = new Popup_text_confirmation(this, &message);
	ok_button = new Button({(size_t)Vidget_type::BUTTON, get_position() + Vector_ll(offset, (DEFAULT_BUTTON_HEIGHT + vertical_offset * 5 / 2)), nullptr, GREY, get_width() - offset * 2, (DEFAULT_BUTTON_HEIGHT * 2)}, delegate, "OK");
	
	add_visual_object(ok_button);
}

Input_string *Search_box::create_input_string(const Vector_ll &position, const size_t width, const size_t height)
{
	Input_string *input = new Input_string({(size_t)Vidget_type::INPUT_STRING, position, nullptr, WHITE, width, height});

	add_visual_object(input);
	return input;
}

void Search_box::update_text(char *new_text)
{
	size_t new_text_size = strlen(new_text);
	if (new_text_size + 1 > strlen(message))
	{
		delete [] message;
		message = new char[new_text_size + 1];
	}

	memcpy(message, new_text, new_text_size);
	message[new_text_size] = '\0';
}

void Search_box::draw(Screen_information *screen)
{
	Visual_object::draw(screen);

	Visual_object **objects_array = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		if (objects_array[i]->get_visible())
		{
			objects_array[i]->draw(screen);
		}
	}
}

bool Search_box::on_mouse_click(const bool state, const size_t par_x, const size_t par_y)
{
	if (point_inside(par_x, par_y))
	{
		Visual_object::on_mouse_click(state, par_x, par_y);

		bool result = field->on_mouse_click(state, par_x, par_y);
		if (result)
		{
			update_text(field->get_message());
			return true;
		}

		update_text(field->get_message());
		result = ok_button->on_mouse_click(state, par_x, par_y);
		
		return result;
	}

	return false;
}


