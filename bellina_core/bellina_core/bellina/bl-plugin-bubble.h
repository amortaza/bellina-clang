#pragma once

#include <map>

#include "bl-types.h"

namespace bl { extern class Node; }

namespace bl {
	namespace plugin {
		namespace bubble {
			class PluginBubble {
			public:
				~PluginBubble();

			public:
				void bubbleUp(Node* node, char* pluginName, void* eventData);

				void setCallback(PluginCallback cb, Node* node, char* pluginName);
				PluginCallback getCallback(Node*, char* pluginName);

			private:				
				std::map<std::string, PluginCallback> callback_By_NodeId_and_PluginName;
			};
		}
	}
}