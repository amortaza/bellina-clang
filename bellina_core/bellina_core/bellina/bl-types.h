#pragma once

#include <functional>
#include "Xel/Xel.h"

using namespace std;

namespace bl { extern class Node; }

namespace bl {
	typedef function<bool(int mx, int my, Node* bubbledFrom)> NodeMouseMoveCallback;
	typedef function<bool(Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom)> NodeMouseDownCallback;
	typedef function<bool(Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom)> NodeMouseUpCallback;
	typedef function<bool(int amount, int mx, int my, Node* bubbledFrom)> NodeMouseScrollCallback;

	//

	typedef function<void(void)> PluginInit;
	typedef function<void(void)> PluginUninit;
	typedef function<void(void)> PluginTickAfterCoreRender;
	typedef function<bool(void*)> PluginCallback;
	typedef function<void(void)> PluginOnNode;

	//
	typedef function<void(Node*)> ShadowCallback;
	typedef function<void(void*)> ListenerCallback;

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