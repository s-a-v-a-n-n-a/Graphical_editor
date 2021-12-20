#include "Vidget_color_picker.hpp"
#include "Render.hpp"
#include "../Editor/Application.hpp"

Vidget_color_picker::Vidget_color_picker(PUPPY::Vec2f position, PUPPY::Vec2f size, PUPPY::Widget *parent)
: PUPPY::ColorPicker(), Vidget(position, size, parent)
{
	Vector_ll app_position = app_translate_vector(position);
	Vector_ll app_size = app_translate_vector(size);

	Vidget *par_parent = dynamic_cast<Vidget*>(parent);
	Visual_object *visual_parent = nullptr;
	if (par_parent)
		visual_parent = par_parent->get_analog();

	color_picker = new Vidget_color_picker_container({ visual_parent, (size_t)Vidget_type::COLOR_SELECTION, app_position, nullptr, TRANSPARENT, (size_t)app_size.get_x(), (size_t)app_size.get_y() }, RED, this);
}

Vidget_color_picker::~Vidget_color_picker() 
{
	delete color_picker;
}

void Vidget_color_picker::set_handler(const PUPPY::ColorPicker::HandlerType &handler_)
{
	handler = handler_;
}

PUPPY::ColorPicker::HandlerType &Vidget_color_picker::get_handler()
{
	return handler;
}


PUPPY::RGBA Vidget_color_picker::get_color()
{
	return app_translate_color_back(color_picker->get_color());
}

void Vidget_color_picker::set_color(PUPPY::RGBA color)
{
	color_picker->set_current_color(app_translate_color(color));
}


