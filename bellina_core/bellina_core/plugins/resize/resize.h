#pragma once

#include "bellina/bl-node.h" 

using namespace bl;

namespace resize {
	void load();
	void init();
	void uninit();

	void onNode();

	struct ResizeEvent {
		int w;
		int h;
		Node* node;
	};
}