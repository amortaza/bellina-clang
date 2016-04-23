#pragma once

#include "bellina/bl-node.h" // focus.h (plugin) needs to be self contained

namespace focus {
	void init();
	void tickOnAfterCoreRender();
	void uninit();

	void onNode(PluginCallback);

	struct FocusOnKeyEvent {
		bl::listener::KeyDownEvent* keyDownEvent;
		Node* node;
	};
}