#include "Dialog_window.hpp"

#include "Application.hpp"

Dialog *create_dialog_window(const size_t width, const size_t height)
{
	Visual_object *editor = Application::get_app()->get_default();

	Vector_ll main_position = editor->get_position();
	Vector_ll main_window_size = Vector_ll(editor->get_width(), editor->get_height());
	Vector_ll dialog_size = Vector_ll(width, height);

	if (dialog_size.get_x() < main_window_size.get_x())
		dialog_size.set_x(main_window_size.get_x());
	if (dialog_size.get_y() < main_window_size.get_y())
		dialog_size.set_y(main_window_size.get_y());
	
	size_t x_pos = main_position.get_x() + rand() % (main_window_size.get_x() - dialog_size.get_x());  
	size_t y_pos = main_position.get_y() + rand() % (main_window_size.get_y() - dialog_size.get_y());  

	Vector_ll position = Vector_ll(x_pos, y_pos);

	Dialog *dialog_window = new Dialog({(size_t)Vidget_type::DIALOG, position, nullptr, TRANSPARENT, (size_t)dialog_size.get_x(), (size_t)dialog_size.get_y()});
	editor->add_visual_object(dialog_window);

	return dialog_window;
}

void destroy_dialog_window(Dialog *dialog_window)
{
	Visual_object *editor = Application::get_app()->get_default();

	editor->very_slow_delete_visual_object(dialog_window);
}

Dialog::Dialog(const Visual_object::Config &par_base)
: Window(par_base), offset(DEFAULT_BUTTON_HEIGHT)
{
	;
}

Slider *Dialog::create_slider()
{
	size_t height = 100 < (get_height() - offset) ? 100 : get_height() - offset; 
	Slider *slider = new Slider({(size_t)Vidget_type::SLIDER, get_position() + Vector_ll(0, offset), NULL, TRANSPARENT, get_width(), height}, NULL, 0, 1, true);

	offset += height;

	add_visual_object(slider);

	return slider;
}

Color_selection_window *Dialog::create_color_picker()
{
	size_t width = get_width();
	size_t height = width < (get_height() - offset) ? width : get_height() - offset; 
	Visual_object::Config picker_base = { (size_t)Vidget_type::COLOR_SELECTION, get_position() + Vector_ll(0, offset), NULL, TRANSPARENT, get_width(), height};

	Color_selection_window *picker = new Color_selection_window(picker_base, RED);

	offset += height;

	add_visual_object(picker);

	return picker;
}

Input_string *Dialog::create_input_string()
{
	size_t height = 50 < (get_height() - offset) ? 50 : get_height() - offset; 
	Animating_texture *text_field_texture = Resources::get_instance()->create_texture(TEXT_FIELD, get_width(), height, TEXT_FIELD_ACTIVE, NULL);
	Input_string *input = new Input_string({(size_t)Vidget_type::INPUT_STRING, get_position() + Vector_ll(0, offset), text_field_texture, TRANSPARENT, get_width(), height});
	
	offset += height;

	add_visual_object(input);

	return input;
}

double Dialog::get_fraction(Slider *slider)
{
	return slider->get_relation();
}

Color Dialog::get_color(Color_selection_window *color_picker)
{
	return color_picker->get_color();
}

char *Dialog::get_text(Input_string *input)
{
	return input->get_message();
}

