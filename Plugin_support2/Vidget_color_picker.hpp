#ifndef VIDGET_COLOR_PICKER_HPP
#define VIDGET_COLOR_PICKER_HPP

#include "plugin_std_2.hpp"
#include "Vidget.hpp"
#include "Vidget_color_picker_container.hpp"

class Vidget_color_picker : public PUPPY::ColorPicker, public Vidget
{
private:
	Vidget_color_picker_container *color_picker;
	PUPPY::ColorPicker::HandlerType handler;

public:
	Vidget_color_picker(PUPPY::Vec2f position, PUPPY::Vec2f size, PUPPY::Widget *parent = nullptr);
	~Vidget_color_picker();

	void set_handler(const PUPPY::ColorPicker::HandlerType &handler_) override;
    PUPPY::ColorPicker::HandlerType &get_handler() override;

    PUPPY::RGBA get_color() override;
    void set_color(PUPPY::RGBA color) override;

    Vidget_color_picker_container *get_color_picker();
};

#endif // VIDGET_COLOR_PICKER_HPP
