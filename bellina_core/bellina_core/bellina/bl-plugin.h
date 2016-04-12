#pragma once

//extern class bl::Node;
//#include "bl-node.h"

//namespace bl {
	//namespace plug {
		typedef std::function<void(void)> PluginInit;
		typedef std::function<void(bl::Node*)> PluginTick;
		typedef std::function<void(void)> PluginUninit;

		struct Plugin {
			std::string name;
			PluginInit init;
			PluginTick tick;
			PluginUninit uninit;
		};

		//extern std::map<std::string, Plugin*> pluginMap2;
	//}
//}
