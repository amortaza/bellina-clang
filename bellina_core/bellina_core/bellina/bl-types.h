#pragma once

#include <functional>
#include "Xel/Xel.h"

namespace bl { extern class Node; }

namespace bl {
	typedef std::function<bool(int mx, int my, Node* bubbledFrom)> NodeMouseMoveCallback;
	typedef std::function<bool(Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom)> NodeMouseDownCallback;
	typedef std::function<bool(Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom)> NodeMouseUpCallback;
	typedef std::function<bool(int amount, int mx, int my, Node* bubbledFrom)> NodeMouseScrollCallback;

	//

	typedef std::function<void(void)> PluginInit;
	typedef std::function<void(void)> PluginUninit;
	typedef std::function<void(void)> PluginTickAfterCoreRender;
	typedef std::function<bool(void*)> PluginCallback;
	typedef std::function<void(void)> PluginOnNode;

	//
	typedef std::function<void(Node*)> ShadowCallback;
	typedef std::function<void(void*)> ListenerCallback;

	//
	
	struct BorderSide {
		unsigned char red, green, blue;
		int thickness;
		float alpha;
		bool topsCanvas;
	};

	struct Point {
		int x, y;
	};
}