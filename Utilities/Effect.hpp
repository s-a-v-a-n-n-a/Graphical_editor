#ifndef EFFECTS_H
#define EFFECTS_H

template<typename T> class Effect 
{
protected: 
	T *to_effect;

public:
	Effect(T *par_to_effect)
	: to_effect(par_to_effect)
	{ ; }

	void set_affected(T *other_object)
	{
		to_effect = other_object;
	}

	virtual void apply() = 0;
	void apply_to(T *other_object, bool change)
	{
		if (change)
		{
			set_affected(other_object);
			apply();
		}
		else
		{
			T *tmp_storage = to_effect;
			set_affected(other_object);
			apply();

			set_affected(tmp_storage);
		}
	}
};

#endif // EFFECTS_H
