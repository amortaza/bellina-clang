#pragma once

#include <map>

#include "bl-types.h"

using namespace bl;

namespace bl { extern class Node; }

namespace bl {
	namespace plugin {

		struct Plugin {
			std::string name;

			PluginInit init;
			PluginOnNode onNode;
			PluginTickAfterCoreRender tickAfterCoreRender;
			PluginTickBeforeEnd tickBeforeEnd; // current_node is still available
			PluginUninit uninit;
		};

		extern std::map<std::string, Plugin*> pluginMap;		

		void tickAfterCoreRender();
		void tickBeforeEnd(); // current_node is still available

		void uninit();		
	}
}
