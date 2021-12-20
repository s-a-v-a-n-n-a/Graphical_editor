#ifndef VIDGET_WINDOW_HPP
#define VIDGET_WINDOW_HPP

#include "plugin_std_2.hpp"
#include "Vidget.hpp"
#include "Vidget_window_container.hpp"

class Vidget_window : public PUPPY::Window, public Vidget
{
private:
	Vidget_window_container *dialog;
	PUPPY::Window::HandlerType hide_handler;
	PUPPY::Window::HandlerType show_handler;
	
public:
	Vidget_window(PUPPY::Vec2f position, PUPPY::Vec2f size, const char *name = nullptr, PUPPY::Widget *parent = nullptr);
	~Vidget_window();

	void set_show_handler(PUPPY::Window::HandlerType &handler_) override;
    PUPPY::Window::HandlerType &get_show_handler() override;

    void set_hide_handler(PUPPY::Window::HandlerType &handler_) override;
    PUPPY::Window::HandlerType &get_hide_handler() override;

    bool set_name(const char *name) override;
    const char *get_name() override;

    Vidget_window_container *get_dialog();
};

#endif // VIDGET_WINDOW_HPP
