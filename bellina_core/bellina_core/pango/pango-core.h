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

	string constructPluginKey__Node_and_Plugin_and_Signature_and_LifeCycle(char*nodeId, char* pluginName, char* signature, char* lifeCycle);
	string constructPluginKey__Plugin_and_Signature_and_LifeCycle(                      char* pluginName, char* signature, char* lifeCycle);
	string constructPluginKey__Plugin_and_Signature(                                    char* pluginName, char* signature);
}