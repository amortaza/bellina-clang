#pragma once

#include "bellina/bl-node.h" 

using namespace bl;

namespace node_drag {
	void load();
	
	extern char* plugin_name;

	struct NodeDragEvent {
		int mx;
		int my;

		int relativeX;
		int relativeY;

		Node* node;
	};
}