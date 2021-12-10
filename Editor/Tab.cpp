#include "Tab.hpp"

const size_t DEFAULT_TAB_WIDTH = 250;
const size_t DEFAULT_TAB_HEIGHT = 80;

Tab::Tab(const Visual_object::Config &par_base, Visual_object *par_parent)
: Visual_object(par_base), parent(par_parent)
{
    size_t button_height = 80;

    Canvas_keeper *keep = new Canvas_keeper(parent);
    size_t button_width = get_text_length(GHOST_TYPE, " Canvas ", button_height/2);
    Visual_object::Config keeper_base = { (size_t)Vidget_type::BUTTON,
                                            get_position() + Vector_ll(30, 0), // get_position() + Vector_ll(get_objects()->get_length() * 250, 0.0), 
                                            nullptr,
                                            TRANSPARENT, 
                                            button_width, 
                                            get_height() };

    Button *keeper = new Button(keeper_base, keep, " Canvas ");


    Full_texture *texture = new Full_texture(CLOSE_TEXTURE, INCREASED_BUTTON_HEIGHT, INCREASED_BUTTON_HEIGHT);
    Visual_object::Config closing_base = { (size_t)Vidget_type::BUTTON,
                                            get_position() + Vector_ll(get_width(), 0) - Vector_ll(80, 0), // get_position() + Vector_ll(get_objects()->get_length() * 250, 0.0), 
                                            texture,
                                            TRANSPARENT, 
                                            INCREASED_BUTTON_HEIGHT, 
                                            INCREASED_BUTTON_HEIGHT };
    Button *closing = new Button(closing_base, NULL, "");
    Close_delegate *close = new Close_delegate(parent);
    closing->set_delegate(close);

    add_visual_object(keeper);
    add_visual_object(closing);
}

void Tab::draw(Screen_information *screen)
{
    if (get_active_state())
    {
        Animating_texture *texture = (Animating_texture *)get_texture();
        texture->set_current_texture(texture->get_default_texture());
    }
    else
    {
        Animating_texture *texture = (Animating_texture *)get_texture();
        texture->set_current_texture(texture->get_inactive_texture());
    }

    Visual_object::draw(screen);
}
