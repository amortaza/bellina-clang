#pragma once

#include "bellina/bl-node.h" 

using namespace bl;

namespace drag {
	void init();
	void tickOnAfterCoreRender();
	void uninit();

	void onNode();

	struct DragEvent {
		int mx;
		int my;

		int dx;
		int dy;

		Node* node;

		Xel::Mouse::Button button;
	};
}