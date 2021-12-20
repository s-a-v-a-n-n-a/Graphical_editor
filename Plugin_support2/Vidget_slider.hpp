#ifndef VIDGET_SLIDER_HPP
#define VIDGET_SLIDER_HPP

#include "plugin_std_2.hpp"
#include "Vidget.hpp"
#include "Vidget_slider_container.hpp"

class Vidget_slider : public PUPPY::Slider, public Vidget
{
private:
	Vidget_slider_container *slider;
	PUPPY::Slider::HandlerType handler;

public:
	Vidget_slider(PUPPY::Slider::Type type, PUPPY::Vec2f position, PUPPY::Vec2f size, PUPPY::Widget *parent = nullptr);
	~Vidget_slider();

	void set_handler(const PUPPY::Slider::HandlerType &handler_) override;
    PUPPY::Slider::HandlerType &get_handler() override;

    PUPPY::Vec2f get_fraction_2d() override;
    void set_fraction_2d(const PUPPY::Vec2f &frac) override;

    float get_fraction() override;
    void set_fraction(float frac) override;
};

#endif // VIDGET_SLIDER_HPP
