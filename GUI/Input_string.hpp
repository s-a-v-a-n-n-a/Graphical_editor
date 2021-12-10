#ifndef INPUT_STRING_H
#define INPUT_STRING_H

#include "../GUI/Visual_object_base.hpp"
#include "../Utilities/Text_string.hpp"

class Input_string : public Visual_object
{
private:
	Text_string string;

	bool pressed;
	bool uppercase;

	// хранить выделение

public:
	Input_string(const Visual_object::Config &base);

	char *get_message();

	bool on_key_pressed(const bool pressed_state, const unsigned key_mask) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override;
	
	void draw(Screen_information *screen) override;

};

#endif // INPUT_STRING_H
