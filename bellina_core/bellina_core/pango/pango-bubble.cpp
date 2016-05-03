#include "stdafx.h"

#include "pango-bubble.h"
#include "pango-core.h"

namespace pango {
	namespace bubble {
		namespace _ {
			MapList<PluginCallback> callbacks_By_NodeId_and_PluginName_and_Signature;
		}
	}
}

using namespace std;

using namespace pango;
using namespace pango::bubble::_;

void bubble::clearCallbacks() {
	callbacks_By_NodeId_and_PluginName_and_Signature.clear();
}

void bubble::addCallback(PluginCallback cb, char* nodeId, char* pluginName, char* signature) {
	if (cb == nullptr) return;

	string key = constructPluginKey(nodeId, pluginName, signature);

	callbacks_By_NodeId_and_PluginName_and_Signature.add(key, cb);
}

list<PluginCallback>* bubble::getCallbacks(char* nodeId, char* pluginName, char* signature) {
	string key = constructPluginKey(nodeId, pluginName, signature);

	list<PluginCallback>* cbs = callbacks_By_NodeId_and_PluginName_and_Signature.getList(key);

	return cbs;
}
bool bubble::startBubble(char* nodeId, char* pluginName, char* signature, void* eventData) {

	bool bubble = true;

	list<PluginCallback>* cbs = getCallbacks(nodeId, pluginName, signature);
	
	if (cbs) {
		
		list<PluginCallback>::const_iterator it;
		for (it = cbs->begin(); it != cbs->end(); ++it) {
			PluginCallback cb = *it;

			bubble = cb(eventData) && bubble;
		}
	}

	return bubble;
}




