#ifndef TEST_H
#define TEST_H

#include "../GUI/Button.hpp"

class Test_button : public Button
{
private:

public:
	Test_button (const Visual_object::Config &par_base, Button_delegate *par_click, const char *par_text)
	: Button(par_base, par_click, par_text)
	{
		;
	}
	~Test_button() = default;

	bool point_inside(const size_t par_x, const size_t par_y) override
	{
		bool tmp_result = false;

		Vector_ll center = get_position() + Vector_ll(get_width() / 2, get_height() / 2);

		if ((par_x - center.get_x()) * (par_x - center.get_x()) + (par_y - center.get_y()) * (par_y - center.get_y()) < get_width() * get_height() / 4)
		{
			tmp_result = true;;
		}

		if ((par_x - center.get_x()) * (par_x - center.get_x()) + (par_y - center.get_y()) * (par_y - center.get_y()) < get_width() * get_height() / 16)
		{
			tmp_result = false;
		}
	
		return tmp_result;
	}
};

#endif // TEST_H
