#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Button_delegate.hpp"
#include "../GUI/Button.hpp"

class Button_manager : public Visual_object
{
private:
	Vector_ll current_end_position;

public:
	Button_manager(const Visual_object::Config &par_base);
	~Button_manager();

	Button *add_button(Button_delegate *par_delegate, const char *par_text, const Color par_color, const size_t par_width, const size_t par_height = DEFAULT_BUTTON_HEIGHT);
	Button *add_button(Button_delegate *par_delegate, const char *par_text, Texture *par_texture, const size_t par_width = 0, const size_t par_height = 0);

	// void draw(Screen_information *screen) override;
};

#endif // BUTTON_MANAGER_H
