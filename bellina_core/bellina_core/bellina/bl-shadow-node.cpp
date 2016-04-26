#include "stdafx.h"

#include"bl-node.h"
#include"bl-shadow-node.h"

#include "BasePluginContext.h"

using namespace bl;

void ShadowNode::copyTo(Node* target) {
	target->x = x;
	target->y = y;

	target->dim(w, h);
}

BasePluginContext* ShadowNode::getPlugin(char* pluginName, PluginFactory factory) {
	string key(pluginName);

	auto e2 = basePluginMap.find(key);
	if (e2 == basePluginMap.end()) {
		if (factory == nullptr) {
			printf("getPlugin \"%s\" did not have a plugin for node id \"%s\".\n", pluginName, nid);
			return 0;
		}

		BasePluginContext* plugin = factory();

		addPlugin(pluginName, plugin);

		return plugin;
	}
	
	return e2->second;
}

void ShadowNode::addPlugin(char* pluginName, BasePluginContext* plugin) {
	string key(pluginName);

	basePluginMap[key] = plugin;
}

ShadowNode::~ShadowNode() {
	// id
	if (nid) delete[] nid;

	// plugins
	typedef map<string, BasePluginContext*>::iterator it1;
	for (it1 it = basePluginMap.begin(); it != basePluginMap.end(); it++) {
		
		BasePluginContext* p = it->second;

		delete p;
	}
}

