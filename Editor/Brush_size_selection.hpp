#ifndef BRUSHES_VIDGET_H
#define BRUSHES_VIDGET_H

#include "../GUI/Visual_object_base.hpp"

#include "Window_control_panel.hpp"
#include "Thickness_palette.hpp"

#include "Window.hpp"

const size_t THICK_PALETTE_HEIGHT = 40 + DEFAULT_BUTTON_HEIGHT;
const size_t THICK_PALETTE_WIDTH = 320;

class Brush_size_selection_window : public Window
{
private:

public:
	// Brush_size_manager(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil);
	Brush_size_selection_window(const Visual_object::Config &par_base)
	: Window(par_base)
	{
		// Palette *palette = new Palette((size_t)Vidget_type::PALETTE, par_position + Vector_ll(0, DEFAULT_BUTTON_HEIGHT), WHITE, 300, 300, par_pencil);
		Thickness_palette *thick_palette = new Thickness_palette({(size_t)Vidget_type::PALETTE, get_position() + Vector_ll(0, DEFAULT_BUTTON_HEIGHT), nullptr, TRANSPARENT, THICK_PALETTE_WIDTH, 40});

		add_visual_object(thick_palette);
	}
	~Brush_size_selection_window() = default;
};

#endif // BRUSHES_VIDGET_H
