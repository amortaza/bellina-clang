#pragma once

#include "bellina/bl-node.h" 

namespace click {
	void load();

	extern char* plugin_name;

	struct MouseClickEvent {
		int mx;
		int my;
		Node* node;
		Xel::Mouse::Button button;
	};

	namespace lifecycle {
		extern char* default;
		extern char* mouse_down;
		extern char* mouse_drag;
		extern char* mouse_up_and_no_click;
	}
}