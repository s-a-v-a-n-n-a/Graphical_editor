#include "Vidget_button.hpp"
#include "Render.hpp"
#include "../Editor/Application.hpp"

Vidget_button::Vidget_button(PUPPY::Vec2f position, PUPPY::Vec2f size, const char *caption, PUPPY::Widget *parent)
: PUPPY::Button(), Vidget(position, size, parent)
{
	Vector_ll app_position = app_translate_vector(position);
	Vector_ll app_size = app_translate_vector(size);

	Animating_texture *texture = Application::get_app()->get_rescrs()->create_texture(SIMPLE_BUTTON, app_size.get_x(), app_size.get_y(), SIMPLE_BUTTON_MOVE, nullptr);
	
	Vidget *par_parent = dynamic_cast<Vidget*>(parent);
	Visual_object *visual_parent = nullptr;
	if (par_parent)
		visual_parent = par_parent->get_analog();

	if (caption)
		button = new Vidget_button_container({ visual_parent, (size_t)Vidget_type::BUTTON, app_position, texture, TRANSPARENT, (size_t)app_size.get_x(), (size_t)app_size.get_y() }, nullptr, caption, this);
	else
		button = new Vidget_button_container({ visual_parent, (size_t)Vidget_type::BUTTON, app_position, texture, TRANSPARENT, (size_t)app_size.get_x(), (size_t)app_size.get_y() }, nullptr, this);

	Animating *delegate = new Animating(button);
	button->set_delegate(delegate);
}

Vidget_button::~Vidget_button()
{
	delete button;
}

void Vidget_button::set_handler(const PUPPY::Button::HandlerType &handler_)
{
	handler = handler_;
}

PUPPY::Button::HandlerType &Vidget_button::get_handler()
{
	return handler;
}

Vidget_button_container *Vidget_button::get_button()
{
	return button;
}
