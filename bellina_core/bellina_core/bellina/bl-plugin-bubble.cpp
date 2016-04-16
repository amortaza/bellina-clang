#include "stdafx.h"

#include "bl-node.h"
#include "bl-plugin-bubble.h"

using namespace bl;
using namespace bl::plugin::bubble;

void PluginBubble::bubbleUp(Node* node, char* pluginName, void* eventData) {
	bool bubble = true;

	Node* parent = node;

	while (bubble && parent) {
		PluginCallback cb = getCallback(parent, pluginName);

		if (cb) bubble = cb(eventData);

		parent = parent->parent;
	}
}

PluginCallback PluginBubble::getCallback(Node* node, char* pluginName) {
	std::string key(node->nid);
	key.append(":");
	key.append(pluginName);

	auto e2 = callback_By_NodeId_and_PluginName.find(key);

	if (e2 == callback_By_NodeId_and_PluginName.end()) return nullptr;

	return e2->second;
}

void PluginBubble::setCallback(PluginCallback cb, Node* node, char* pluginName) {
	std::string key(node->nid);
	key.append(":");
	key.append(pluginName);

	auto e2 = callback_By_NodeId_and_PluginName.find(key);

	if (e2 != callback_By_NodeId_and_PluginName.end()) throw "There is already a callback registered for this plugin for this node.";

	callback_By_NodeId_and_PluginName[key] = cb;
}

PluginBubble::~PluginBubble() {
	callback_By_NodeId_and_PluginName.clear();
}