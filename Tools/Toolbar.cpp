#include "Toolbar.hpp"
#include "Pencil.hpp"
#include "Eraser.hpp"
#include "Pipette.hpp"

// Toolbar *Toolbar::toolbar = nullptr;
// Toolbar_destroyer Toolbar::destroyer;

Toolbar::Toolbar()
: tools(), active_tool(nullptr), current_color(DEFAULT_TOOL_COLOR) 
{
	Pencil *pencil = new Pencil();
	add_tool(pencil);

	Eraser *eraser = new Eraser();
	add_tool(eraser);

	Pipette *pipette = new Pipette();
	add_tool(pipette);

	tools_amount = tools.size();
	set_active_tool(pencil);

	set_color(current_color);
}

Toolbar::~Toolbar()
{
	for (size_t i = 0; i < tools_amount; ++i)
	{
		delete tools[i];
	}
}

// Toolbar *Application::get_app()->get_tools()
// {
// 	if (toolbar == nullptr)
// 	{
// 		toolbar = new Toolbar();
// 		destroyer.initialize(toolbar);
// 	}

// 	return toolbar;
// }

void Toolbar::add_tool(Tool *tool)
{
	tools.push_back(tool);
	tools_amount = tools.size();
}

void Toolbar::set_active_tool(Tool *tool)
{
	active_tool = tool;
}

Tool *Toolbar::get_active_tool()
{
	return active_tool;
}

const std::vector<Tool*> &Toolbar::get_tools()
{
	return tools;	
}

void Toolbar::set_color(const Color &color)
{
	current_color = color;

	for (size_t i = 0; i < tools_amount; ++i)
	{
		tools[i]->set_color(color);
	}
}

Color Toolbar::get_color()
{
	if (current_color != active_tool->get_color())
		set_color(active_tool->get_color());
	return current_color;
}

size_t Toolbar::get_tools_amount() const
{
	return tools_amount;
}



// Toolbar_destroyer::~Toolbar_destroyer() 
// { 
// 	delete toolbar; 
// }

// void Toolbar_destroyer::initialize(Toolbar *par_toolbar) 
// { 
// 	toolbar = par_toolbar; 
// }
