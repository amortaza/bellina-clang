#pragma once

#include "bellina/bl-node.h" 

using namespace bl;

namespace mouse_drag {
	void load();

	void init();
	void uninit();

	void onNode();

	extern char* plugin_name;

	struct MouseDragEvent {
		int mx;
		int my;

		int relativeX, relativeY; // Relative.Pos = Node.Pos - Mouse.Pos (on initial click)
		int deltaX, deltaY;

		Node* node;

		Xel::Mouse::Button button;
	};
}