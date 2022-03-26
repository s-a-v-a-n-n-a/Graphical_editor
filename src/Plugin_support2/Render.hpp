#ifndef RENDER_HPP
#define RENDER_HPP

#include "plugin_std_2.hpp"

#include "../sfml_drawing/Renderer.hpp"
#include "../sfml_drawing/Texture.hpp"

Blend_mode app_translate_mode(PUPPY::BlendMode mode);
Vector_ll app_translate_vector(PUPPY::Vec2f vec);
Color app_translate_color(PUPPY::RGBA color);

PUPPY::RGBA app_translate_color_back(Color color);
PUPPY::Vec2f app_translate_vector_back(Vector_ll vec);
PUPPY::Event::MousePress app_translate_mouse_press(const size_t x, const size_t y);
PUPPY::Event::MouseRelease app_translate_mouse_release(const size_t x, const size_t y);
PUPPY::Event::MouseMove app_translate_mouse_move(const Vector_ll &from, const Vector_ll &to);
PUPPY::Event::Render app_translate_draw();
PUPPY::Event::Tick app_translate_tick(const double delta);
PUPPY::Event::Click app_translate_click();
PUPPY::Event::Hide app_translate_hide();
PUPPY::Event::Show app_translate_show();
PUPPY::Event::FractionChanged app_translate_fraction(const double frac);
PUPPY::Event::Scroll app_translate_scroll(const Vector_ll &delta, const Vector_ll &position);
PUPPY::Event::TextEnter app_translate_text_enter(const unsigned char symbol);
PUPPY::Event::Key app_translate_key(const unsigned key_mask);
PUPPY::Event::KeyDown app_translate_key_down(const unsigned key_mask);
PUPPY::Event::KeyUp app_translate_key_up(const unsigned key_mask);

class Render : public PUPPY::RenderTarget
{
private:
    bool preview;

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
