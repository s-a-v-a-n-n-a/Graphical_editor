#ifndef THICKNESS_WINDOW_H
#define THICKNESS_WINDOW_H

#include "../GUI/Slider.hpp"

#include "Graphical_delegates.hpp"
#include "Window.hpp"

const size_t INDENT_SIZE = 10;

class Thickness_window : public Window 
{
private:
	Slider *slider;

public:
	Thickness_window(const Visual_object::Config &par_base);

	Slider *create_slider(const Vector_ll &position, const size_t width, const size_t height, Button_delegate *par_delegate);

	void tick(const double delta) override;
};

#endif // THICKNESS_WINDOW_H
