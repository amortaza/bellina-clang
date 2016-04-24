#pragma once

#include "bellina/bl-node.h" 

namespace click {
	void load();
	void init();
	void tickOnAfterCoreRender();
	void uninit();

	void onNode();

	struct MouseClickEvent {
		int mx;
		int my;
		Node* node;
		Xel::Mouse::Button button;
	};
}