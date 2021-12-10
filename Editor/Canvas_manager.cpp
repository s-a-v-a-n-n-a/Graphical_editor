#include "Canvas_manager.hpp"

Canvas_manager::Canvas_manager(const Visual_object::Config &par_base, const size_t predecessors_amount)
: Visual_object(par_base), tab(nullptr), canvas(nullptr)
{
	// create Canvas
	// ------------------------------------------------------------------------------
	Full_texture *canvas_texture = Resources::get_instance()->create_texture(CAT_TEXTURE, get_width(), (size_t)(get_height() - INCREASED_BUTTON_HEIGHT));
	Visual_object::Config canvas_base = { (size_t)Vidget_type::CANVAS, get_position() + Vector_ll(0.0, INCREASED_BUTTON_HEIGHT), canvas_texture, TRANSPARENT, get_width(), get_height() - INCREASED_BUTTON_HEIGHT };
	canvas = new Canvas(canvas_base); // , par_pencil

	// создаёт кнопку управления
	// ------------------------------------------------------------------------------
	Animating_texture *tab_texture = Resources::get_instance()->create_texture(TAB_TEXTURE, (size_t)280, INCREASED_BUTTON_HEIGHT, nullptr, TAB_INACTIVE_TEXTURE);
	
	Visual_object::Config tab_base = { (size_t)Vidget_type::TAB, get_position() + Vector_ll(predecessors_amount * DEFAULT_TAB_WIDTH, 0.0), tab_texture, TRANSPARENT, (size_t)280, INCREASED_BUTTON_HEIGHT };
	tab = new Tab(tab_base, this);
	tab->set_active_state(true);


	add_visual_object(canvas);
	add_visual_object(tab);
}

Canvas_manager::~Canvas_manager()
{
	Visual_object **objects = get_objects()->get_array();
	size_t objects_amount = get_objects()->get_length();

	for (size_t i = 0; i < objects_amount; ++i)
	{
		delete objects[i];
	}
}

void Canvas_manager::draw(Screen_information *screen)
{
	assert(screen);

	if (get_reactive())
	{
		Visual_object **objects_array = get_objects()->get_array();
		size_t objects_amount = get_objects()->get_length();

		for (size_t i = 0; i < objects_amount; ++i)
		{
			if (objects_array[i]->get_visible())
			{
				objects_array[i]->set_active_state(get_active_state());
				objects_array[i]->draw(screen);
			}
		}
	}
}


void Canvas_manager::set_offset(const Vector_ll &par_offset) 
{ 
	printf("[Canvas manager] : Set offset to tab\n");
	tab->set_position(get_position() + par_offset); 
}

Vector_ll Canvas_manager::get_offset() const 
{ 
	return tab->get_position() - get_position(); 
}
