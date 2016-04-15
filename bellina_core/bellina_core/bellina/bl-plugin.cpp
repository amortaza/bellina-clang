#include "stdafx.h"

#include "bl-core.h"

#include "bl-plugin.h"

using namespace bl::plug;

namespace bl {
	namespace plug {
		std::map<std::string, Plugin*> pluginMap;
	}
}

void bl::plug::tick() {
	typedef std::map<std::string, Plugin*>::iterator it1;
	for (it1 it = pluginMap.begin(); it != pluginMap.end(); it++) {
		Plugin* plugin = it->second;

		if (plugin->tick != nullptr) plugin->tick();
	}
}

void bl::plugin(char* name, PluginInit init, PluginOnNode onNode, PluginTick tick, PluginUninit uninit) {
	Plugin* plugin = new Plugin();

	plugin->name.assign(name, strlen(name));
	plugin->init = init;
	plugin->onNode = onNode;
	plugin->tick = tick;
	plugin->uninit = uninit;

	pluginMap[plugin->name] = plugin;

	if (init != nullptr) init();
}


void bl::use(char* name) {
	on(name, nullptr);
}

void bl::on(char* name, PluginCallback cb) {
	std::string key(name);

	auto e2 = pluginMap.find(key);
	if (e2 == pluginMap.end()) throw "plugin not found";

	Plugin* plugin = e2->second;

	plugin->onNode(cb);
}

void bl::plug::uninit() {
	typedef std::map<std::string, Plugin*>::iterator it1;
	for (it1 it = pluginMap.begin(); it != pluginMap.end(); it++) {
		Plugin* plugin = it->second;

		if (plugin->uninit != nullptr) plugin->uninit();

		delete plugin;
	}
}