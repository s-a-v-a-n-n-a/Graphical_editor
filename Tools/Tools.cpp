#include "Tools.hpp"

Tool::Tool()
: pressed(false), data_params(0, 0), data(nullptr), name(nullptr)
{
	color = DEFAULT_TOOL_COLOR;
	size = DEFAULT_TOOL_SIZE;
}

Tool::Tool(const char *par_name)
: pressed(false), data_params(0, 0), data(nullptr), name(nullptr)
{
	size_t name_size = strlen(par_name);

	name = new char[name_size + 1];
	strncpy(name, par_name, name_size);
	name[name_size] = 0;
}

Tool::~Tool()
{
	if (name)
	{
		delete [] name;
	}
}

void Tool::on_mouse_move(const Vector_ll &from, const Vector_ll &to)
{
	if (pressed)
	{
		apply(data, data_params, to);
	}
}

void Tool::on_mouse_press(Color *to_apply, const Vector_ll &parameters, const Vector_ll &position)
{
	// if (position.get_x() < 0 || position.get_y() < 0 || position.get_x() >= parameters.get_x() || position.get_y() >= parameters.get_y())
	// 	return; 
	// data = new Color[parameters.get_x() * parameters.get_y()];
	// for (size_t i = 0; i < parameters.get_x() * parameters.get_y(); ++i)
	// 	data[i] = to_apply[i];

	set_data(to_apply, parameters);

	if (!pressed)
	{ 
		apply(data, data_params, position);
		pressed = true;
	}
}

void Tool::on_mouse_release(const Vector_ll &position)
{
	// if (position.get_x() < 0 || position.get_y() < 0 || position.get_x() >= data_params.get_x() || position.get_y() >= data_params.get_y())
	// 	return; 

	pressed = false;
	// if (pressed)
	// 	apply(data, data_params, position);
	// printf("Tool released!!!!!!!!!!!\n");
 
	release_data();
}

void Tool::set_data(Color *to_apply, const Vector_ll &parameters)
{
	data = to_apply;
	data_params = parameters;
}

void Tool::release_data()
{
	// delete [] data;
}

