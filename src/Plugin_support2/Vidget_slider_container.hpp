#ifndef VIDGET_SLIDER_CONTAINER_HPP
#define VIDGET_SLIDER_CONTAINER_HPP

#include "plugin_std_2.hpp"
#include "../GUI/Slider.hpp"

class Vidget_slider_container : public Slider
{
private:
	PUPPY::Slider *ward;

	double current_fraction;

public:
	Vidget_slider_container(const Visual_object::Config &par_base, Button_delegate *par_delegate, const long long par_high_limit, const long long par_low_limit, const bool par_horizontal, PUPPY::Slider *par_ward)
	: Slider(par_base, par_delegate, par_high_limit, par_low_limit, par_horizontal), ward(par_ward), current_fraction(0.0) {}
	~Vidget_slider_container() {}

	void tick(const double delta) override
	{
		if (get_horizontal())
		{
			auto vidget_handler = ward->get_handler();
			if (current_fraction != get_slider()->get_x_relation() && vidget_handler)
			{
				vidget_handler(current_fraction);
			}
		}
		else
		{
			auto vidget_handler = ward->get_handler();
			if (current_fraction != get_slider()->get_y_relation() && vidget_handler)
			{
				vidget_handler(current_fraction);
			}
		}
	}

	PUPPY::Slider *get_ward() { return ward; }
};

#endif // VIDGET_SLIDER_CONTAINER_HPP
