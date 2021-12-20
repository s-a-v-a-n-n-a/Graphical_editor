#ifndef VIDGET_BUTTON_CONTAINER_HPP
#define VIDGET_BUTTON_CONTAINER_HPP

#include "plugin_std_2.hpp"
#include "../GUI/Button.hpp"

class Vidget_button_container : public Button
{
private:
	PUPPY::Button *ward;

public:
	Vidget_button_container(const Visual_object::Config &par_base, Button_delegate *par_delegate, const char *text, PUPPY::Button *par_ward);
	Vidget_button_container(const Visual_object::Config &par_base, Button_delegate *par_delegate, PUPPY::Button *par_ward);
	~Vidget_button_container() {}

	virtual bool on_mouse_click  (const bool state, const size_t par_x, const size_t par_y) override; //const Mouse_event par_event,
	virtual bool on_mouse_move	(const Vector_ll from, const Vector_ll to) override;

	PUPPY::Button *get_ward() { return ward; }
};

#endif // VIDGET_BUTTON_CONTAINER_HPP
