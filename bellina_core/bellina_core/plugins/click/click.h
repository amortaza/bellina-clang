#pragma once

#include "bellina/bl-node.h" 

namespace click {
	void init();
	void tick(PluginCallback);
	void uninit();

	struct MouseClickEvent {
		int mx;
		int my;
		Node* node;
		Xel::Mouse::Button button;
	};
}