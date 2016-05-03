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
	bl::on(pluginName, "default", nullptr, cb);
}

void bl::on(char* pluginName, char* signature, PluginCtxFactory factory, PluginCallback cb) {
	if (!isRegistered(pluginName)) {
		printf("Unregistered plugin cannot be used, see \"%s\"\n", pluginName);
		return;
	}

	Plugin* plugin = pango::getPluginByName(pluginName);

	if (cb != nullptr) 
		bubble::addCallback(cb, current_node->nid, pluginName, signature);

	// some plugins do not have on_node, see mouse-in
	if (plugin->on_node != nullptr)
		plugin->on_node(signature, factory);
}

void bl::pluginCall(char* pluginName, char* signature, Node* node, void* eventData) {
	printf("you forgot bl-plugin.cpp line 52...parent!!!\n");
	bubble::startBubble(node->nid, pluginName, signature, eventData);
}

