#ifndef VIDGET_CONTAINER_HPP
#define VIDGET_CONTAINER_HPP

// #include "Vidget.hpp"
#include "plugin_std_2.hpp"
#include "../GUI/Visual_object_base.hpp"

class Vidget_container : public Visual_object
{
private:
	PUPPY::Widget *ward;

public:
	Vidget_container(const Visual_object::Config &par_base, PUPPY::Widget *par_ward);
	~Vidget_container() {}

	// virtual void add_visual_object(Visual_object *par_object) override; 
	// virtual void slow_delete_visual_object(size_t index);
	// virtual long long very_slow_delete_visual_object(Visual_object *par_object);
	// virtual long long very_slow_extract_visual_object(Visual_object *par_object);

	virtual void draw(Screen_information *screen) override;

	// virtual bool point_inside (const size_t par_x, const size_t par_y) override;
	virtual bool on_mouse_click  (const bool state, const size_t par_x, const size_t par_y) override; //const Mouse_event par_event,
	virtual bool on_mouse_move	(const Vector_ll from, const Vector_ll to) override;
	virtual bool on_key_pressed(const bool pressed_state, const unsigned key_mask) override; 
	virtual bool on_text_entered(const char symbol) override; 

	virtual void tick(const double delta) override;

	// Visual_object 		   *get_parent()                { return base.parent; }
	// List<Visual_object*>   *get_objects()        		{ return &objects; }
	// Vector_ll  				get_position() 		const 	{ return base.position; }
	// Color         		 	get_color()    		const 	{ return base.color; }
	// size_t         			get_width()    		const 	{ return base.width; }
	// size_t         			get_height()   		const 	{ return base.height; }
	// Visual_object 		   *get_active() 				{ return current_active; }
	// bool					get_active_state() 	const 	{ return active; }
	// bool				    get_visible()  	   	const 	{ return visible; }
	// bool				    get_reactive()  	const 	{ return reactive; }
	// bool				    get_alive()  		const 	{ return alive; }
	// size_t					get_type()			const	{ return base.type; }
	// Texture 			   *get_texture()				{ return base.texture; }

	// virtual void set_parent         (const Visual_object *par_parent)   { base.parent = par_parent; }
	// virtual void set_position 		(const Vector_ll &par_position);
	// virtual void set_color    		(const Color &par_color)            { base.color = par_color; }
	// virtual void set_width    		(const size_t par_width);
	// virtual void set_height   		(const size_t par_height);
	// virtual void set_active_state   (const bool par_active)             { active = par_active; }
	// virtual void set_active  		(Visual_object *par_current_active);
	// virtual void set_visible		(const bool par_visible)			{ visible = par_visible; }
	// virtual void set_reactive		(const bool par_reactive)			{ reactive = par_reactive; }
	// virtual void set_alive			(const bool par_alive)				{ alive = par_alive; }
	// virtual void set_texture 		(Texture *par_texture)				{ base.texture = par_texture; }

	PUPPY::Widget *get_ward() { return ward; }
};

#endif // VIDGET_CONTAINER_HPP
