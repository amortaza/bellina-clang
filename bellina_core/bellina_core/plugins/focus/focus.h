#pragma once

#include "bellina/bl-node.h" // focus.h (plugin) needs to be self contained

namespace focus {
	void init();
	void tick();
	void uninit();

	void onNode(PluginCallback);
}