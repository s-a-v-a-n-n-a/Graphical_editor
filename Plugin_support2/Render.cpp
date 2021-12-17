#include "Render.hpp"
#include "../Editor/Application.hpp"

Blend_mode app_translate_mode(BlendMode mode)
{
	switch(mode)
	{
	case BlendMode::COPY:
		return Blend_mode::COPY;
	case BlendMode::ALPHA_BLEND:
		return Blend_mode::ALPHA;
	default:
		return Blend_mode::ALPHA;
	}
}

Vector_ll app_translate_vector(Vec2f vec)
{
	return Vector_ll((long long)vec.x, (long long)vec.y);
}

Color app_translate_color(RGBA color)
{
	return { color.r, color.g, color.b, color.a };
}

Render::~Render() {}

void Render::get_active_target()
{
	target = ((Graphical_editor_main_page*)Application::get_app()->get_default())->get_active_canvas()->get_drawing();
	texture = ((Graphical_editor_main_page*)Application::get_app()->get_default())->get_active_canvas()->get_texture()->get_current_texture();
	// inn_texture = ((Graphical_editor_main_page*)Application::get_app()->get_default())->get_active_canvas()->get_texture()->get_texture();
	size.set_x(((Graphical_editor_main_page*)Application::get_app()->get_default())->get_active_canvas()->get_width());
	size.set_y(((Graphical_editor_main_page*)Application::get_app()->get_default())->get_active_canvas()->get_height());
}

Render::Render *get_copy();

Vec2s Render::get_size()
{
	return Vec2s(size.get_x(), size.get_y());
}

RGBA Render::get_pixel(size_t x, size_t y)
{
	Color *texture_data = texture2data(texture, size.get_x(), size.get_y());

	return texture_data[y * size.get_y() + x];
}

void Render::set_pixel(size_t x, size_t y, const RGBA &color)
{
	get_active_target();

	Renderer::Object obj = { texture, {0, 0}, app_translate_mode(render_mode.blend) };
	Renderer *renderer = Application::get_app()->get_renderer();
	renderer->push_back(&obj);

	renderer->draw_point(Vector_ll(x, y), app_translate_color(color));
	target[y * size.get_y() + x] = app_translate_color(color);

	renderer->pop_back();
}

RGBA *Render::get_pixels() const
{
	return (RGBA*)target;
}

void Render::clear(const RGBA &color)
{
	Renderer::Object obj = { texture, {0, 0}, app_translate_mode(render_mode.blend) };
	Renderer *renderer = Application::get_app()->get_renderer();

	renderer->clear_texture(texture, app_translate_color(color));
}

// render
void Render::render_circle(const Vec2f &position, float radius, const RGBA &color, const RenderMode &render_mode)
{
	get_active_target();

	Renderer::Object obj = { texture, {0, 0}, app_translate_mode(render_mode.blend) };
	Renderer *renderer = Application::get_app()->get_renderer();
	renderer->push_back(&obj);
	
	Color app_color = app_translate_color(color);
	renderer->draw_circle(app_translate_vector(position), radius, app_color, app_color);
	
	renderer->pop_back();
}

void Render::render_line(const Vec2f &start, const Vec2f &end, const RGBA &color, const RenderMode &render_mode)
{
	get_active_target();

	Renderer::Object obj = { texture, {0, 0}, app_translate_mode(render_mode.blend) };
	Renderer *renderer = Application::get_app()->get_renderer();
	renderer->push_back(&obj);
	renderer->draw_circle(app_translate_vector(start), app_translate_vector(end), app_translate_color(color));
	renderer->pop_back();
}

void Render::render_triangle(const Vec2f &p1, const Vec2f &p2, const Vec2f &p3, const RGBA &color, const RenderMode &render_mode)
{
	get_active_target();

	Renderer::Object obj = { texture, {0, 0}, app_translate_mode(render_mode.blend) };
	Renderer *renderer = Application::get_app()->get_renderer();
	renderer->push_back(&obj);
	renderer->draw_circle(app_translate_vector(p1), app_translate_vector(p2), app_translate_vector(p3), app_translate_color(color));
	renderer->pop_back();
}

void Render::render_rectangle(const Vec2f &p1, const Vec2f &p2, const RGBA &color, const RenderMode &render_mode)
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

	renderer->draw_circle(start, width, height, app_color, app_color);
	renderer->pop_back();
}

void Render::render_texture(const Vec2f &position, const RenderTarget *texture, const RenderMode &render_mode)
{
	get_active_target();
	
	Vector_ll app_position = app_translate_vector(position);
	Target_texture *app_texture = (Render*)texture->texture;

	Renderer::Object obj = { texture, {0, 0}, app_translate_mode(render_mode.blend) };
	Renderer *renderer = Application::get_app()->get_renderer();
	renderer->push_back(&obj);

	Vec2s size = texture->get_size();
	renderer->draw_texture(app_position, app_texture, size.x, size.y);
	
	renderer->pop_back();
}

void Render::render_pixels(const Vec2f &position, const Vec2s &size, const RGBA *data, const RenderMode &render_mode)
{
	get_active_target();
	
	Renderer::Object obj = { texture, {0, 0}, app_translate_mode(render_mode.blend) };
	Renderer *renderer = Application::get_app()->get_renderer();
	renderer->push_back(&obj);

	Vec2s size = texture->get_size();
	renderer->draw_image((Color*)data, app_translate_vector(position), size.x, size.y);
	
	renderer->pop_back();
}

void Render::apply_shader(const Shader *shader) {}
