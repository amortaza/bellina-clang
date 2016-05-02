#pragma once

#include "bellina/bl-node.h" // z-index.h (plugin) needs to be self contained

namespace z_index { extern class ZIndexContext; }

namespace z_index {
	void load();
	ZIndexContext* default_factory();
	void on_node(char* signature, PluginCtxFactory factory);

	extern char* plugin_name;

	struct ZIndexEvent {
		Node* topNode;
	};
}