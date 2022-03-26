#ifndef CANVAS_EFFECTS_MANAGER_HPP
#define CANVAS_EFFECTS_MANAGER_HPP

#include "../../Utilities/Effect.hpp"
#include "../Canvas.hpp"

// class Effects_manager;

// class Effects_manager_destroyer
// {
// private:
// 	Effects_manager *effect_manager;


// public:
// 	~Effects_manager_destroyer();

// 	void initialize(Effects_manager *par_effect_manager);
// };

class Effect_manager
{
private:
	// static Effects_manager *effect_manager;
	// static Effects_manager_destroyer destroyer;

	// List<Tool*> tools;
	std::vector<Effect<Canvas>*> effects;
	size_t effects_amount;

protected:
public:
	Effect_manager();
	// friend class Effects_manager_destroyer;

	~Effect_manager();
	// static Effects_manager *get_instance();

	void add_effect(Effect<Canvas> *effect);
	void delete_effect(Effect<Canvas> *effect);

	size_t get_effects_amount() const { return effects_amount; }
	const std::vector<Effect<Canvas>*> &get_effects() { return effects; }
};

#endif // CANVAS_EFFECTS_MANAGER_HPP
