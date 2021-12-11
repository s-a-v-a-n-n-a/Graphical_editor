#include "Canvas_effects_manager.hpp"

Effect_manager::Effect_manager()
: effects_amount(0) {}

void Effect_manager::add_effect(Effect<Canvas> *effect)
{
	effects.push_back(effect);
	effects_amount++;
}

void Effect_manager::delete_effect(Effect<Canvas> *effect)
{
	for (size_t i = 0; i < effects_amount; ++i)
	{
		if (effects[i] == effect)
		{
			for (size_t j = i + 1; j < effects_amount; ++j)
				effects[j - 1] = effects[j];

			delete effect;

			effects_amount--;
			break;
		}
	}
}
