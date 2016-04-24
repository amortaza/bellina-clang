#pragma once

#include "bellina/bl-node.h" 

using namespace bl;

namespace node_drag {
	void load();

	void init();	
	void uninit();

	void onNode();

	struct NodeDragEvent {
		int mx;
		int my;

		int dx;
		int dy;

		Node* node;
	};
}