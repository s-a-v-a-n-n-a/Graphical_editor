#include "Menu.hpp"

#include "Application.hpp"
#include "Editor_delegates.hpp"

Menu::Menu(const Visual_object::Config &par_base)
: Visual_object(par_base), buttons(nullptr)
{
	buttons = new Button_manager(par_base, false);
	add_visual_object(buttons);

	set_reactive(false);
	set_visible(false);
}

Menu::~Menu()
{
	delete buttons;
}

Button *Menu::add_button(Button_delegate *par_delegate, const char *par_text)
{
	Animating_texture *texture = Application::get_app()->get_rescrs()->create_texture(SIMPLE_BUTTON, get_width(), DEFAULT_BUTTON_HEIGHT, SIMPLE_BUTTON_MOVE, nullptr);
	Button *button = buttons->add_button(par_delegate, par_text, texture, TRANSPARENT, 0, 0, false);

	return button;
}

bool Menu::on_mouse_click(const bool state, const size_t par_x, const size_t par_y)
{
	return Visual_object::on_mouse_click(state, par_x, par_y);
}

bool Menu::on_mouse_move(const Vector_ll from, const Vector_ll to)
{
	Visual_object::on_mouse_move(from, to);
	// if (point_inside(from.get_x(), from.get_y()) && !point_inside(to.get_x(), to.get_y()))
	// {
	// 	set_visible(false);
	// 	set_reactive(false);
	// }

	return true;
}

void Menu::tick(const double delta)
{
	Visual_object::tick(delta);

	size_t current_effects_amount = Application::get_app()->get_effects()->get_effects_amount();
	size_t buttons_amount = buttons->get_objects()->get_length();
	
	// printf("%lu\n", current_effects_amount);

	Graphical_editor_main_page *editor = (Graphical_editor_main_page*)Application::get_app()->get_default();
	if (current_effects_amount != (buttons_amount))
	{
		for (size_t i = buttons_amount; i < current_effects_amount; ++i)
		{
			Effect<Canvas> *add = Application::get_app()->get_effects()->get_effects()[i];
	
			assert(editor->get_active_canvas());
			
			char *name = nullptr;
			if (add->get_name())
				name = add->get_name();
			
			Button *to_add = nullptr;
			if (!name)
				to_add = add_button(nullptr, "Effect");
			else
				to_add = add_button(nullptr, name);

			Animating_effect_applier *delegate = new Animating_effect_applier(editor->get_active_canvas(), add, to_add);
			to_add->set_delegate(delegate);
		}
	}

	// printf("uuuu\n");
}

