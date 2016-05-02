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
			PluginOnNode on_node;
			PluginCtxFactory default_factory;
			PluginUninit uninit;
		};

		void uninit();

		namespace util {
			bool isRegistered(char* name);
			Plugin *getPluginByName(char* pluginName);

			string getPluginKey(char*nodeId, char* pluginName, char* signature);
			string getPluginKey(char* pluginName, char* signature);
		}
	}
}
