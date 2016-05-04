#include "stdafx.h"

#include "pango/pango.h"

#include"bl-node.h"
#include"bl-shadow-node.h"

using namespace bl;

void ShadowNode::copyTo(Node* target) {
	target->x = x;
	target->y = y;

	target->dim(w, h);
}

namespace bl {
	namespace shadow_node {
		BasePluginCtx* createDefaultPluginCtx(char* pluginName) {
			Plugin* plugin = pango::getPluginByName(pluginName);

			if (plugin == 0) {
				printf("ShadowNode.getPluginCtx failed cause there is no plugin named \"%s\"\n", pluginName);
				return 0;
			}

			if (plugin->default_factory == nullptr) {
				printf("ShadowNode.getPluginCtx failed cause there is no default factory for plugin named \"%s\"\n", pluginName);
				return 0;
			}

			return plugin->default_factory();
		}
	}
}
BasePluginCtx* ShadowNode::getPluginCtx(char* pluginName, char* signature, PluginCtxFactory factory) {
	string key = pango::constructPluginKey(pluginName, signature);

	auto e2 = pluginCtxByNameSignatureKey.find(key);

	if (e2 == pluginCtxByNameSignatureKey.end()) {
		BasePluginCtx* pluginCtx;

		if (strcmp("default", signature) == 0 || factory == nullptr) 
			pluginCtx = shadow_node::createDefaultPluginCtx(pluginName);
		else		
			pluginCtx = factory();

		setPluginCtx(pluginName, signature, pluginCtx);

		return pluginCtx;
	}
	
	return e2->second;
}

void ShadowNode::setPluginCtx(char* pluginName, char* signature, BasePluginCtx* pluginCtx) {
	string key = pango::constructPluginKey(pluginName, signature);

	pluginCtxByNameSignatureKey[key] = pluginCtx;
}

ShadowNode::~ShadowNode() {
	// id
	if (nid) delete[] nid;

	// plugins
	typedef map<string, BasePluginCtx*>::iterator it1;
	for (it1 it = pluginCtxByNameSignatureKey.begin(); it != pluginCtxByNameSignatureKey.end(); it++) {
		
		BasePluginCtx* p = it->second;

		delete p;
	}
}

