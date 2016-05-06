#include "stdafx.h"

#include "pango-bubble.h"
#include "pango-core.h"

namespace pango {
	namespace bubble {
		namespace _ {
			MapList<PluginCallback> callbacks_By_NodeId_and_PluginName_and_Signature_and_LifeCycle;
		}
	}
}

using namespace std;

using namespace pango;
using namespace pango::bubble::_;

void bubble::clearCallbacks() {
	callbacks_By_NodeId_and_PluginName_and_Signature_and_LifeCycle.clear();
}

void bubble::addCallback(PluginCallback cb, char* nodeId, char* pluginName, char* signature, char* lifeCycle) {
	if (cb == nullptr) return;

	string key = constructPluginKey__Node_and_Plugin_and_Signature_and_LifeCycle(nodeId, pluginName, signature, lifeCycle);

	//cout << "adding callback " << key << "\n";
	callbacks_By_NodeId_and_PluginName_and_Signature_and_LifeCycle.add(key, cb);
}

list<PluginCallback>* bubble::getCallbacks(char* nodeId, char* pluginName, char* signature, char* lifeCycle) {
	string key = constructPluginKey__Node_and_Plugin_and_Signature_and_LifeCycle(nodeId, pluginName, signature, lifeCycle);

	list<PluginCallback>* cbs = callbacks_By_NodeId_and_PluginName_and_Signature_and_LifeCycle.getList(key);

	/*if (cbs) {
		cout << "getting callback " << key << "\n";

		//printf("size %i\n", cbs->size());
	}*/
	return cbs;
}

bool bubble::startBubble(char* nodeId, char* pluginName, char* signature, char* lifeCycle, void* eventData) {

	bool bubble = true;

	//printf("startBubble %s %s\n", nodeId, lifeCycle);

	list<PluginCallback>* cbs = getCallbacks(nodeId, pluginName, signature, lifeCycle);
	
	if (cbs) {
		
		list<PluginCallback>::const_iterator it;
		for (it = cbs->begin(); it != cbs->end(); ++it) {
			PluginCallback cb = *it;

			bubble = cb(eventData) && bubble;
		}
	}

	return bubble;
}




