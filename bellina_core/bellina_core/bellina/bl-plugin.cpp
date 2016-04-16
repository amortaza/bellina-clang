#include "stdafx.h"

#include "bl-core.h"
#include "bl-globals.h"
#include "bl-plugin.h"
#include "bl-plugin-bubble.h"

using namespace bl::_;
using namespace bl::plugin;

namespace bl {
	namespace plugin {
		std::map<std::string, Plugin*> pluginMap;

		std::map<std::string, int> intMap;
	}
}

void bl::pluginSetInt(char* name, char* prop_name, int value) {
	std::string key(name);
	key.append(":");
	key.append(prop_name);

	intMap[key] = value;
}

int bl::pluginGetInt(char* name, char* prop_name) {
	std::string key(name);
	key.append(":");
	key.append(prop_name);

	auto e2 = intMap.find(key);
	if (e2 == intMap.end()) throw "plugin value not found in pluginGetInt";

	return e2->second;
}

bool bl::pluginHasInt(char* name, char* prop_name) {
	std::string key(name);
	key.append(":");
	key.append(prop_name);

	auto e2 = intMap.find(key);
	if (e2 == intMap.end()) return false;

	return true;
}

void bl::plugin::tick() {
	typedef std::map<std::string, Plugin*>::iterator it1;
	for (it1 it = pluginMap.begin(); it != pluginMap.end(); it++) {
		Plugin* plugin = it->second;

		if (plugin->tick != nullptr) plugin->tick();
	}
}

void bl::pluginLoad(char* pluginName, PluginInit init, PluginOnNode onNode, PluginTick tick, PluginUninit uninit) {
	Plugin* plugin = new Plugin();

	plugin->name.assign(pluginName, strlen(pluginName));
	plugin->init = init;
	plugin->onNode = onNode;
	plugin->tick = tick;
	plugin->uninit = uninit;

	pluginMap[plugin->name] = plugin;

	if (init != nullptr) init();
}


void bl::use(char* pluginName) {
	on(pluginName, nullptr);
}

void bl::on(char* pluginName, PluginCallback cb) {
	std::string key(pluginName);

	auto e2 = pluginMap.find(key);
	if (e2 == pluginMap.end()) throw "plugin not found";

	Plugin* plugin = e2->second;

	pluginBubble->setCallback(cb, current_node, pluginName);

	plugin->onNode(cb);
}

void bl::pluginCall(char* pluginName, Node* node, void* eventData) {
	_::pluginBubble->bubbleUp(node, pluginName, eventData);
}

void bl::plugin::uninit() {
	//
	typedef std::map<std::string, Plugin*>::iterator it1;
	for (it1 it = pluginMap.begin(); it != pluginMap.end(); it++) {
		Plugin* plugin = it->second;

		if (plugin->uninit != nullptr) plugin->uninit();

		delete plugin;
	}

	//
	intMap.clear();
}