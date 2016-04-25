#include "stdafx.h"

#include "bl-types.h"
#include "bl-core.h"
#include "bl-globals.h"
#include "bl-plugin.h"
#include "bl-plugin-bubble.h"

using namespace std;

using namespace bl;
using namespace bl::_;
using namespace bl::plugin;

namespace bl {
	namespace plugin {
		map<string, Plugin*> pluginMap;

		map<string, int> intMap;

		bool isRegistered(char* name) {
			string key(name);

			auto e2 = pluginMap.find(key);
			
			return e2 != pluginMap.end();			
		}
	}
}

void bl::pluginSetInt(char* name, char* prop_name, int value) {
	string key(name);
	key.append(":");
	key.append(prop_name);

	intMap[key] = value;
}

int bl::pluginGetInt(char* name, char* prop_name) {
	string key(name);
	key.append(":");
	key.append(prop_name);

	auto e2 = intMap.find(key);
	if (e2 == intMap.end()) throw "plugin value not found in pluginGetInt";

	return e2->second;
}

bool bl::pluginHasInt(char* name, char* prop_name) {
	string key(name);
	key.append(":");
	key.append(prop_name);

	auto e2 = intMap.find(key);
	if (e2 == intMap.end()) return false;

	return true;
}

void bl::pluginLoad(PluginLoad load) {
	load();
}

void bl::pluginRegister(char* pluginName, 
						PluginInit init, 
						PluginOnNode onNode, 
						PluginUninit uninit) {

	if (plugin::isRegistered(pluginName)) {
		printf("Plugin \"%s\" is already loaded.  Ignoring re-load request.\n", pluginName);
		return;
	}

	Plugin* plugin = new Plugin();

	plugin->name.assign(pluginName, strlen(pluginName));
	plugin->init = init;
	plugin->onNode = onNode;
	plugin->uninit = uninit;

	pluginMap[plugin->name] = plugin;

	if (init != nullptr) init();
}


void bl::use(char* pluginName) {
	on(pluginName, nullptr);
}

void bl::on(char* pluginName, PluginCallback cb) {
	if (!isRegistered(pluginName)) {
		printf("Unregistered plugin cannot be used, see \"%s\"\n", pluginName);
		return;
	}

	string key(pluginName);

	auto e2 = pluginMap.find(key);

	Plugin* plugin = e2->second;

	_::pluginBubble->setCallback(cb, current_node, pluginName);

	plugin->onNode();
}

void bl::pluginCall(char* pluginName, Node* node, void* eventData) {
	_::pluginBubble->bubbleUp(node, pluginName, eventData);
}

void bl::plugin::uninit() {
	//
	typedef map<string, Plugin*>::iterator it1;
	for (it1 it = pluginMap.begin(); it != pluginMap.end(); it++) {
		Plugin* plugin = it->second;

		if (plugin->uninit != nullptr) plugin->uninit();

		delete plugin;
	}

	//
	intMap.clear();
}