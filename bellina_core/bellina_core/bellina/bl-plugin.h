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
			//PluginTickAfterCoreRender tickAfterCoreRender;
			PluginUninit uninit;
		};

		extern map<string, Plugin*> pluginMap;

		void registerTickAfterCoreRender(PluginTickAfterCoreRender);

		void tickAfterCoreRender();

		void uninit();		
	}
}
