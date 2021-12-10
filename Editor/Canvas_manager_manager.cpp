#include "Canvas_manager_manager.hpp"

Canvas_manager_manager::Canvas_manager_manager(const Visual_object::Config &par_base)
: Visual_object(par_base), active_canvas(nullptr)
{
	// создаёт Window_control_panel
    // ------------------------------------------------------------------------------
	Window_control_panel *control = create_control_panel(this, get_position(), get_width(), DEFAULT_BUTTON_HEIGHT);

	Button_manager *panel = new Button_manager({ (size_t)Vidget_type::BUTTON_MANAGER, get_position() + Vector_ll(0, DEFAULT_BUTTON_HEIGHT), nullptr, MEDIUM_GREY, get_width(), INCREASED_BUTTON_HEIGHT });
	
	// Button_manager *panel = new Button_manager((size_t)Vidget_type::BUTTON_MANAGER, par_position + Vector_ll(0, DEFAULT_BUTTON_HEIGHT), MEDIUM_GREY, par_width, INCREASED_BUTTON_HEIGHT);

	// создаёт начальный объект
	// ------------------------------------------------------------------------------
	Canvas_manager *canvas = new Canvas_manager({ (size_t)Vidget_type::CANVAS_MANAGER, get_position() + Vector_ll(0.0, DEFAULT_BUTTON_HEIGHT), nullptr, WHITE, get_width(), get_height() - DEFAULT_BUTTON_HEIGHT }, 0);

	active_canvas = canvas;

	// add_visual_object(control);
	add_visual_object(panel);
	add_visual_object(canvas);
}

Window_control_panel *Canvas_manager_manager::create_control_panel(Visual_object *parent, const Vector_ll &position, const size_t width, const size_t height)
{
	Full_texture *texture = Resources::get_instance()->create_texture(WINDOW_HEADER, width, height);

	Visual_object::Config panel_base = { (size_t)Vidget_type::WINDOW_CONTROL_PANEL, position, texture, TRANSPARENT, width, height };
	Window_control_panel *control = new Window_control_panel(panel_base, parent);
	add_visual_object(control);

	return control;
}

void Canvas_manager_manager::add_canvas()
{
	if ((get_objects()->get_length() - 1) * DEFAULT_TAB_WIDTH >= get_width())
	{
		printf("Unable to create new canvas\n");
		return;
	}

	Visual_object::Config canvas_base = { (size_t)Vidget_type::CANVAS_MANAGER, get_position() + Vector_ll(0.0, DEFAULT_BUTTON_HEIGHT), nullptr, WHITE, get_width(), get_height() - DEFAULT_BUTTON_HEIGHT };
	Canvas_manager *canvas = new Canvas_manager(canvas_base, get_objects()->get_length() - 2);

	active_canvas = canvas;

	add_visual_object(canvas);

	set_active(canvas);
}

void Canvas_manager_manager::tick(Screen_information *screen, const double delta_time)
{
	assert(screen);

	Visual_object **objects_array = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	size_t offset_coefficient = 0;

	for (size_t i = 0; i < objects_amount; ++i)
	{
		if (!objects_array[i]->get_alive())
		{
			if (objects_array[i]->get_type() != (size_t)Vidget_type::CANVAS_MANAGER)
				continue;

			offset_coefficient++;

			for (size_t j = 0; j < objects_amount; ++j)
			{
				if (i == j || objects_array[j]->get_type() != (size_t)Vidget_type::CANVAS_MANAGER)
					continue;

				if (((Canvas_manager*)objects_array[j])->get_offset().get_x() > ((Canvas_manager*)objects_array[i])->get_offset().get_x())
				{
					((Canvas_manager*)objects_array[j])->set_offset(((Canvas_manager*)objects_array[j])->get_offset() - Vector_ll(DEFAULT_TAB_WIDTH, 0.0));

				}
			}

			slow_delete_visual_object(i);
			i--;
			objects_amount--;

			continue;
		}
		// else if (objects_array[i]->get_type() == (size_t)Vidget_type::CANVAS_MANAGER && offset_coefficient)
		// {
		// 	((Canvas_manager*)objects_array[i])->set_offset(((Canvas_manager*)objects_array[i])->get_offset() - Vector_ll(DEFAULT_TAB_WIDTH, 0.0) * offset_coefficient);
		// }

		objects_array[i]->tick(screen, delta_time);
	}
}

bool Canvas_manager_manager::on_mouse_click(const bool state, const size_t par_x, const size_t par_y) // const Mouse_event par_event, 
{
	if (point_inside(par_x, par_y))
	{
		size_t objects_amount = get_objects()->get_length();
		
		for (long long i = (long long)objects_amount - 1; i >= 0; --i)
		{
			if ((get_objects()->get_array()[i])->on_mouse_click(state, par_x, par_y) && (get_objects()->get_array()[i])->get_type() == (size_t)Vidget_type::CANVAS_MANAGER)//(((get_objects()->get_array()[i])->get_reactive() || state == Mouse_state::MOVED) && (get_objects()->get_array()[i])->on_mouse(state, par_x, par_y)) // ??????
			{
				set_active(get_objects()->get_array()[i]);
				(get_objects()->get_array()[i])->set_active_state(true);
				
				// slow_delete
				get_objects()->extract(i);
				// push
				add_visual_object(get_active());
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
			if ((get_objects()->get_array()[i])->on_mouse_move(from, to) && (get_objects()->get_array()[i])->get_type() == (size_t)Vidget_type::CANVAS_MANAGER)//(((get_objects()->get_array()[i])->get_reactive() || state == Mouse_state::MOVED) && (get_objects()->get_array()[i])->on_mouse(state, par_x, par_y)) // ??????
			{
				set_active(get_objects()->get_array()[i]);
				(get_objects()->get_array()[i])->set_active_state(true);
				
				// slow_delete
				get_objects()->extract(i);
				// push
				add_visual_object(get_active());
				active_canvas = (Canvas_manager*)get_active();
				
				return true;
			}
		}
	}

	return false;
}

void Canvas_manager_manager::draw(Screen_information *screen)
{
	assert(screen);

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
	return active_canvas->get_canvas(); 
}
