#ifndef CANVAS_MANAGER_SINGLE
#define CANVAS_MANAGER_SINGLE

#include "../GUI/Visual_object_base.hpp"
#include "../GUI/Resource_manager.hpp"
#include "../sfml_drawing/Animating_texture.hpp"

#include "Window_control_panel.hpp"
#include "Canvas.hpp"
#include "Tab.hpp"

class Canvas_manager : public Visual_object
{
private:
	Tab *tab;
	Canvas *canvas;

public:
	// поэтому получает информацию о главном
	Canvas_manager(const Visual_object::Config &par_base, const size_t predecessors_amount);
	~Canvas_manager();

	void draw(Screen_information *screen) override;

	void set_offset(const Vector_ll &par_offset);
	Vector_ll get_offset() const;

	Canvas *get_canvas() { return canvas; }
};

#endif // CANVAS_MANAGER_SINGLE
