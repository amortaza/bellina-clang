#pragma once

#include "bellina/bl-node.h" 

using namespace bl;

namespace mouse_in {
	void load();
	void init();
	void uninit();

	void onNode();

	extern char* plugin_name;

	struct MouseInOutEvent {
		int mx;
		int my;
		Node* outNode;
		Node* inNode;
		bool isInEvent;
	};
}