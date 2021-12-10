#ifndef CANVAS_H
#define CANVAS_H

#include "../GUI/Visual_object_base.hpp"

#include "../Utilities/Affected.hpp"


extern const Color DEFAULT_BACKGROUND_COLOR;

class Canvas : public Visual_object, public Affected<Canvas>
{
protected:
	// Pencil *pencil;

	// Color current_background_color;
	Color current_drawing_color;

	// Finally
	Color *preview;

	Color *original_drawing;
	Color *drawing;

	// RGBA_effect effect[MAX_COLOR_VALUE + 1];

	bool drawing_state;

public:
	Canvas() = delete;
	// + храним информацию о главном
	Canvas(const Visual_object::Config &par_base); // , Pencil *par_pencil
	// Canvas(const size_t par_type, const Vector_ll &par_position, const Color &par_color, const size_t par_width, const size_t par_height, Pencil *par_pencil);
	// Canvas(const size_t par_type, const Vector_ll &par_position, Texture *par_text;ure, const size_t par_width, const size_t par_height, Pencil *par_pencil);

	~Canvas()
	{
		delete [] preview;

		delete [] original_drawing;
		delete [] drawing;
	}

	void draw_point(const size_t par_x, const size_t par_y);

	// void set_red (const unsigned char from, const unsigned char to);
	// void set_green (const unsigned char from, const unsigned char to);
	// void set_blue (const unsigned char from, const unsigned char to);

	Color *get_drawing() { return original_drawing; }

	void make_drawing();

	void draw(Screen_information *screen) override;
	bool point_inside (const size_t par_x, const size_t par_y) override;
	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override; // const Mouse_event par_event, 
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
	void tick(Screen_information *screen, const double delta_time) override 
	{ 
		Affected::tick(); 
	}
};

#endif // CANVAS_H
