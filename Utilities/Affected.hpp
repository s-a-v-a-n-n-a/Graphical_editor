#ifndef AFFECTED_H
#define AFFECTED_H

#include "Effect.hpp"
#include "../simple_list/simple_list.hpp"

template<typename T> class Affected
{
protected:
	friend Effect<T>;
	List<Effect<T>*> effects;

	bool to_apply;
	bool applied;

public:
	Affected()
	: effects(), to_apply(true), applied(true)
	{ ; }

	virtual ~Affected() { ; }

	void set_applying(const bool par_to_apply)
	{
		to_apply = par_to_apply;
	}

	void set_applied(const bool par_applied)
	{
		applied = par_applied;
	}

	void apply()
	{
		if (!to_apply)
			return;

		size_t effects_amount = effects.get_length();
		for (size_t i = 0; i < effects_amount; ++i)
		{
			effects[i].apply();
		}
	}

	void add_effect(Effect<T> *effect)
	{
		effects.add_to_end(effect);
	}

	void delete_effect(Effect<T> *effect)
	{
		size_t effects_amount = effects.get_length();
		for (size_t i = 0; i < effects_amount; ++i)
		{
			if (effect == effects[i])
			{
				effects.slow_delete(i);
				return;
			}
		}
	}

	void delete_effect(const size_t index)
	{
		effects.slow_delete(index);
	}

	void tick()
	{
		if (applied)
			return;

		size_t effects_amount = effects.get_length();
		for (size_t i = 0; i < effects_amount; ++i)
		{
			effects.get_array()[i]->apply();
		}

		set_applied(true);
	}
};

#endif // AFFECTED_H
