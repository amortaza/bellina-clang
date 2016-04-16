#pragma once

#include <map>

#include "echo/echo.h"

#include "bl-types.h"

using namespace echo;
using namespace bl;

namespace bl { extern class Node; }

namespace bl {
	namespace plug {

		struct Plugin {
			std::string name;

			PluginInit init;
			PluginOnNode onNode;
			PluginTick tick;
			PluginUninit uninit;
		};

		extern std::map<std::string, Plugin*> pluginMap;		

		void tick();
		void uninit();		
	}
}
