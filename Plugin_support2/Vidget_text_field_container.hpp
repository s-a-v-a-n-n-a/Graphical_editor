#ifndef VIDGET_TEXT_FIELD_CONTAINER_HPP
#define VIDGET_TEXT_FIELD_CONTAINER_HPP

#include "plugin_std_2.hpp"
#include "../GUI/Input_string.hpp"

class Vidget_text_field_container : public Input_string
{
private:
	PUPPY::TextField *ward;

public:
	Vidget_text_field_container(const Visual_object::Config &par_base, PUPPY::TextField *par_ward)
	: Input_string(par_base), ward(par_ward) {}
	~Vidget_text_field_container() {}

	bool on_mouse_click(const bool state, const size_t par_x, const size_t par_y) override
	{
		bool result = Input_string::on_mouse_click(state, par_x, par_y);

		auto vidget_handler = ward->get_handler();
		if (result && vidget_handler)
		{
			vidget_handler(std::string_view{ get_message() });
		}

		return result;
	}
	
	bool on_text_entered(const char symbol) override
	{
		bool result = Input_string::on_text_entered(symbol);

		auto vidget_handler = ward->get_handler();
		if (result && vidget_handler)
		{
			vidget_handler(std::string_view{ get_message() });
		}

		return result;
	}

	PUPPY::TextField *get_ward() { return ward; }
};

#endif // VIDGET_TEXT_FIELD_CONTAINER_HPP
