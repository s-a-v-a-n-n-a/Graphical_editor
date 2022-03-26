#ifndef VIDGET_HPP
#define VIDGET_HPP

#include "plugin_std_2.hpp"
#include "Vidget_container.hpp"
// #include "../GUI/Visual_object_base.hpp"

class Vidget : virtual public PUPPY::Widget
{
private:
	// Vidget_container *analog;
	Visual_object *analog;

public:
	Vidget(PUPPY::Vec2f position, PUPPY::Vec2f size, PUPPY::Widget *parent = nullptr);
	virtual ~Vidget() override;

    virtual void set_position(const PUPPY::Vec2f &position_) override;
    virtual void set_size(const PUPPY::Vec2f &size_) override;

    virtual PUPPY::WBody get_body() override;
    virtual void set_body(const PUPPY::WBody &body_) override;

    virtual PUPPY::Widget *get_parent() const override;
    virtual void set_parent(PUPPY::Widget *parent_) override;

    virtual PUPPY::RenderTarget *get_texture() override;
    virtual void set_texture(PUPPY::RenderTarget *texture_) override;

    virtual bool is_active() override;
    virtual bool is_inside(const PUPPY::Vec2f &pos) override;

    virtual bool add_child(PUPPY::Widget *child) override;

    virtual void set_to_delete() override; // set to true -> app will try to delete it as soon as possible from its side
                                      // after once setting to true you can not use this widget anymore, it can 
                                      // already be deleted
    virtual bool delete_child(PUPPY::Widget *child) override;
    virtual bool delete_from_parent() override;
    
    virtual void on_render          (const PUPPY::Event::Render          &event) override;
    virtual void on_tick            (const PUPPY::Event::Tick            &event) override;
    virtual void on_mouse_press     (const PUPPY::Event::MousePress      &event) override;
    virtual void on_mouse_release   (const PUPPY::Event::MouseRelease    &event) override;
    virtual void on_mouse_move      (const PUPPY::Event::MouseMove       &event) override;
    virtual void on_key_down        (const PUPPY::Event::KeyDown         &event) override;
    virtual void on_key_up          (const PUPPY::Event::KeyUp           &event) override;
    virtual void on_text_enter      (const PUPPY::Event::TextEnter       &event) override;
    virtual void on_scroll          (const PUPPY::Event::Scroll          &event) override;
    virtual void on_hide            (const PUPPY::Event::Hide            &event) override;
    virtual void on_show            (const PUPPY::Event::Show            &event) override;

    virtual void hide()  override;
    virtual void show()  override;
    virtual void focus() override;

    virtual void set_caption(const char *text, size_t font_size, const PUPPY::Vec2f *pos = nullptr) override;
    virtual void set_base_color(const PUPPY::RGBA &color) override;

    // You are obliged to return nullptr from this in your plugins
    virtual void *get_extra_data(void *arg) override;

    Visual_object *get_analog() { return analog; }
    void set_analog(Visual_object *par_analog);
};

#endif // VIDGET_HPP
