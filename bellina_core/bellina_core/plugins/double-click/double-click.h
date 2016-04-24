#pragma once

#include "bellina/bl-node.h" 

namespace double_click {
	void load();
	void init();
	void tickOnAfterCoreRender();
	void uninit();

	void onNode();

	struct MouseDoubleClickEvent {
		int mx;
		int my;
		Node* node;
		Xel::Mouse::Button button;
	};
}