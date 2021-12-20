#include "Vidget.hpp"
#include "Render.hpp"

Vidget::Vidget(PUPPY::Vec2f position, PUPPY::Vec2f size, PUPPY::Widget *parent)
{
	Vector_ll app_position = app_translate_vector(position);
	Vector_ll app_size = app_translate_vector(size);

	Vidget *par_parent = dynamic_cast<Vidget*>(parent);
	Visual_object *visual_parent = nullptr;
	if (par_parent)
		visual_parent = par_parent->get_analog();
	analog = (Visual_object*)(new Vidget_container({ visual_parent, 0, app_position, NULL, TRANSPARENT, (size_t)app_size.get_x(), (size_t)app_size.get_y() }, this));
}

Vidget::~Vidget()
{
	// delete analog;
}

void Vidget::set_position(const PUPPY::Vec2f &position_)
{
	Vector_ll app_position = app_translate_vector(position_);

	analog->set_position(app_position);
}

void Vidget::set_size(const PUPPY::Vec2f &size_)
{
	Vector_ll app_size = app_translate_vector(size_);

	analog->set_width(app_size.get_x());
	analog->set_height(app_size.get_y());
}

PUPPY::WBody Vidget::get_body()
{
	return PUPPY::WBody(app_translate_vector_back(analog->get_position()), { (float)analog->get_width(), (float)analog->get_height() });
}

void Vidget::set_body(const PUPPY::WBody &body_)
{
	set_position(body_.position);
	set_size(body_.size);
}

PUPPY::Widget *Vidget::get_parent() const
{
	// return ((Vidget_container*)analog->get_parent())->get_ward();
	return nullptr;
}

void Vidget::set_parent(PUPPY::Widget *parent_)
{
	Vidget *par_parent = dynamic_cast<Vidget*>(parent_);
	Visual_object *visual_parent = nullptr;
	if (par_parent)
		visual_parent = par_parent->get_analog();
	analog->set_parent(visual_parent);
}

PUPPY::RenderTarget *Vidget::get_texture()
{
	// Render *render = new Render();
	// return render;
	return nullptr;
}

void Vidget::set_texture(PUPPY::RenderTarget *texture_)
{

}

bool Vidget::is_active()
{
	return analog->get_active();
}

bool Vidget::is_inside(const PUPPY::Vec2f &pos)
{
	Vector_ll app_point_position = app_translate_vector(pos);
	return analog->point_inside((size_t)app_point_position.get_x(), (size_t)app_point_position.get_y());
}

bool Vidget::add_child(PUPPY::Widget *child)
{
	if (!child)
		return false;

	Vidget *par_child = dynamic_cast<Vidget*>(child);
	Visual_object *visual_child = nullptr;
	if (par_child)
		visual_child = par_child->get_analog();
	analog->add_visual_object(visual_child);
	return true;
}

void Vidget::set_to_delete()
{
	analog->set_alive(false);
}

bool Vidget::delete_child(PUPPY::Widget *child)
{
	if (!child)
		return false;

	Vidget *par_child = dynamic_cast<Vidget*>(child);
	Visual_object *visual_child = nullptr;
	if (par_child)
		visual_child = par_child->get_analog();
	long long deleted = analog->very_slow_delete_visual_object(visual_child);

	if (deleted == -1)
		return false;

	return true;
}

bool Vidget::delete_from_parent()
{
	if (!analog->get_parent())
		return false;

	long long deleted = analog->get_parent()->very_slow_extract_visual_object(analog);

	if (deleted == -1)
		return false;

	return true;
}

void Vidget::on_render			(const PUPPY::Event::Render 		 &event) {}
void Vidget::on_tick            (const PUPPY::Event::Tick            &event) {}
void Vidget::on_mouse_press     (const PUPPY::Event::MousePress      &event) {}
void Vidget::on_mouse_release   (const PUPPY::Event::MouseRelease    &event) {}
void Vidget::on_mouse_move      (const PUPPY::Event::MouseMove       &event) {}
void Vidget::on_key_down        (const PUPPY::Event::KeyDown         &event) {}
void Vidget::on_key_up          (const PUPPY::Event::KeyUp           &event) {}
void Vidget::on_text_enter      (const PUPPY::Event::TextEnter       &event) {}
void Vidget::on_scroll          (const PUPPY::Event::Scroll          &event) {}
void Vidget::on_hide            (const PUPPY::Event::Hide            &event) {}
void Vidget::on_show            (const PUPPY::Event::Show            &event) {}

void Vidget::hide() {}
void Vidget::show() {}
void Vidget::focus() {}

void Vidget::set_caption(const char *text, size_t font_size, const PUPPY::Vec2f *pos) {}

void Vidget::set_base_color(const PUPPY::RGBA &color)
{
	Color app_color = app_translate_color(color);

	analog->set_color(app_color);
}

void *Vidget::get_extra_data(void *arg)
{
	return nullptr;
}

void Vidget::set_analog(Visual_object *par_analog) 
{ 
	delete analog; 
	analog = par_analog; 
}

