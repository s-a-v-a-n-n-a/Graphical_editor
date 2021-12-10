#ifndef DIALOG_WINDOW_H
#define DIALOG_WINDOW_H

#include "Window.hpp"
#include "Color_selection.hpp"
#include "../GUI/Input_string.hpp"
#include "../GUI/Slider.hpp"

class Dialog : public Window
{
private:
	size_t offset;

public:
	Dialog(const Visual_object::Config &par_base);
	
	Slider *create_slider();
	Color_selection_window *create_color_picker();
	Input_string *create_input_string();

	double get_fraction(Slider *slider);
	Color get_color(Color_selection_window *color_picker);
	char *get_text(Input_string *input);
};

Dialog *create_dialog_window(const size_t width, const size_t height);
void destroy_dialog_window(Dialog *dialog_window);

#endif // DIALOG_WINDOW_H
