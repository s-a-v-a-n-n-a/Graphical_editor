#ifndef VIDGET_BUTTON_HPP
#define VIDGET_BUTTON_HPP

#include "plugin_std_2.hpp"
#include "Vidget.hpp"
#include "Vidget_button_container.hpp"

class Vidget_button : public PUPPY::Button, public Vidget
{
private:
	Vidget_button_container *button;
	PUPPY::Button::HandlerType handler;

public:
	Vidget_button(PUPPY::Vec2f position, PUPPY::Vec2f size, const char *caption = nullptr, PUPPY::Widget *parent = nullptr);
	~Vidget_button();

	void set_handler(const PUPPY::Button::HandlerType &handler_) override;
    PUPPY::Button::HandlerType &get_handler() override;

    Vidget_button_container *get_button();
};

#endif // VIDGET_BUTTON_HPP
