#include "Interface.hpp"
#include "../Editor/Application.hpp"

Interface::Interface()
: PUPPY::AppInterface()
{
	render = new Render();
	; // ?????????????????????????
}

Interface::~Interface()
{
	delete render;
}

void Interface::log(const char *fmt, ...) const
{
	va_list arg;
	va_start(arg, fmt);

	printf(fmt, arg);
	printf("\n");

	va_end(arg);
}

double Interface::get_absolute_time() const
{
	return Application::get_app()->get_time();
}

RGBA Interface::get_color() const
{
	Color color = Application::get_app()->get_tools()->get_color();

	return *((PRGBA*)&(color));
}

float Interface::get_size() const
{
	return (float)Application::get_app()->get_tools()->get_active_tool()->get_size();
}

void Interface::set_color(const PUPPY::RGBA &color) const
{
	Application::get_app()->get_tools()->set_color(app_translate_color(color));
}

void Interface::set_size(float size) const
{
	Application::get_app()->get_tools()->get_active_tool()->set_size((size_t)size);
}

RenderTarget *Interface::get_target()  const
{
	// return Application::get_app()->get_plugins()->get_render_target(); // no such function yet
	return render;
}

RenderTarget *Interface::get_preview() const
{
	// return Application::get_app()->get_plugins()->get_render_target(); // no such function yet
	return render; // no such function yet
}

void Interface::flush_preview() const
{
	((Graphical_editor_main_page*)Application::get_app()->get_default())->get_active_canvas()->apply((Color*)data, mode);
}
