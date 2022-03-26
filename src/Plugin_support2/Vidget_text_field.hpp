#ifndef VIDGET_TEXT_FIELD_HPP
#define VIDGET_TEXT_FIELD_HPP

#include "plugin_std_2.hpp"
#include "Vidget.hpp"
#include "Vidget_text_field_container.hpp"

class Vidget_text_field : public PUPPY::TextField, public Vidget
{
private:
	Vidget_text_field_container *text_field;
	PUPPY::TextField::HandlerType handler;

public:
	Vidget_text_field(PUPPY::Vec2f position, PUPPY::Vec2f size, PUPPY::Widget *parent = nullptr);
	~Vidget_text_field();

	void set_handler(const PUPPY::TextField::HandlerType &handler_) override;
    PUPPY::TextField::HandlerType &get_handler() override;

    std::string_view get_text() const override;
    void set_text(std::string_view text) override;

    Vidget_text_field_container *get_text_field();
};

#endif // VIDGET_TEXT_FIELD_HPP
