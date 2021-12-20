#include "Vidget_slider.hpp"
#include "Render.hpp"

Vidget_slider::Vidget_slider(PUPPY::Slider::Type type, PUPPY::Vec2f position, PUPPY::Vec2f size, PUPPY::Widget *parent)
: PUPPY::Slider(), Vidget(position, size, parent)
{
	Vector_ll app_position = app_translate_vector(position);
	Vector_ll app_size = app_translate_vector(size);

	bool horizontal = true;
	if (type == PUPPY::Slider::Type::Y)
		horizontal = false;

	Vidget *par_parent = dynamic_cast<Vidget*>(parent);
	Visual_object *visual_parent = nullptr;
	if (par_parent)
		visual_parent = par_parent->get_analog();

	slider = new Vidget_slider_container({ visual_parent, (size_t)Vidget_type::SLIDER, app_position, nullptr, TRANSPARENT, (size_t)app_size.get_x(), (size_t)app_size.get_y() }, nullptr, 100, 0, horizontal, this);
}

Vidget_slider::~Vidget_slider()
{
	delete slider;
}

void Vidget_slider::set_handler(const PUPPY::Slider::HandlerType &handler_)
{
	handler = handler_;
}

PUPPY::Slider::HandlerType &Vidget_slider::get_handler()
{
	return handler;
}

PUPPY::Vec2f Vidget_slider::get_fraction_2d()
{
	return {get_fraction(), 0};
}

void Vidget_slider::set_fraction_2d(const PUPPY::Vec2f &frac)
{
	set_fraction(frac.x);
}

float Vidget_slider::get_fraction()
{
	return (float)slider->get_relation();
}

void Vidget_slider::set_fraction(float frac)
{
	slider->set_relation((double)frac);
}


