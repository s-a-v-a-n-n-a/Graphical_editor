#ifndef MENU_HPP
#define MENU_HPP

#include "../GUI/Button_manager.hpp"

class Menu : public Visual_object
{
private:
	Button_manager *buttons;

public:
	Menu(const Visual_object::Config &par_base);

	~Menu();

	Button *add_button(Button_delegate *par_delegate, const char *par_text);

	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override;
	bool on_mouse_move(const Vector_ll from, const Vector_ll to) override;
	void tick(const double delta) override;
};

#endif // MENU_HPP
