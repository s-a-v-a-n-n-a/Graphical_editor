#ifndef EFFECTS_H
#define EFFECTS_H

#include <cstring>
#include <cstdlib>
#include <cstdio>

template<typename T> class Effect 
{
protected: 
	T *to_effect;

	bool appliable;

	char *name;

public:
	Effect(T *par_to_effect)
	: to_effect(par_to_effect), appliable(true)
	{ ; }

	Effect(T *par_to_effect, const char *par_name)
	: to_effect(par_to_effect), appliable(true), name(nullptr)
	{ 
		if (par_name)
		{
			size_t name_size = strlen(par_name);
		
			name = new char[name_size + 1];
			strncpy(name, par_name, name_size);
			name[name_size] = 0;
		}
	}

	virtual ~Effect() 
	{
		if (name)
			delete [] name;
	} 

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

	void set_appliable(const bool par_appliable) { appliable = par_appliable; }
	bool get_appliable() const { return appliable; }

	char *get_name() { return name; }
};

#endif // EFFECTS_H
