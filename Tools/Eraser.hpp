#ifndef ERASER_H
#define ERASER_H

#include "Tools.hpp"

class Eraser : public Tool 
{
public:
	Eraser()
	: Tool() 
	{ 
		Tool::set_color(TRANSPARENT); 
	}
	~Eraser() = default;
	
	void apply(Color *to_apply, const Vector_ll &parameters, const Vector_ll &position) override
	{
		size_t eraser_size = get_size() / 2;
		Color eraser_color = get_color();

		// size_t width = to_apply->get_width();
		// size_t height = to_apply->get_height();
		size_t width = parameters.get_x();
		size_t height = parameters.get_y();

		// size_t position_x = to_apply->get_position().get_x();
		// size_t position_y = to_apply->get_position().get_y();

		size_t par_x = position.get_x();
		size_t par_y = position.get_y();

		size_t begin_x = par_x > eraser_size ? par_x - eraser_size : par_x;
		size_t begin_y = par_y > eraser_size ? par_y - eraser_size : par_y;

		size_t end_x = par_x + eraser_size < width ? par_x + eraser_size : par_x;
		size_t end_y = par_y + eraser_size < height ? par_y + eraser_size : par_y;

		for (size_t i = begin_y; i < end_y; ++i)
			for (size_t j = begin_x; j < end_x; ++j)
			{
				size_t index = i * width + j;

				to_apply[index] = eraser_color;
			}
	}

	void set_color(const Color &par_color) override { ; }
};

#endif // ERASER_H
