#pragma once

using namespace std;

#include <list>

#include "MapList.h"
#include "pango-types.h"

namespace pango {
	namespace bubble {
		namespace _ {
			extern MapList<PluginCallback> callbacks_By_NodeId_and_PluginName_and_Signature_and_LifeCycle;
		}

		void addCallback(PluginCallback cb, char* nodeId, char* pluginName, char* signature, char* lifeCycle);
		list<PluginCallback>* getCallbacks(char* nodeId, char* pluginName, char* signature, char* lifeCycle);

		bool startBubble(char* nodeId, char* pluginName, char* signature, char* lifeCycle, void* eventData);

		void clearCallbacks();
	}
}