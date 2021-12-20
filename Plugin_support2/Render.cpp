#include "Render.hpp"
#include "../Editor/Application.hpp"

Blend_mode app_translate_mode(PUPPY::BlendMode mode)
{
	switch(mode)
	{
	case PUPPY::BlendMode::COPY:
		return Blend_mode::COPY;
	case PUPPY::BlendMode::ALPHA_BLEND:
		return Blend_mode::ALPHA;
	default:
		return Blend_mode::ALPHA;
	}
}

Vector_ll app_translate_vector(PUPPY::Vec2f vec)
{
	return Vector_ll((long long)vec.x, (long long)vec.y);
}

Color app_translate_color(PUPPY::RGBA color)
{
	return { color.r, color.g, color.b, color.a };
}

PUPPY::RGBA app_translate_color_back(Color color)
{
	return { color.r, color.g, color.b, color.a };
} 

PUPPY::Vec2f app_translate_vector_back(Vector_ll vec)
{
	return { (float)vec.get_x(), (float)vec.get_y() };
}

PUPPY::Event::MousePress app_translate_mouse_press(const size_t x, const size_t y)
{
	return { app_translate_vector_back(Vector_ll((long long)x, (long long)y)) };
} 

PUPPY::Event::MouseRelease app_translate_mouse_release(const size_t x, const size_t y)
{
	return { app_translate_vector_back(Vector_ll((long long)x, (long long)y)) };
}

PUPPY::Event::MouseMove app_translate_mouse_move(const Vector_ll &from, const Vector_ll &to)
{
	return { app_translate_vector_back(from), app_translate_vector_back(to) };
}

PUPPY::Event::Render app_translate_draw()
{
	return { false };
}

PUPPY::Event::Tick app_translate_tick(const double delta)
{
	return { delta };
}

PUPPY::Event::Click app_translate_click() { return {}; }

PUPPY::Event::Hide app_translate_hide() { return {}; }

PUPPY::Event::Show app_translate_show() { return {}; }

PUPPY::Event::FractionChanged app_translate_fraction(const double frac) { return { frac }; }

PUPPY::Event::Scroll app_translate_scroll(const Vector_ll &delta, const Vector_ll &position) 
{ 
	return { app_translate_vector_back(delta), app_translate_vector_back(position) }; 
}

PUPPY::Event::TextEnter app_translate_text_enter(const unsigned char symbol)
{
	return { (uint32_t)symbol };
}

PUPPY::Event::Key app_translate_key(const unsigned key_mask)
{
	PUPPY::Keyboard::Key key = (PUPPY::Keyboard::Key)key_mask;
	return  PUPPY::Event::Key(key);
}

PUPPY::Event::KeyDown app_translate_key_down(const unsigned key_mask)
{	
	PUPPY::Keyboard::Key key = (PUPPY::Keyboard::Key)key_mask;
	return { key };
}

PUPPY::Event::KeyUp app_translate_key_up(const unsigned key_mask)
{
	PUPPY::Keyboard::Key key = (PUPPY::Keyboard::Key)key_mask;
	return { key };
}


Render::Render()
: PUPPY::RenderTarget()
{
	get_active_target();
}

void Render::get_active_target()
{
	if (!preview)
		texture = ((Graphical_editor_main_page*)Application::get_app()->get_default())->get_active_canvas()->get_drawable_texture()->get_current_texture();
	else
		texture = ((Graphical_editor_main_page*)Application::get_app()->get_default())->get_active_canvas()->get_preview_texture()->get_current_texture();
	// inn_texture = ((Graphical_editor_main_page*)Application::get_app()->get_default())->get_active_canvas()->get_texture()->get_texture();
	size.set_x(((Graphical_editor_main_page*)Application::get_app()->get_default())->get_active_canvas()->get_width());
	size.set_y(((Graphical_editor_main_page*)Application::get_app()->get_default())->get_active_canvas()->get_height());
}

Render *Render::get_copy() const
{
	Render *copy = new Render();

	copy->preview = preview;
	copy->size = size;
	copy->texture = texture;

	return copy;
}

PUPPY::Vec2s Render::get_size() const
{
	return PUPPY::Vec2s(size.get_x(), size.get_y());
}

PUPPY::RGBA Render::get_pixel(size_t x, size_t y) const
{
	Color *texture_data = Application::get_app()->get_renderer()->texture2data(texture, size.get_x(), size.get_y());

	return app_translate_color_back(texture_data[y * size.get_y() + x]);
}

void Render::set_pixel(size_t x, size_t y, const PUPPY::RGBA &color)
{
	// get_active_target();

	Renderer::Object obj = { texture, {0, 0}, Blend_mode::ALPHA };
	Renderer *renderer = Application::get_app()->get_renderer();
	renderer->push_back(&obj);

	renderer->draw_point(Vector_ll(x, y), app_translate_color(color));
	
	renderer->pop_back();
}

PUPPY::RGBA *Render::get_pixels() const
{
	return (PUPPY::RGBA*)Application::get_app()->get_renderer()->texture2data(texture, size.get_x(), size.get_y());
}

void Render::clear(const PUPPY::RGBA &color)
{
	Renderer::Object obj = { texture, {0, 0}, Blend_mode::ALPHA };
	Renderer *renderer = Application::get_app()->get_renderer();

	renderer->clear_texture(texture, app_translate_color(color));
}

// render
void Render::render_circle(const PUPPY::Vec2f &position, float radius, const PUPPY::RGBA &color, const PUPPY::RenderMode &render_mode)
{
	// get_active_target();

	Renderer::Object obj = { texture, {0, 0}, Blend_mode::ALPHA }; // app_translate_mode(render_mode.blend)
	Renderer *renderer = Application::get_app()->get_renderer();
	renderer->push_back(&obj);
	
	Color app_color = app_translate_color(color);
	renderer->draw_circle(app_translate_vector(position) - Vector_ll(radius, radius), radius, app_color, app_color);
	
	renderer->pop_back();
}

void Render::render_line(const PUPPY::Vec2f &start, const PUPPY::Vec2f &end, const PUPPY::RGBA &color, const PUPPY::RenderMode &render_mode)
{
	// get_active_target();

	Renderer::Object obj = { texture, {0, 0}, app_translate_mode(render_mode.blend) };
	Renderer *renderer = Application::get_app()->get_renderer();
	renderer->push_back(&obj);
	renderer->draw_line(app_translate_vector(start), app_translate_vector(end), app_translate_color(color));
	renderer->pop_back();
}

void Render::render_triangle(const PUPPY::Vec2f &p1, const PUPPY::Vec2f &p2, const PUPPY::Vec2f &p3, const PUPPY::RGBA &color, const PUPPY::RenderMode &render_mode)
{
	// get_active_target();

	Renderer::Object obj = { texture, {0, 0}, app_translate_mode(render_mode.blend) };
	Renderer *renderer = Application::get_app()->get_renderer();
	renderer->push_back(&obj);

	Color app_color = app_translate_color(color);
	renderer->draw_triangle(app_translate_vector(p1), app_translate_vector(p2), app_translate_vector(p3), app_color, app_color);
	renderer->pop_back();

	// Renderer::Object obj = { texture, {0, 0}, app_translate_mode(render_mode.blend) };
	// Renderer *renderer = Application::get_app()->get_renderer();
	// renderer->push_back(&obj);
	// renderer->draw_line(app_translate_vector(p1), app_translate_vector(p2), app_translate_color(color));
	// renderer->pop_back();
}

void Render::render_rectangle(const PUPPY::Vec2f &p1, const PUPPY::Vec2f &p2, const PUPPY::RGBA &color, const PUPPY::RenderMode &render_mode)
{
	// get_active_target();

	Renderer::Object obj = { texture, {0, 0}, app_translate_mode(render_mode.blend) };
	Renderer *renderer = Application::get_app()->get_renderer();
	renderer->push_back(&obj);
	
	Vector_ll start = app_translate_vector(p1);
	Vector_ll end = app_translate_vector(p2);

	double width = (double)(start.get_x() - end.get_x());
	double height = (double)(start.get_y() - end.get_y());

	Color app_color = app_translate_color(color);

	renderer->draw_rectangle(start, width, height, app_color, app_color);
	renderer->pop_back();
}

void Render::render_texture(const PUPPY::Vec2f &position, const PUPPY::RenderTarget *texture, const PUPPY::RenderMode &render_mode)
{
	// get_active_target();
	
	Vector_ll app_position = app_translate_vector(position);
	Target_texture *app_texture = ((Render*)texture)->texture;

	Renderer::Object obj = { app_texture, {0, 0}, app_translate_mode(render_mode.blend) };
	Renderer *renderer = Application::get_app()->get_renderer();
	renderer->push_back(&obj);

	PUPPY::Vec2s other_size = ((Render*)texture)->get_size();
	renderer->draw_texture(app_position, app_texture, other_size.x, other_size.y);
	
	renderer->pop_back();
}

void Render::render_pixels(const PUPPY::Vec2f &position, const PUPPY::Vec2s &size, const PUPPY::RGBA *data, const PUPPY::RenderMode &render_mode)
{
	// get_active_target();
	
	Renderer::Object obj = { texture, {0, 0}, app_translate_mode(render_mode.blend) };
	Renderer *renderer = Application::get_app()->get_renderer();
	renderer->push_back(&obj);

	PUPPY::Vec2s other_size = ((Render*)texture)->get_size();
	renderer->draw_image((Color*)data, app_translate_vector(position), other_size.x, other_size.y);
	
	renderer->pop_back();
}

void Render::apply_shader(const PUPPY::Shader *shader) {}
