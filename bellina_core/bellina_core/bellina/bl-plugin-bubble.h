#pragma once

#include <map>

#include "bl-types.h"
#include "bl-map-list.h"

using namespace std;

namespace bl { extern class Node; }

namespace bl {
	namespace plugin {
		namespace bubble {
			class PluginBubble {
			public:
				~PluginBubble();

			public:
				void bubbleUp(Node* node, char* pluginName, char* signature, void* eventData);

				void addCallback(PluginCallback* ptrCb, Node* node, char* pluginName, char* signature);
				list<PluginCallback*>* getCallbacks(Node*, char* pluginName, char* signature);

			private:				
				MapList<PluginCallback*> callbackPtrList_By_NodeId_and_PluginName_and_Signature;
			};
		}
	}
}