#pragma once

#include "bellina/bl-node.h" 

namespace double_click {
	void load();

	extern char* plugin_name;

	struct MouseDoubleClickEvent {
		int mx;
		int my;
		Node* node;
		Xel::Mouse::Button button;
	};
}