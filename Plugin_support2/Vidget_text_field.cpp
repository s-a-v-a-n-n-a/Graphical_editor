#include "Vidget_text_field.hpp"

#include <cstring>

#include "Render.hpp"
#include "../Editor/Application.hpp"

Vidget_text_field::Vidget_text_field(PUPPY::Vec2f position, PUPPY::Vec2f size, PUPPY::Widget *parent)
: PUPPY::TextField(), Vidget(position, size, parent)
{
	Vector_ll app_position = app_translate_vector(position);
	Vector_ll app_size = app_translate_vector(size);

	Animating_texture *texture = Application::get_app()->get_rescrs()->create_texture(TEXT_FIELD, (size_t)app_size.get_x(), (size_t)app_size.get_y(), TEXT_FIELD_ACTIVE, NULL);
	
	Vidget *par_parent = dynamic_cast<Vidget*>(parent);
	Visual_object *visual_parent = nullptr;
	if (par_parent)
		visual_parent = par_parent->get_analog();

	text_field = new Vidget_text_field_container({ visual_parent, (size_t)Vidget_type::INPUT_STRING, app_position, texture, TRANSPARENT, (size_t)app_size.get_x(), (size_t)app_size.get_y() }, this);
}

Vidget_text_field::~Vidget_text_field()
{
	delete text_field;
}

void Vidget_text_field::set_handler(const PUPPY::TextField::HandlerType &handler_)
{
	handler = handler_;
}

PUPPY::TextField::HandlerType &Vidget_text_field::get_handler()
{
	return handler;
}


std::string_view Vidget_text_field::get_text() const
{
	return std::string_view{text_field->get_message()};
}

void Vidget_text_field::set_text(std::string_view text)
{
	char *message = new char[text.size() + 1];
	strncpy(message, text.cbegin(), text.size());
	message[text.size()] = '\0';

	text_field->set_message(message);
	delete [] message;
}

Vidget_text_field_container *Vidget_text_field::get_text_field()
{
	return text_field;
}

