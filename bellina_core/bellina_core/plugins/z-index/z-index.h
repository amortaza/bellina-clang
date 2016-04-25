#pragma once

#include "bellina/bl-node.h" // z-index.h (plugin) needs to be self contained

namespace z_index {
	void load();
	void init();
	void uninit();

	void onNode();

	extern char* plugin_name;

	struct ZIndexEvent {
		Node* topNode;
	};
}