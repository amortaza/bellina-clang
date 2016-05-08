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

namespace bl {
	namespace plugin {
		Plugin* current_plugin = 0;
	}
}

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
	bl::on(pluginName, "default", nullptr, cb);
}

void bl::onLifeCycle(char* pluginName, char* lifeCycle, PluginCallback cb) {
	bl::onLifeCycle(pluginName, "default", lifeCycle, cb);
}

void bl::onLifeCycle(char* pluginName, char* signature, char* lifeCycle, PluginCallback cb) {
	if (!plugin::current_plugin) plugin::current_plugin = pango::getPluginByName(pluginName);

	if (plugin::current_plugin == 0) {
		printf("Unregistered plugin cannot be used, see \"%s\"\n", pluginName);
		return;
	}

	if (cb != nullptr)
		bubble::addCallback(cb, current_node->nid, pluginName, signature, lifeCycle);
}

void bl::on(char* pluginName, char* signature, PluginCtxFactory factory, PluginCallback cb) {
	if (!plugin::current_plugin) plugin::current_plugin = pango::getPluginByName(pluginName);

	if (plugin::current_plugin == 0) {
		printf("Unregistered plugin cannot be used, see \"%s\"\n", pluginName);
		return;
	}

	if (cb != nullptr) 
		bubble::addCallback(cb, current_node->nid, pluginName, signature, "default");

	// some plugins do not have on_node, see mouse-in
	if (plugin::current_plugin->on_node != nullptr)
		plugin::current_plugin->on_node(signature, factory);

	plugin::current_plugin = 0;
}

void bl::pluginCall(char* pluginName, char* signature, char* lifeCycle, Node* node, void* eventData) {
	Node* parent = node;
	bool bubble = true;

	//printf("pluginCall %s\n", lifeCycle);

	while (parent && bubble) {
		bubble = bubble::startBubble(parent->nid, pluginName, signature, lifeCycle, eventData) && bubble;
		parent = parent->parent;
	}
}


