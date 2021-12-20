#ifndef VIDGET_COLOR_PICKER_CONTAINER_HPP
#define VIDGET_COLOR_PICKER_CONTAINER_HPP

#include "plugin_std_2.hpp"
#include "../Editor/Color_selection.hpp"
#include "Render.hpp"

class Vidget_color_picker_container : public Color_selection_window
{
private:
	PUPPY::ColorPicker *ward;

	Color current_color;

public:
	Vidget_color_picker_container(const Visual_object::Config &par_base, const Color color, PUPPY::ColorPicker *par_ward)
	: Color_selection_window(par_base, color), ward(par_ward), current_color(color) {}
	~Vidget_color_picker_container() {}

	void tick(const double delta) override
	{
		auto vidget_handler = ward->get_handler();
		Color actual_color = get_color();
		if (actual_color != current_color && vidget_handler)
		{
			vidget_handler(app_translate_color_back(actual_color));
			current_color = actual_color;
		}
	}

	PUPPY::ColorPicker *get_ward() { return ward; }
};

#endif // VIDGET_COLOR_PICKER_CONTAINER_HPP
