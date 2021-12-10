#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <vector>

#include "Pencil.hpp"
#include "Eraser.hpp"

class Toolbar;

class Toolbar_destroyer
{
private:
	Toolbar *toolbar;


public:
	~Toolbar_destroyer();

	void initialize(Toolbar *par_toolbar);
};

class Toolbar
{
private:
	static Toolbar *toolbar;
	static Toolbar_destroyer destroyer;

	// List<Tool*> tools;
	std::vector<Tool*> tools;
	size_t tools_amount;

	Tool *active_tool;

	Color current_color;

protected:
// public:
	Toolbar();
	friend class Toolbar_destroyer;

public:
	~Toolbar();
	static Toolbar *get_instance();

	void add_tool(Tool *tool);

	void set_active_tool(Tool *tool);
	
	Tool *get_active_tool();
	size_t get_tools_amount() const;
	const std::vector<Tool*> &get_tools();

	void set_color(const Color &color);
	Color get_color() const;
};

#endif // TOOLBAR_H
