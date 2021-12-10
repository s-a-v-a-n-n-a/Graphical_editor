#include "Color_picker.hpp"

const size_t DEFAULT_POINTER_RADIUS = 5;

Color_picker::Color_picker(const Visual_object::Config &par_base, const Color &par_main_color, Color *par_to_set)
: Visual_object(par_base), main_color(par_main_color), current_position(0, get_height()), to_set(par_to_set)
{
	color_array = new Color[get_width() * get_height()];
	set_main_color(par_main_color);

	Full_texture *circle = Resources::get_instance()->create_texture(PICKING_CIRCLE_TEXTURE, 18, 18);// new Full_texture(WINDOW_BACKGROUND, DEFAULT_COLOR_VIDGET_WIDTH, DEFAULT_COLOR_VIDGET_HEIGHT);
	
	size_t circle_width = circle->get_width();
	size_t circle_height = circle->get_height();

    HSV hsv = get_hsv(*par_to_set);
	current_position = Vector_ll(((double)(hsv.s))/255.0 * ((double)get_width()), (255.0 - (double)hsv.v)/255.0 * ((double)get_height()));

	Visual_object::Config buttton_base = { (size_t)Vidget_type::BUTTON, get_position() + current_position - Vector_ll(circle_width, 0), circle, TRANSPARENT, circle_width, circle_height };
	picker = new Magnetic(buttton_base, this, get_position(), get_position() + Vector_ll(get_width(), get_height()) - Vector_ll(circle_width, circle_height));
	
	add_visual_object(picker);
}

Color_picker::~Color_picker()
{
	delete [] color_array;
}

void Color_picker::set_main_color(const Color &par_main)
{
	main_color = par_main;

	HSV hsv = get_hsv(main_color);

	size_t width = get_width();
	size_t height = get_height();
	for (size_t i = 0; i < width; ++i)
	{
		int value = (int)(255.0 - ((double)i / (double)height) * 255.0);
		for (size_t j = 0; j < height; ++j)
		{
			int saturation = (int)(((double)j / (double)width) * 255.0);

			Color pixel_color = get_rgb({ hsv.h, saturation, value });
			color_array[i * height + j] = pixel_color;
		}
	}
}

void Color_picker::set_color()
{
	// pencil->set_color(color_array[current_position.get_y() * MAX_COLOR_VALUE + current_position.get_x()]);
	// Toolbar::get_instance()->get_tools()->get_array()[0]->set_color(color_array[current_position.get_y() * MAX_COLOR_VALUE + current_position.get_x()]);
	// Toolbar::get_instance()->set_color(color_array[current_position.get_y() * get_height() + current_position.get_x()]);
	(*to_set) = color_array[current_position.get_y() * get_height() + current_position.get_x()];
}

Color Color_picker::get_color()
{
	return color_array[current_position.get_y() * get_height() + current_position.get_x()];
}

bool Color_picker::on_mouse_click(const bool state, const size_t par_x, const size_t par_y)
{
	if (point_inside(par_x, par_y))
	{
		if (state)
		{
			Vector_ll last_position = current_position;
			current_position = Vector_ll(par_x, par_y) - get_position();
			
			// picker->set_position(picker->get_position() + current_position - last_position);
			picker->on_mouse_click(state, par_x - picker->get_width()/2, par_y - picker->get_height()/2);
			
			set_color();

			return true;
		}
		else
			picker->on_mouse_click(state, par_x - picker->get_width()/2, par_y - picker->get_height()/2);

		// picker->on_mouse_click(state, par_x, par_y);
	}

	return false;
}

bool Color_picker::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	// printf("move picker\n");
	// picker->set_position(picker->get_position() + to - last);

	bool result = picker->on_mouse_move(from, to - Vector_ll(picker->get_width()/2, picker->get_height()/2));
	if (result)
	{
		current_position = to - get_position();
		set_color();
	}

	return result;
	// return true;
}

void Color_picker::draw(Screen_information *screen)
{
	Vector_ll position(get_position());

	screen->draw_image(color_array, get_position(), get_width(), get_height());
	picker->draw(screen);
	// Full_texture *circle = new Full_texture(PICKING_CIRCLE_TEXTURE, 18, 18);
	// screen->draw_texture(position + current_position - Vector_ll(circle->get_width()/2, circle->get_height()/2), PICKING_CIRCLE_TEXTURE);
	// delete circle;
}
