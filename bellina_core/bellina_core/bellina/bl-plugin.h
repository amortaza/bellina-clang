#pragma once

#include <map>

namespace bl { extern class Node; }

namespace bl {
	namespace plug {
		typedef std::function<void(void)> PluginInit;		
		typedef std::function<void(void)> PluginUninit;
		typedef std::function<void(void*)> PluginCallback;
		typedef std::function<void(PluginCallback)> PluginTick;

		struct Plugin {
			std::string name;

			PluginInit init;
			PluginTick tick;
			PluginUninit uninit;
		};

		extern std::map<std::string, Plugin*> pluginMap;

		void uninit();
	}
}
