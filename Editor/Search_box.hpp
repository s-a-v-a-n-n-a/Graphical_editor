#ifndef SEARCH_BOX_HPP
#define SEARCH_BOX_HPP

#include "Window.hpp"
#include "Graphical_delegates.hpp"
#include "../GUI/Input_string.hpp"

extern const size_t DEFAULT_MESSAGE_SIZE;

class Search_box : public Closing_window
{
private:
	char *message;

	Input_string *field;
	Button *ok_button;

public:
	Search_box(const Visual_object::Config &par_base);

	Input_string *create_input_string(const Vector_ll &position, const size_t width, const size_t height);

	void update_text(char *new_text);

	void draw(Screen_information *screen) override;
	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override;
};

#endif // SEARCH_BOX_HPP
