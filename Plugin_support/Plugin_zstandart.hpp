#ifndef PLUGIN_ZSTANDART_HPP
#define PLUGIN_ZSTANDART_HPP

#include <dlfcn.h>
#include "Plugin.hpp"

#include "plugin_std.hpp"

class Plugin_zstandart
{
private:
	

public:
	Plugin_zstandart(const char *dll_name)
	: Plugin(dll_name)
	{
		// Не забудь вызвать init
		
	}

	~Plugin_zstandart()
	{
		// Не забудь вызвать deinit

	}
};

#endif // PLUGIN_ZSTANDART_HPP
