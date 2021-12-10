#include "Canvas.hpp"

#include "../Tools/Toolbar.hpp"

const Color DEFAULT_BACKGROUND_COLOR = WHITE;

Canvas::Canvas(const Visual_object::Config &par_base) //, Pencil *par_pencil
: Visual_object(par_base), Affected(), current_drawing_color(BLACK), drawing_state(false) // pencil(par_pencil),
{
	preview          = new Color[get_width() * get_height()];

	drawing          = new Color[get_width() * get_height()];
	original_drawing = new Color[get_width() * get_height()];
	
	Color *array = ((Full_texture*)get_texture())->get_pixels();

	for (size_t i = 0; i < get_width() * get_height(); ++i)
	{
		preview[i] = array[i];
		original_drawing[i] = array[i];
		drawing[i] = array[i];
	}

	delete [] array;

	Tool *current_tool = Toolbar::get_instance()->get_active_tool();
	if (!current_tool->get_pixels())
		current_tool->set_data(get_drawing(), Vector_ll(get_width(), get_height()));
	
	// for (int i = 0; i <= (int)MAX_COLOR_VALUE; ++i)
	// {
	// 	effect[i] = { -1, -1, -1, -1 };
	// }
}

void Canvas::draw_point(const size_t par_x, const size_t par_y)
{
	set_applied(false);

	size_t width  = get_width();
	size_t height = get_height();

	size_t position_x = get_position().get_x();
	size_t position_y = get_position().get_y();

	// size_t y_coord = position_y + get_height() - (par_y - position_y);

	// Tool *current_tool = Toolbar::get_instance()->get_active_tool();
	// size_t tool_size = current_tool->get_size() / 2;
	
	// current_tool->apply(get_drawing(), Vector_ll(get_width(), get_height()), Vector_ll(par_x, par_y) - get_position());
	
	// size_t begin_x = par_x - position_x > tool_size ? par_x - position_x - tool_size : par_x - position_x;
	// size_t begin_y = par_y - position_y > tool_size ? par_y - position_y - tool_size : par_y - position_y;

	// size_t end_x = par_x - position_x + tool_size < width ? par_x - position_x + tool_size : par_x - position_x;
	// size_t end_y = par_y - position_y + tool_size < height ? par_y - position_y + tool_size : par_y - position_y;

	// for (size_t i = begin_y; i < end_y; ++i)
	// 	for (size_t j = begin_x; j < end_x; ++j)
	// 	{
	// 		size_t index = i * width + j;

	// 		original_drawing[index] = current_drawing_color;
			
	// 		// unsigned char red    = effect[original_drawing[index].get_r()].r == -1 ? original_drawing[index].get_r() : effect[original_drawing[index].get_r()].r;
	// 		// unsigned char green  = effect[original_drawing[index].get_g()].g == -1 ? original_drawing[index].get_g() : effect[original_drawing[index].get_g()].g;
	// 		// unsigned char blue   = effect[original_drawing[index].get_b()].b == -1 ? original_drawing[index].get_b() : effect[original_drawing[index].get_b()].b;
	// 		// unsigned char bright = effect[original_drawing[index].get_a()].a == -1 ? original_drawing[index].get_a() : effect[original_drawing[index].get_a()].a;

	// 		// drawing[index].set_a(bright);
	// 		// drawing[index].set_r(red);
	// 		// drawing[index].set_g(green);
	// 		// drawing[index].set_b(blue);
	// 	}
	// Affected::tick();

	// get_texture()->set_texture(drawing, get_width(), get_height());
}

void Canvas::draw(Screen_information *screen)
{
	Visual_object::draw(screen);

	// size_t width = get_width();
	// size_t height = get_height();

	// Color current_color = get_color();

	// Vector_ll position(get_position());

	// screen->draw_image(drawing, get_position(), width, height);
}

bool Canvas::point_inside (const size_t par_x, const size_t par_y)
{
	size_t low_bound_x = get_position().get_x();
	size_t low_bound_y = get_position().get_y();

	if (par_x >= low_bound_x && par_x < low_bound_x + get_width() && par_y >= low_bound_y && par_y <= low_bound_y + get_height())
		return true;

	return false;
}

// void Canvas::set_red (const unsigned char from, const unsigned char to)
// {
// 	size_t width  = get_width();
// 	size_t height = get_height();

// 	effect[from].r = to;
// 	for (size_t i = 0; i < width * height; ++i)
// 	{
// 		if (original_drawing[i].get_r() == from)
// 		{
// 			drawing[i].set_r(to);
// 		}
// 	}

// 	get_texture()->set_texture(drawing, get_width(), get_height());
// }

// void Canvas::set_green (const unsigned char from, const unsigned char to)
// {
// 	size_t width  = get_width();
// 	size_t height = get_height();

// 	effect[from].g = to;
// 	for (size_t i = 0; i < width * height; ++i)
// 	{
// 		if (original_drawing[i].get_g() == from)
// 		{
// 			drawing[i].set_g(to);
// 		}
// 	}

// 	get_texture()->set_texture(drawing, get_width(), get_height());
// }

// void Canvas::set_blue (const unsigned char from, const unsigned char to)
// {
// 	size_t width = get_width();
// 	size_t height = get_height();

// 	effect[from].b = to;
// 	for (size_t i = 0; i < width * height; ++i)
// 	{
// 		if (original_drawing[i].get_b() == from)
// 		{
// 			drawing[i].set_b(to);
// 		}
// 	}

// 	get_texture()->set_texture(drawing, get_width(), get_height());
// }
void Canvas::make_drawing()
{
	for (size_t i = 0; i < get_width() * get_height(); ++i)
	{
		drawing[i] = original_drawing[i];
	}

	Affected::tick();
	get_texture()->set_texture(drawing, get_width(), get_height());
}

bool Canvas::on_mouse_click (const bool state, const size_t par_x, const size_t par_y)
{
	if (!point_inside(par_x, par_y))
		return false;

	Tool *current_tool = Toolbar::get_instance()->get_active_tool();

	if (current_tool->get_color() != current_drawing_color)
		current_drawing_color = current_tool->get_color();

	if (state)
	{
		set_applied(false);
		current_tool->on_mouse_press(get_drawing(), Vector_ll(get_width(), get_height()), Vector_ll(par_x, par_y) - get_position());
		make_drawing();
	}
	else if (!state)
	{
		set_applied(false);
		current_tool->on_mouse_release(Vector_ll(par_x, par_y) - get_position());
		make_drawing();
	}

	return true;
}

bool Canvas::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	Tool *current_tool = Toolbar::get_instance()->get_active_tool();
	if (point_inside(to.get_x(), to.get_y()))
	{
		set_applied(false);
		current_tool->on_mouse_move(from - get_position(), to - get_position());
		make_drawing();

		return true;
	}
	else
	{
		current_tool->on_mouse_release(from - get_position());
		return false;
	}
}
