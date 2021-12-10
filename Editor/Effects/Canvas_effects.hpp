#ifndef CANVAS_EFFECTS_H
#define CANVAS_EFFECTS_H

#include "../../Utilities/Effect.hpp"
#include "../Canvas.hpp"

#include "../../sfml_drawing/colors.hpp"

class Red_effect : public Effect<Canvas>
{
protected:
	int red_effect[MAX_COLOR_VALUE + 1];

public:
	Red_effect(Canvas *par_to_effect)
	: Effect(par_to_effect)
	{ 
		for (size_t i = 0; i <= MAX_COLOR_VALUE; ++i)
		{
			red_effect[i] = -1;
		}
	}

	~Red_effect();

	void set_red(const unsigned char from, const unsigned char to)
	{
		size_t canvas_width = to_effect->get_width();
		size_t canvas_height = to_effect->get_height();
		size_t canvas_capacity = canvas_height * canvas_width;

		red_effect[from] = to;
		
		// apply();
		to_effect->set_applied(false);
	}

	void apply() override
	{
		size_t canvas_width = to_effect->get_width();
		size_t canvas_height = to_effect->get_height();
		size_t canvas_capacity = canvas_height * canvas_width;Color *drawing = new Color[canvas_capacity];
		
		for (size_t i = 0; i < canvas_capacity; ++i)
		{
			drawing[i] = to_effect->get_drawing()[i];
			for (size_t j = 0; j <= MAX_COLOR_VALUE; ++j)
			{
				if (red_effect[j] < 0)
					continue;

				if (to_effect->get_drawing()[i].get_r() == j)
				{
					drawing[i].set_r(red_effect[j]);
				}
			}
		}

		to_effect->get_texture()->set_texture(drawing, canvas_width, canvas_height);

		delete [] drawing;
	}
};

class Green_effect : public Effect<Canvas>
{
protected:
	int green_effect[MAX_COLOR_VALUE + 1];

public:
	Green_effect(Canvas *par_to_effect)
	: Effect(par_to_effect)
	{ 
		for (size_t i = 0; i <= MAX_COLOR_VALUE; ++i)
		{
			green_effect[i] = -1;
		}
	}

	~Green_effect();

	void set_green(const unsigned char from, const unsigned char to)
	{
		size_t canvas_width = to_effect->get_width();
		size_t canvas_height = to_effect->get_height();
		size_t canvas_capacity = canvas_height * canvas_width;

		green_effect[from] = to;
		
		// apply();
		to_effect->set_applied(false);
	}

	void apply() override
	{
		size_t canvas_width = to_effect->get_width();
		size_t canvas_height = to_effect->get_height();
		size_t canvas_capacity = canvas_height * canvas_width;Color *drawing = new Color[canvas_capacity];
		
		for (size_t i = 0; i < canvas_capacity; ++i)
		{
			drawing[i] = to_effect->get_drawing()[i];
			for (size_t j = 0; j <= MAX_COLOR_VALUE; ++j)
			{
				if (green_effect[j] < 0)
					continue;

				if (to_effect->get_drawing()[i].get_g() == j)
				{
					drawing[i].set_g(green_effect[j]);
				}
			}
		}

		to_effect->get_texture()->set_texture(drawing, canvas_width, canvas_height);

		delete [] drawing;
	}
};

class Blue_effect : public Effect<Canvas>
{
protected:
	int blue_effect[MAX_COLOR_VALUE + 1];

public:
	Blue_effect(Canvas *par_to_effect)
	: Effect(par_to_effect)
	{ 
		for (size_t i = 0; i <= MAX_COLOR_VALUE; ++i)
		{
			blue_effect[i] = -1;
		}
	}

	~Blue_effect();

	void set_blue(const unsigned char from, const unsigned char to)
	{
		size_t canvas_width = to_effect->get_width();
		size_t canvas_height = to_effect->get_height();
		size_t canvas_capacity = canvas_height * canvas_width;

		blue_effect[from] = to;	

		// apply();
		to_effect->set_applied(false);
	}

	void apply() override
	{
		size_t canvas_width = to_effect->get_width();
		size_t canvas_height = to_effect->get_height();
		size_t canvas_capacity = canvas_height * canvas_width;Color *drawing = new Color[canvas_capacity];
		
		for (size_t i = 0; i < canvas_capacity; ++i)
		{
			drawing[i] = to_effect->get_drawing()[i];
			for (size_t j = 0; j <= MAX_COLOR_VALUE; ++j)
			{
				if (blue_effect[j] < 0)
					continue;

				if (to_effect->get_drawing()[i].get_b() == j)
				{
					drawing[i].set_b(blue_effect[j]);
				}
			}
		}

		to_effect->get_texture()->set_texture(drawing, canvas_width, canvas_height);

		delete [] drawing;
	}
};

#endif // CANVAS_EFFECTS_H

