#include "Canvas.hpp"

#include "Application.hpp"
// #include "../Tools/Toolbar.hpp"

const Color DEFAULT_BACKGROUND_COLOR = WHITE;

Canvas::Canvas(const Visual_object::Config &par_base) //, Pencil *par_pencil
: Visual_object(par_base), Affected(), current_drawing_color(BLACK), drawing_state(false), ready(true) // pencil(par_pencil),
{
	preview          = new Color[get_width() * get_height()];

	drawing          = new Color[get_width() * get_height()];
	original_drawing = new Color[get_width() * get_height()];
	
	Color *array = ((Full_texture*)get_texture())->get_pixels();
	original_texture = Application::get_app()->get_rescrs()->create_texture((Full_texture*)get_texture());
	preview_texture = Application::get_app()->get_rescrs()->create_texture(get_width(), get_height());

	for (size_t i = 0; i < get_width() * get_height(); ++i)
	{
		preview[i] = array[i];
		original_drawing[i] = array[i];
		drawing[i] = array[i];
	}

	delete [] array;

	Tool *current_tool = Application::get_app()->get_tools()->get_active_tool();
	if (!current_tool->get_pixels())
		current_tool->set_data(original_texture, Vector_ll(get_width(), get_height()));
}

/*void Canvas::draw_point(const size_t par_x, const size_t par_y)
{
	// set_applied(false);

	// size_t width  = get_width();
	// size_t height = get_height();

	// size_t position_x = get_position().get_x();
	// size_t position_y = get_position().get_y();

	// size_t y_coord = position_y + get_height() - (par_y - position_y);

	// Tool *current_tool = Application::get_app()->get_tools()->get_active_tool();
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
	// Affected::tick(const double delta);

	// get_texture()->set_texture(drawing, get_width(), get_height());
}*/

void Canvas::draw(Screen_information *screen)
{
	if (!ready)
	{
		make_drawing();
		ready = true;
	}

	// screen->draw_texture(get_position(), original_texture->get_texture(), get_width(), get_height());
	Visual_object::draw(screen);
	screen->draw_texture(get_position(), preview_texture->get_texture(), get_width(), get_height());
}

bool Canvas::point_inside (const size_t par_x, const size_t par_y)
{
	size_t low_bound_x = get_position().get_x();
	size_t low_bound_y = get_position().get_y();

	if (par_x >= low_bound_x && par_x < low_bound_x + get_width() && par_y >= low_bound_y && par_y <= low_bound_y + get_height())
		return true;

	return false;
}

Color *Canvas::get_drawing() 
{ 
	ready = false; 
	return original_texture->get_pixels(); 
}

Full_texture *Canvas::get_drawable_texture()
{
	return original_texture;
}

Full_texture *Canvas::get_preview_texture()
{
	return preview_texture;
}

void Canvas::make_drawing()
{
	// for (size_t i = 0; i < get_width() * get_height(); ++i)
	// {
	// 	drawing[i] = original_drawing[i];
	// }
	// Color *data = original_texture->get_pixels();
	((Full_texture*)get_texture())->set_texture(original_texture->get_texture());

	// Affected::tick(const double delta);
}

void Canvas::flush(const Blend_mode &mode)
{
	original_texture->add_texture(preview_texture, blending_mode(mode));
	preview_texture->clear();
	make_drawing();
}

bool Canvas::on_mouse_click (const bool state, const size_t par_x, const size_t par_y)
{
	if (!point_inside(par_x, par_y))
		return false;

	Tool *current_tool = Application::get_app()->get_tools()->get_active_tool();

	if (current_tool->get_color() != current_drawing_color)
		current_drawing_color = current_tool->get_color();

	if (state)
	{
		set_applied(false);
		current_tool->on_mouse_press(original_texture, Vector_ll(get_width(), get_height()), Vector_ll(par_x, par_y) - get_position());
		make_drawing();

		set_drawing_state(true);
	}
	else if (!state)
	{
		set_applied(false);
		current_tool->on_mouse_release(Vector_ll(par_x, par_y) - get_position());
		flush(Blend_mode::ALPHA);
		make_drawing();

		set_drawing_state(false);
	}

	return true;
}

bool Canvas::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	Tool *current_tool = Application::get_app()->get_tools()->get_active_tool();
	if (point_inside(to.get_x(), to.get_y()) && drawing_state)
	{
		set_applied(false);
		// printf("[Canvas]: %lld %lld\n", (to - get_position()).get_x(), (to - get_position()).get_y());
		current_tool->on_mouse_move(from - get_position(), to - get_position());
		make_drawing();

		return true;
	}
	else
	{
		current_tool->on_mouse_release(from - get_position());
		set_drawing_state(false);
		return false;
	}
}

void Canvas::apply(Color *data, const Blend_mode &mode)
{
	make_drawing();

	((Full_texture*)get_texture())->add_picture(data, get_width(), get_height(), blending_mode(mode));
	// delete [] original_drawing;
	// original_drawing = ((Full_texture*)get_texture())->get_pixels();
	original_texture->set_texture(data, get_width(), get_height());
}

void Canvas::apply(const Shelled_texture *texture, const Blend_mode &mode)
{
	flush(mode);
	// make_drawing();

	original_texture->set_texture(texture);
}
