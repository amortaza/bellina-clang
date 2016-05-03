#include "stdafx.h"

#include <map>

#include "pango-core.h"
#include "pango-state.h"
#include "pango-params.h"

#include "Plugin.h"

using namespace std;
using namespace pango;
using namespace pango::_;

bool pango::isRegistered(char* pluginName) {
	return getPluginByName(pluginName) != 0;
}

Plugin* pango::getPluginByName(char* pluginName) {
	string key(pluginName);

	auto e2 = pluginByName.find(key);

	if (e2 == pluginByName.end()) return 0;

	return e2->second;
}

void pango::uninit() {
	typedef map<string, Plugin*>::iterator it1;

	for (it1 it = pluginByName.begin(); it != pluginByName.end(); it++) {
		Plugin* plugin = it->second;

		if (plugin->uninit != nullptr) plugin->uninit();

		delete plugin;
	}

	intProperty.clear();
	boolProperty.clear();
}

string pango::constructPluginKey(char*nodeId, char* pluginName, char* signature) {
	string key(nodeId);

	key.append(":");
	key.append(pluginName);
	key.append(".");
	key.append(signature);

	return key;
}

string pango::constructPluginKey(char* pluginName, char* signature) {
	string key(pluginName);

	key.append(".");
	key.append(signature);

	return key;
}

void pango::registerPlugin(
	char* pluginName,
	PluginInit init,
	PluginCtxFactory default_factory,
	PluginOnNode on_node,
	PluginUninit uninit) {

	if (isRegistered(pluginName)) {
		// rintf("Plugin \"%s\" is already loaded.  Ignoring re-load request.\n", pluginName);
		return;
	}

	Plugin* plugin = new Plugin();

	plugin->name.assign(pluginName, strlen(pluginName));
	plugin->init = init;
	plugin->default_factory = default_factory;
	plugin->on_node = on_node;
	plugin->uninit = uninit;

	pluginByName[plugin->name] = plugin;

	if (init != nullptr) init();
}

void pango::load(PluginLoad load) {
	load();
}




