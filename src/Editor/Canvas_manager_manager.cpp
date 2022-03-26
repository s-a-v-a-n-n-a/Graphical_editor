#include "Canvas_manager_manager.hpp"
#include "Application.hpp"

Canvas_manager_manager::Canvas_manager_manager(const Visual_object::Config &par_base)
: Window(par_base), active_canvas(nullptr), canvases_amount(0)
{
	// создаёт Window_control_panel
    // ------------------------------------------------------------------------------
	Button_manager *panel = new Button_manager({ this, (size_t)Vidget_type::BUTTON_MANAGER, get_position() + Vector_ll(0, DEFAULT_BUTTON_HEIGHT), nullptr, MEDIUM_GREY, get_width(), INCREASED_BUTTON_HEIGHT });
	add_visual_object(panel);
	
	// создаёт начальный объект
	// ------------------------------------------------------------------------------
	add_canvas(WINTER_TEXTURE);
}

Window_control_panel *Canvas_manager_manager::create_control_panel(Visual_object *parent, const Vector_ll &position, const size_t width, const size_t height)
{
	Full_texture *texture = Application::get_app()->get_rescrs()->create_texture(WINDOW_HEADER, width, height);

	Visual_object::Config panel_base = { this, (size_t)Vidget_type::WINDOW_CONTROL_PANEL, position, texture, TRANSPARENT, width, height };
	Window_control_panel *control = new Window_control_panel(panel_base, parent);
	add_visual_object(control);

	return control;
}

void Canvas_manager_manager::add_canvas(const char *texture_name)
{
	if (canvases_amount * DEFAULT_TAB_WIDTH >= get_width())
	{
		printf("Unable to create new canvas\n");
		return;
	}

	Full_texture *canvas_texture = nullptr;
	if (texture_name)
		canvas_texture = Application::get_app()->get_rescrs()->create_texture(texture_name, 0, 0);
	else
		canvas_texture = Application::get_app()->get_rescrs()->create_texture(CANVAS_TEXTURE, get_width(), get_height() - DEFAULT_BUTTON_HEIGHT);

	Vector_ll texture_size = canvas_texture->get_size();

	size_t width = texture_size.get_x() <= get_width() ? texture_size.get_x() : get_width();
	size_t height = texture_size.get_y() <= (get_height() - DEFAULT_BUTTON_HEIGHT) ? texture_size.get_y() : (get_height() - DEFAULT_BUTTON_HEIGHT);

	canvas_texture->set_size(Vector_ll(width, height));

	Full_texture *texture = Application::get_app()->get_rescrs()->create_texture(CANVAS_BCKGRND, get_width(), get_height() - DEFAULT_BUTTON_HEIGHT - INCREASED_BUTTON_HEIGHT);
	Canvas_manager *canvas = new Canvas_manager({ this, (size_t)Vidget_type::CANVAS_MANAGER, get_position() + Vector_ll(0, DEFAULT_BUTTON_HEIGHT), texture, TRANSPARENT, get_width(), get_height() - DEFAULT_BUTTON_HEIGHT }, canvases_amount, canvas_texture);

	active_canvas = canvas;

	add_visual_object(canvas);
	canvases_amount++;

	set_active(canvas);
}

void Canvas_manager_manager::tick(const double delta)
{
	size_t objects_amount = get_objects()->get_length();

	size_t offset_coefficient = 0;

	for (size_t i = 0; i < objects_amount; ++i)
	{
		Visual_object **objects_array = get_objects()->get_array();
		if (!objects_array[i]->get_alive())
		{
			if (objects_array[i]->get_type() != (size_t)Vidget_type::CANVAS_MANAGER)
				continue;

			printf("%p\n", objects_array[i]);
			
			offset_coefficient++;

			bool next_active_found = false;
			bool first_canvas_manager_found = false;
			Visual_object *first = nullptr;
			Visual_object *after = nullptr;
			for (size_t j = 0; j < objects_amount; ++j)
			{
				if (i == j || objects_array[j]->get_type() != (size_t)Vidget_type::CANVAS_MANAGER)
					continue;

				if (!first_canvas_manager_found)
				{
					first = objects_array[j];
					first_canvas_manager_found = true;
				}

				if (((Canvas_manager*)objects_array[j])->get_offset().get_x() > ((Canvas_manager*)objects_array[i])->get_offset().get_x())
				{
					((Canvas_manager*)objects_array[j])->set_offset(((Canvas_manager*)objects_array[j])->get_offset() - Vector_ll(DEFAULT_TAB_WIDTH, 0.0));
				}

				if (j > i && !after)
				{
					after = objects_array[j];
				}
			}

			slow_delete_visual_object(i);
			i--;
			objects_amount--;
			canvases_amount--;

			if (after)
			{
				set_active(after);
				active_canvas = (Canvas_manager*)after;
			}
			else if (first)
			{
				set_active(first);
				active_canvas = (Canvas_manager*)first;
			}
			else
				active_canvas = nullptr;

			continue;
		}

		objects_array[i]->tick(delta);
	}
}

bool Canvas_manager_manager::on_mouse_click(const bool state, const size_t par_x, const size_t par_y) // const Mouse_event par_event, 
{
	if (point_inside(par_x, par_y))
	{
		size_t objects_amount = get_objects()->get_length();
		
		for (long long i = (long long)objects_amount - 1; i >= 0; --i)
		{
			if ((get_objects()->get_array()[i])->on_mouse_click(state, par_x, par_y) && (get_objects()->get_array()[i])->get_type() == (size_t)Vidget_type::CANVAS_MANAGER)
			{
				set_active(get_objects()->get_array()[i]);
				active_canvas = (Canvas_manager*)get_active();
				
				return true;
			}

			set_active_state(false);
		}
	}

	return false;
}

bool Canvas_manager_manager::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	if (get_reactive() && (point_inside(from.get_x(), from.get_y()) || point_inside(to.get_x(), to.get_y())))
	{
		// set_active_state(true);
		size_t objects_amount = get_objects()->get_length();
		
		for (long long i = (long long)objects_amount - 1; i >= 0; --i)
		{
			if ((get_objects()->get_array()[i])->on_mouse_move(from, to) && (get_objects()->get_array()[i])->get_type() == (size_t)Vidget_type::CANVAS_MANAGER)
			{
				set_active(get_objects()->get_array()[i]);
				active_canvas = (Canvas_manager*)get_active();
				
				return true;
			}
		}
	}

	return false;
}

void Canvas_manager_manager::draw(Screen_information *screen)
{
	// assert(screen);

	Visual_object::draw(screen);

	if (get_reactive())
	{
		Visual_object **objects_array = get_objects()->get_array();
		size_t objects_amount = get_objects()->get_length();

		for (size_t i = 0; i < objects_amount - 1; ++i)
		{
			if (objects_array[i]->get_visible())
			{
				objects_array[i]->set_active_state(false);
				objects_array[i]->draw(screen);
			}
		}

		objects_array[objects_amount - 1]->set_active_state(true);
		objects_array[objects_amount - 1]->draw(screen);
	}
}

Canvas *Canvas_manager_manager::get_active_canvas() 
{ 
	if (active_canvas)
		return active_canvas->get_canvas(); 
	else
		return nullptr;
}
