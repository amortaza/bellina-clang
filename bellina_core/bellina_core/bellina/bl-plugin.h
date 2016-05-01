#pragma once

#include <map>

#include "bl-types.h"

using namespace std;
using namespace bl;

namespace bl { extern class Node; }

namespace bl {

	namespace plugin {

		struct Plugin {
			string name;

			PluginInit init;
			PluginOnNode onNode;
			PluginUninit uninit;
		};

		//extern map<string, Plugin*> pluginByNameSignatureKey;
		//extern map<string, Plugin*> pluginRegistryByName;

		void uninit();

		namespace util {
			string getPluginKey(char*nodeId, char* pluginName, char* signature);
			string getPluginKey(char* pluginName, char* signature);
		}
	}
}
