#ifndef RENDER_HPP
#define RENDER_HPP

#include "plugin_std_2.hpp"

#include "../sfml_drawing/Renderer.hpp"
#include "../sfml_drawing/Texture.hpp"

Blend_mode app_translate_mode(PUPPY::BlendMode mode);
Vector_ll app_translate_vector(PUPPY::Vec2f vec);
Color app_translate_color(PUPPY::RGBA color);

PUPPY::RGBA app_translate_color_back(Color color);

class Render : public PUPPY::RenderTarget
{
private:
    bool preview;

    Color *target;
    Vector_ll size;
    Target_texture *texture;
    // Shelled_texture *inn_texture;

private:
    void get_active_target();

public:
    Render();
    ~Render() {}

    void set_if_preview(const bool if_preview) { preview = if_preview; }
    bool if_preview() const { return preview; }
    Render *get_copy() const override;

    Target_texture *get_target_texture() { return texture; } // а нужен Full_texture
    const Shelled_texture *get_texture() { return &texture->getTexture(); } // а нужен Full_texture

    PUPPY::Vec2s get_size() const override;

    PUPPY::RGBA get_pixel(size_t x, size_t y) const override;
    void set_pixel(size_t x, size_t y, const PUPPY::RGBA &color) override;

    PUPPY::RGBA *get_pixels() const override;

    void clear(const PUPPY::RGBA &color = 0) override; // fills the target with `color`

// render
    void render_circle(const PUPPY::Vec2f &position, float radius, const PUPPY::RGBA &color, const PUPPY::RenderMode &render_mode = {}) override;
    void render_line(const PUPPY::Vec2f &start, const PUPPY::Vec2f &end, const PUPPY::RGBA &color, const PUPPY::RenderMode &render_mode = {}) override;
    void render_triangle(const PUPPY::Vec2f &p1, const PUPPY::Vec2f &p2, const PUPPY::Vec2f &p3, const PUPPY::RGBA &color, const PUPPY::RenderMode &render_mode = {}) override;
    void render_rectangle(const PUPPY::Vec2f &p1, const PUPPY::Vec2f &p2, const PUPPY::RGBA &color, const PUPPY::RenderMode &render_mode = {}) override;
    
    void render_texture(const PUPPY::Vec2f &position, const PUPPY::RenderTarget *texture, const PUPPY::RenderMode &render_mode = {}) override;
    void render_pixels(const PUPPY::Vec2f &position, const PUPPY::Vec2s &size, const PUPPY::RGBA *data, const PUPPY::RenderMode &render_mode = {}) override;

    void apply_shader(const PUPPY::Shader *shader) override;
};

#endif // RENDER_HPP
