#pragma once

using namespace std;

#include <list>

#include "MapList.h"
#include "pango-types.h"

namespace pango {
	namespace bubble {
		namespace _ {
			extern MapList<PluginCallback> callbacks_By_NodeId_and_PluginName_and_Signature;
		}

		void addCallback(PluginCallback cb, char* nodeId, char* pluginName, char* signature);
		list<PluginCallback>* getCallbacks(char* nodeId, char* pluginName, char* signature);

		bool startBubble(char* nodeId, char* pluginName, char* signature, void* eventData);

		void clearCallbacks();
	}
}