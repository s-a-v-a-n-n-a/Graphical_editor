#ifndef VIDGET_WINDOW_CONTAINER_HPP
#define VIDGET_WINDOW_CONTAINER_HPP

#include "plugin_std_2.hpp"
#include "../Editor/Dialog_window.hpp"

class Vidget_window_container : public Dialog
{
private:
	PUPPY::Window *ward;

	bool open_state;

public:
	Vidget_window_container(const Visual_object::Config &par_base, const char *text, PUPPY::Window *par_ward)
	: Dialog(par_base, text), ward(par_ward), open_state(true) 
	{
		auto show_handler = ward->get_show_handler();
		if (show_handler)
		{
			show_handler();
		}
		else
		{
			printf("Haha, no handler\n");
		}
	}
	~Vidget_window_container() {}

	void tick(const double delta) override
	{
		auto hide_handler = ward->get_hide_handler();
		auto show_handler = ward->get_show_handler();

		if (open_state && !get_visible() && hide_handler)
		{
			hide_handler();
			open_state = false;
		}
		else if (!open_state && get_visible() && show_handler)
		{
			show_handler();
			open_state = true;
		}
	}

	void draw(Screen_information *screen) override;

	PUPPY::Window *get_ward() { return ward; }

	void add_visual_object(Visual_object *par_object) override;
};

#endif // VIDGET_WINDOW_CONTAINER_HPP
