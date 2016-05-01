#pragma once

#include "bellina/bl-node.h" 

namespace click {
	void load();
	void init();
	void uninit();

	void onNode(char* signature);

	extern char* plugin_name;

	struct MouseClickEvent {
		int mx;
		int my;
		Node* node;
		Xel::Mouse::Button button;
	};
}