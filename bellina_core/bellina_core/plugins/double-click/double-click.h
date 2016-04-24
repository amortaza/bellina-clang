#pragma once

#include "bellina/bl-node.h" 

namespace double_click {
	void load();
	void init();
	void uninit();

	void onNode();

	extern char* plugin_name;

	struct MouseDoubleClickEvent {
		int mx;
		int my;
		Node* node;
		Xel::Mouse::Button button;
	};
}