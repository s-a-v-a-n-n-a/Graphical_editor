#include "Vidget_factory.hpp"
#include "../Editor/Application.hpp"

Vidget_factory::Vidget_factory(Visual_object *par_root)
: windows()
{
	root = new Vidget(app_translate_vector_back(par_root->get_position()), app_translate_vector_back(Vector_ll(par_root->get_width(), par_root->get_height())), nullptr);
	root->set_analog(par_root);
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
	Vidget_button *button = new Vidget_button(body.position, body.size, nullptr, parent);
	
	cast_parent(parent)->add_visual_object(button->get_analog());
	
	return button;
}

PUPPY::Button *Vidget_factory::button(const PUPPY::Vec2f &pos, const char *caption, PUPPY::Widget *parent) const
{
	size_t current_button_size = get_text_length(GHOST_TYPE, caption, INCREASED_BUTTON_HEIGHT / 2);
	Vidget_button *button = new Vidget_button(pos, PUPPY::Vec2f((float)current_button_size, INCREASED_BUTTON_HEIGHT), caption, parent);
	
	cast_parent(parent)->add_visual_object(button->get_analog());

	return button;
}

PUPPY::Slider *Vidget_factory::slider(PUPPY::Slider::Type type, const PUPPY::WBody &body, PUPPY::Widget *parent) const
{
	Vidget_slider *slider = new Vidget_slider(type, body.position, body.size, parent);
	
	cast_parent(parent)->add_visual_object(slider->get_analog());

	return slider;
}

PUPPY::TextField *Vidget_factory::text_field(const PUPPY::WBody &body, PUPPY::Widget *parent) const
{
	Vidget_text_field *text_field = new Vidget_text_field(body.position, body.size, parent);

	cast_parent(parent)->add_visual_object(text_field->get_analog());

	return text_field;
}

PUPPY::Window *Vidget_factory::window(const char *name, const PUPPY::WBody &body, PUPPY::Widget *parent) const
{
	Vidget_window *window = new Vidget_window(body.position, body.size, name, parent);
	
	Visual_object *editor = Application::get_app()->get_default();
	editor->add_visual_object(window->get_analog());

	windows.push_back(body);

	return window;
}

PUPPY::ColorPicker *Vidget_factory::color_picker(const PUPPY::WBody &body, PUPPY::Widget *parent) const
{
	Vidget_color_picker *picker = new Vidget_color_picker(body.position, body.size, parent);
	
	cast_parent(parent)->add_visual_object(picker->get_analog());

	return picker;
}

PUPPY::Label *Vidget_factory::label(const PUPPY::Vec2f &pos, const char *text, PUPPY::Widget *parent) const
{
	Vidget_label *label = new Vidget_label(pos, text, parent);
	
	cast_parent(parent)->add_visual_object(label->get_analog());

	return label;
}

PUPPY::Widget *Vidget_factory::abstract(const PUPPY::WBody &body, PUPPY::Widget *parent) const
{
	Vidget *abstract = new Vidget(body.position, body.size, parent);

	// ?????????????????????????????????????????????

	return abstract;
}

