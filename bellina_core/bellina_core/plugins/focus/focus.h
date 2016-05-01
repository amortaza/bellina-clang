#pragma once

#include "bellina/bl-node.h" // focus.h (plugin) needs to be self contained

namespace focus {
	void load();
	void init();
	void uninit();

	void onNode(char* signature);

	extern char* plugin_name;

	struct FocusOnKeyEvent {
		bl::listener::KeyDownEvent* keyDownEvent;
		Node* node;
	};
}