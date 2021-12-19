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

Render::Render()
: PUPPY::RenderTarget()
{
	;
}

void Render::get_active_target()
{
	target = ((Graphical_editor_main_page*)Application::get_app()->get_default())->get_active_canvas()->get_drawing();
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
	copy->target = target;
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
	get_active_target();

	Renderer::Object obj = { texture, {0, 0}, Blend_mode::ALPHA };
	Renderer *renderer = Application::get_app()->get_renderer();
	renderer->push_back(&obj);

	renderer->draw_point(Vector_ll(x, y), app_translate_color(color));
	target[y * size.get_y() + x] = app_translate_color(color);

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
	get_active_target();

	Renderer::Object obj = { texture, {0, 0}, app_translate_mode(render_mode.blend) };
	Renderer *renderer = Application::get_app()->get_renderer();
	renderer->push_back(&obj);
	
	Color app_color = app_translate_color(color);
	renderer->draw_circle(app_translate_vector(position), radius, app_color, app_color);
	
	renderer->pop_back();
}

void Render::render_line(const PUPPY::Vec2f &start, const PUPPY::Vec2f &end, const PUPPY::RGBA &color, const PUPPY::RenderMode &render_mode)
{
	get_active_target();

	Renderer::Object obj = { texture, {0, 0}, app_translate_mode(render_mode.blend) };
	Renderer *renderer = Application::get_app()->get_renderer();
	renderer->push_back(&obj);
	renderer->draw_line(app_translate_vector(start), app_translate_vector(end), app_translate_color(color));
	renderer->pop_back();
}

void Render::render_triangle(const PUPPY::Vec2f &p1, const PUPPY::Vec2f &p2, const PUPPY::Vec2f &p3, const PUPPY::RGBA &color, const PUPPY::RenderMode &render_mode)
{
	get_active_target();

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
	get_active_target();

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
	get_active_target();
	
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
	get_active_target();
	
	Renderer::Object obj = { texture, {0, 0}, app_translate_mode(render_mode.blend) };
	Renderer *renderer = Application::get_app()->get_renderer();
	renderer->push_back(&obj);

	PUPPY::Vec2s other_size = ((Render*)texture)->get_size();
	renderer->draw_image((Color*)data, app_translate_vector(position), other_size.x, other_size.y);
	
	renderer->pop_back();
}

void Render::apply_shader(const PUPPY::Shader *shader) {}
