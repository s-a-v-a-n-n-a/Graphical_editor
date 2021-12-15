#include "plugin_std.hpp"

Blend_mode app_translate_mode(BlendMode mode);
Vector_ll app_translate_vector(Vec2f vec);
Color app_translate_color(RGBA color);

class Render : public RenderTarget
{
private:
    Color *target;
    Vector_ll size;
    Target_texture *texture;
    // Shelled_texture *inn_texture;

private:
    void get_active_target();

public:
    ~Render() {}

    Render *get_copy() const override;

    Vec2s get_size() const override;

    RGBA get_pixel(size_t x, size_t y) const override;
    void set_pixel(size_t x, size_t y, const RGBA &color) override;

    RGBA *get_pixels() const override;

    void clear(const RGBA &color = 0) override; // fills the target with `color`

// render
    void render_circle(const Vec2f &position, float radius, const RGBA &color, const RenderMode &render_mode = {}) override;
    void render_line(const Vec2f &start, const Vec2f &end, const RGBA &color, const RenderMode &render_mode = {}) override;
    void render_triangle(const Vec2f &p1, const Vec2f &p2, const Vec2f &p3, const RGBA &color, const RenderMode &render_mode = {}) override;
    void render_rectangle(const Vec2f &p1, const Vec2f &p2, const RGBA &color, const RenderMode &render_mode = {}) override;
    
    void render_texture(const Vec2f &position, const RenderTarget *texture, const RenderMode &render_mode = {}) override;
    void render_pixels(const Vec2f &position, const Vec2s &size, const RGBA *data, const RenderMode &render_mode = {}) override;

    void apply_shader(const Shader *shader) override;
};
