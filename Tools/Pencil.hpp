#ifndef PENCIL
#define PENCIL

// #include "../sfml_drawing/colors.hpp"
#include "Tools.hpp"

const size_t DEFAULT_PENCIL_SIZE = 20;

class Pencil : public Tool
{
private:

public:
	Pencil()
	: Tool() { ; }

	// Pencil(const Color &par_color, const size_t par_size)
	// {
	// 	color = par_color;
	// 	size = par_size;
	// }

	~Pencil() = default;
	
	void apply(Color *to_apply, const Vector_ll &parameters, const Vector_ll &position) override
	{
		size_t pencil_size = get_size() / 2;
		Color pencil_color = get_color();

		// size_t width = to_apply->get_width();
		// size_t height = to_apply->get_height();
		size_t width = parameters.get_x();
		size_t height = parameters.get_y();

		// size_t position_x = to_apply->get_position().get_x();
		// size_t position_y = to_apply->get_position().get_y();

		size_t par_x = position.get_x();
		size_t par_y = position.get_y();

		size_t begin_x = par_x > pencil_size ? par_x - pencil_size : par_x;
		size_t begin_y = par_y > pencil_size ? par_y - pencil_size : par_y;

		size_t end_x = par_x + pencil_size < width ? par_x + pencil_size : par_x;
		size_t end_y = par_y + pencil_size < height ? par_y + pencil_size : par_y;

		for (size_t i = begin_y; i < end_y; ++i)
			for (size_t j = begin_x; j < end_x; ++j)
			{
				size_t index = i * width + j;

				to_apply[index] = pencil_color;
			}
	}
};

#endif // PENCIL
