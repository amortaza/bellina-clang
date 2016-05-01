#include "stdafx.h"

#include "bl-node.h"
#include "bl-plugin.h"
#include "bl-plugin-bubble.h"

using namespace bl;
using namespace bl::plugin;
using namespace bl::plugin::bubble;

void PluginBubble::bubbleUp(Node* node, char* pluginName, char* signature, void* eventData) {
	bool bubble = true;

	Node* parent = node;

	while (bubble && parent) {
		list<PluginCallback>* cbs = getCallbacks(parent, pluginName, signature);
		//rintf("got callbacks for signature %s\n", signature);
		if (cbs) {
			//rintf("cbs size %s %i\n", signature, cbs->size());
			list<PluginCallback>::const_iterator it;
			for (it = cbs->begin(); it != cbs->end(); ++it) {
				PluginCallback cb = *it;

				bubble = cb(eventData) && bubble;
			}			
		}

		parent = parent->parent;
	}
}

list<PluginCallback>* PluginBubble::getCallbacks(Node* node, char* pluginName, char* signature) {
	string key = util::getPluginKey(node->nid, pluginName, signature);

	list<PluginCallback>* cbs = callbacks_By_NodeId_and_PluginName_and_Signature.getList(key);

	return cbs;
}

void PluginBubble::addCallback(PluginCallback cb, Node* node, char* pluginName, char* signature) {
	string key = util::getPluginKey(node->nid, pluginName, signature);

	callbacks_By_NodeId_and_PluginName_and_Signature.add(key, cb);
}

PluginBubble::~PluginBubble() {
	callbacks_By_NodeId_and_PluginName_and_Signature.clear();
}