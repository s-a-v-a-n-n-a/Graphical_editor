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
	Plugin_effect(const PPluginInterface *par_plugin, const PAppInterface *interface, void *par_handle, Canvas *canvas);
	~Plugin_effect();

	void apply();
};

#endif // PLUGIN_EFFECT_HPP
