#ifndef CANVAS_H
#define CANVAS_H

#include "../GUI/Visual_object_base.hpp"

#include "../Utilities/Affected.hpp"


extern const Color DEFAULT_BACKGROUND_COLOR;

class Canvas : public Visual_object, public Affected<Canvas>
{
protected:
	Full_texture *preview_texture;
	Full_texture *original_texture;
	
	Color current_drawing_color;

	// Finally
	Color *preview;

	Color *original_drawing;
	Color *drawing;

	// Target_texture *texture;
	// Target_texture *result_texture;

	bool drawing_state;
	bool ready;

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

	Color *get_drawing();
	Full_texture *get_drawable_texture();
	Full_texture *get_preview_texture();

	void make_drawing();
	void flush(const Blend_mode &mode);

	void set_drawing_state(const bool state) { drawing_state = state; }

	void draw(Screen_information *screen) override;
	bool point_inside (const size_t par_x, const size_t par_y) override;
	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override; // const Mouse_event par_event, 
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
	void tick(const double delta) override 
	{ 
		Affected::tick(); 
	}

	void apply(Color *data, const Blend_mode &mode);
	void apply(const Shelled_texture *texture, const Blend_mode &mode);
};

#endif // CANVAS_H
