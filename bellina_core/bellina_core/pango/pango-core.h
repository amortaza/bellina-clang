#pragma once

using namespace std;

#include "pango-types.h"

namespace pango {

	extern struct Plugin;

	void load(PluginLoad);

	bool isRegistered(char* pluginName);

	void registerPlugin(
		char* pluginName,
		PluginInit init,
		PluginCtxFactory default_factory,
		PluginOnNode on_node,
		PluginUninit uninit);

	Plugin *getPluginByName(char* pluginName);

	void uninit();

	string constructPluginKey(char*nodeId, char* pluginName, char* signature);
	string constructPluginKey(             char* pluginName, char* signature);
}