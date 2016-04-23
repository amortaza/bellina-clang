#pragma once

#include "bellina/bl-node.h" 

namespace click {
	void init();
	void tickOnAfterCoreRender();
	void uninit();

	void onNode(PluginCallback);

	struct MouseClickEvent {
		int mx;
		int my;
		Node* node;
		Xel::Mouse::Button button;
	};
}