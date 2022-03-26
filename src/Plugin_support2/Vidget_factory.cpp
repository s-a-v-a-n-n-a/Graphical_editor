#include "Vidget_factory.hpp"
#include "../Editor/Application.hpp"

Vidget_factory::Vidget_factory(Visual_object *par_root)
: windows()
{
	root = new Vidget(app_translate_vector_back(par_root->get_position()), app_translate_vector_back(Vector_ll(par_root->get_width(), par_root->get_height())), nullptr);
	root->set_analog(par_root);

	find_windows(par_root);
}

void Vidget_factory::find_windows(Visual_object *main)
{
	size_t amount = main->get_objects()->get_length();
	if (amount == 0)
		return;

	Visual_object **array = main->get_objects()->get_array();
	
	for (size_t i = 0; i < amount; ++i)
	{
		Window *window = dynamic_cast<Window*>(array[i]);
		if (!window)
		{
			Closing_window *close_window = dynamic_cast<Closing_window*>(array[i]);
			if (!close_window)
			{
				find_windows(array[i]);
			}
			else
			{
				PUPPY::WBody body = PUPPY::WBody(app_translate_vector_back(array[i]->get_position()), { (float)array[i]->get_width(), (float)array[i]->get_height() });
				windows.push_back(body);
			}
		}
		else
		{
			PUPPY::WBody body = PUPPY::WBody(app_translate_vector_back(array[i]->get_position()), { (float)array[i]->get_width(), (float)array[i]->get_height() });
			windows.push_back(body);
		}

		find_windows(array[i]);
	}
}

Visual_object *Vidget_factory::cast_parent(PUPPY::Widget *parent) const
{
	Vidget *par_parent = dynamic_cast<Vidget*>(parent);
	Visual_object *visual_parent = nullptr;
	if (par_parent)
		visual_parent = par_parent->get_analog();

	return visual_parent;
}

PUPPY::Button *Vidget_factory::button(const PUPPY::WBody &body, PUPPY::Widget *parent) const
{
	Vidget_window *their_window = dynamic_cast<Vidget_window*>(parent);
	Dialog *window = their_window->get_dialog();

	Vidget_button *button = new Vidget_button(app_translate_vector_back(app_translate_vector(body.position) + window->get_position() + Vector_ll(0, DEFAULT_BUTTON_HEIGHT)), body.size, nullptr, parent);
	
	window->add_visual_object(button->get_button());
	
	// printf("button\n");

	return button;
}

PUPPY::Button *Vidget_factory::button(const PUPPY::Vec2f &pos, const char *caption, PUPPY::Widget *parent) const
{
	Vidget_window *their_window = dynamic_cast<Vidget_window*>(parent);
	Dialog *window = their_window->get_dialog();

	size_t current_button_size = get_text_length(GHOST_TYPE, caption, INCREASED_BUTTON_HEIGHT / 2);
	Vidget_button *button = new Vidget_button(app_translate_vector_back(app_translate_vector(pos) + window->get_position() + Vector_ll(0, DEFAULT_BUTTON_HEIGHT)), PUPPY::Vec2f((float)current_button_size, INCREASED_BUTTON_HEIGHT), caption, parent);
	
	window->add_visual_object(button->get_button());

	// printf("button\n");
	
	return button;
}

PUPPY::Slider *Vidget_factory::slider(PUPPY::Slider::Type type, const PUPPY::WBody &body, PUPPY::Widget *parent) const
{
	Vidget_window *their_window = dynamic_cast<Vidget_window*>(parent);
	Dialog *window = their_window->get_dialog();

	Vidget_slider *slider = new Vidget_slider(type, app_translate_vector_back(app_translate_vector(body.position) + window->get_position() + Vector_ll(0, DEFAULT_BUTTON_HEIGHT)), body.size, parent);
	
	// Visual_object *visual_parent = cast_parent(parent);
	// if (visual_parent)
	window->add_visual_object(slider->get_slider());

	// printf("slider\n");
	
	return slider;
}

PUPPY::TextField *Vidget_factory::text_field(const PUPPY::WBody &body, PUPPY::Widget *parent) const
{
	Vidget_window *their_window = dynamic_cast<Vidget_window*>(parent);
	Dialog *window = their_window->get_dialog();

	Vidget_text_field *text_field = new Vidget_text_field(app_translate_vector_back(app_translate_vector(body.position) + window->get_position() + Vector_ll(0, DEFAULT_BUTTON_HEIGHT)), body.size, parent);

	// Visual_object *visual_parent = cast_parent(parent);
	// if (visual_parent)
	window->add_visual_object(text_field->get_text_field());

	// printf("text_field\n");
	
	return text_field;
}

PUPPY::Window *Vidget_factory::window(const char *name, const PUPPY::WBody &body, PUPPY::Widget *parent) const
{
	Visual_object *editor = Application::get_app()->get_default();

	Vidget_window *window = new Vidget_window(body.position, app_translate_vector_back(app_translate_vector(body.size) + Vector_ll(0, DEFAULT_BUTTON_HEIGHT)), name, parent);
	
	editor->add_visual_object(window->get_dialog());

	windows.push_back(body);

	return window;
}

PUPPY::ColorPicker *Vidget_factory::color_picker(const PUPPY::WBody &body, PUPPY::Widget *parent) const
{
	Vidget_window *their_window = dynamic_cast<Vidget_window*>(parent);
	Dialog *window = their_window->get_dialog();

	Vidget_color_picker *picker = new Vidget_color_picker(app_translate_vector_back(app_translate_vector(body.position) + window->get_position() + Vector_ll(0, DEFAULT_BUTTON_HEIGHT)), body.size, parent);
	
	// Visual_object *visual_parent = cast_parent(parent);
	// if (visual_parent)
	window->add_visual_object(picker->get_color_picker());

	// printf("color_picker\n");

	return picker;
}

PUPPY::Label *Vidget_factory::label(const PUPPY::Vec2f &pos, const char *text, PUPPY::Widget *parent) const
{
	Vidget_window *their_window = dynamic_cast<Vidget_window*>(parent);
	Dialog *window = their_window->get_dialog();

	Vidget_label *label = new Vidget_label(app_translate_vector_back(app_translate_vector(pos) + window->get_position() + Vector_ll(0, DEFAULT_BUTTON_HEIGHT)), text, parent);
	
	// Visual_object *visual_parent = cast_parent(parent);
	// if (visual_parent)
	window->add_visual_object(label->get_label());

	// printf("label\n");
	
	return label;
}

PUPPY::Widget *Vidget_factory::abstract(const PUPPY::WBody &body, PUPPY::Widget *parent) const
{
	Vidget *abstract = new Vidget(body.position, body.size, parent);

	// ?????????????????????????????????????????????

	return abstract;
}

