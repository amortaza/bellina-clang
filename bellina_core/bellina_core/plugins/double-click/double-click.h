#pragma once

#include "bellina/bl-node.h" 

namespace double_click {
	void init();
	void tick();
	void uninit();

	void onNode(PluginCallback);

	struct MouseDoubleClickEvent {
		int mx;
		int my;
		Node* node;
		Xel::Mouse::Button button;
	};
}