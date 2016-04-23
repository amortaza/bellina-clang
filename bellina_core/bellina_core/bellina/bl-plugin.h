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
			PluginUninit uninit;
		};

		extern std::map<std::string, Plugin*> pluginMap;		

		void tickAfterCoreRender();

		void uninit();		
	}
}
