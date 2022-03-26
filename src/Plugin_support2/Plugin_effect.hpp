#ifndef PLUGIN_EFFECT_HPP
#define PLUGIN_EFFECT_HPP

#include "Plugin.hpp"

#include "../Utilities/Effect.hpp"
#include "../Editor/Canvas.hpp"

#include "../sfml_drawing/colors.hpp"

class Plugin_effect : public Plugin, public Effect<Canvas>
{
private:

public:
	Plugin_effect(PUPPY::PluginInterface *par_plugin, const PUPPY::AppInterface *interface, void *par_handle, Canvas *canvas, const char *name = nullptr);
	~Plugin_effect();

	void apply();
};

#endif // PLUGIN_EFFECT_HPP
