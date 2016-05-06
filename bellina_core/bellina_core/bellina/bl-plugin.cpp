#include "stdafx.h"

#include "pango/pango.h"

#include "bl-types.h"
#include "bl-core.h"
#include "bl-globals.h"
#include "bl-node.h"

using namespace std;

using namespace pango;

using namespace bl;
using namespace bl::_;

void bl::pluginCtxOnNode(char* pluginName, char* signature, PluginCtxFactory factory) {
	BasePluginCtx* ctx = current_node->getPluginCtxFromShadow(pluginName, signature, factory);
	
	ctx->pluginOnNode();
}

void bl::use(char* pluginName) {
	bl::use(pluginName, "default", nullptr);
}

void bl::use(char* pluginName, char* signature, PluginCtxFactory factory) {
	on(pluginName, signature, factory, nullptr);
}

void bl::on(char* pluginName, PluginCallback cb) {
	bl::on(pluginName, "default", "default", nullptr, cb);
}

void bl::on(char* pluginName, char* signature, PluginCtxFactory factory, PluginCallback cb) {
	bl::on(pluginName, signature, "default", factory, cb);
}

void bl::on(char* pluginName, char* signature, char* lifeCycle, PluginCtxFactory factory, PluginCallback cb) {
	if (!isRegistered(pluginName)) {
		printf("Unregistered plugin cannot be used, see \"%s\"\n", pluginName);
		return;
	}

	Plugin* plugin = pango::getPluginByName(pluginName);

	if (cb != nullptr) 
		bubble::addCallback(cb, current_node->nid, pluginName, signature, lifeCycle);

	// some plugins do not have on_node, see mouse-in
	if (plugin->on_node != nullptr)
		plugin->on_node(signature, factory);
}

void bl::pluginCall(char* pluginName, char* signature, Node* node, void* eventData) {
	bl::pluginCall(pluginName, signature, "default", node, eventData);
}

void bl::pluginCall(char* pluginName, char* signature, char* lifeCycle, Node* node, void* eventData) {
	Node* parent = node;
	bool bubble = true;

	while (parent && bubble) {
		bubble = bubble::startBubble(parent->nid, pluginName, signature, lifeCycle, eventData) && bubble;
		parent = parent->parent;
	}
}

