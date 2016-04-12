#include "stdafx.h"

#include "bl-core.h"

#include "bl-plugin.h"

//using namespace bl::plug;


//namespace bl {
	//namespace plug {
		std::map<std::string, Plugin*> pluginMap;
	//}
//}

void bl::plugin(char* name, PluginInit init, PluginTick tick, PluginUninit uninit) {
	Plugin* plugin = new Plugin();

	plugin->name.assign(name, strlen(name));
	plugin->init = init;
	plugin->tick = tick;
	plugin->uninit = uninit;

	pluginMap[plugin->name] = plugin;

	if (init != nullptr) init();
}

void bl::use(char* name) {
	//Plugin* plugin = 
}