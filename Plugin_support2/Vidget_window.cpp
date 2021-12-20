#include "Vidget_window.hpp"
#include "Render.hpp"
#include "../Editor/Application.hpp"

Vidget_window::Vidget_window(PUPPY::Vec2f position, PUPPY::Vec2f size, const char *name, PUPPY::Widget *parent)
: PUPPY::Window(), Vidget(position, size, parent)
{
	Vector_ll app_position = app_translate_vector(position);
	Vector_ll app_size = app_translate_vector(size);

	Full_texture *background = Application::get_app()->get_rescrs()->create_texture(WINDOW_BACKGROUND, (size_t)app_size.get_x(), (size_t)app_size.get_y());
	
	Vidget *par_parent = dynamic_cast<Vidget*>(parent);
	Visual_object *visual_parent = nullptr;
	if (par_parent)
		visual_parent = par_parent->get_analog();

	dialog = new Vidget_window_container({ visual_parent, (size_t)Vidget_type::DIALOG, app_position, background, TRANSPARENT, (size_t)app_size.get_x(), (size_t)app_size.get_y()}, name, this);
}

Vidget_window::~Vidget_window()
{
	delete dialog;
}

void Vidget_window::set_show_handler(PUPPY::Window::HandlerType &handler_)
{
	show_handler = handler_;
}

PUPPY::Window::HandlerType &Vidget_window::get_show_handler()
{
	return show_handler;
}


void Vidget_window::set_hide_handler(PUPPY::Window::HandlerType &handler_)
{
	hide_handler = handler_;
}

PUPPY::Window::HandlerType &Vidget_window::get_hide_handler()
{
	return hide_handler;
}


bool Vidget_window::set_name(const char *name)
{
	return false;
}

const char *Vidget_window::get_name()
{
	return nullptr;
}

Vidget_window_container *Vidget_window::get_dialog()
{
	return dialog;
}

