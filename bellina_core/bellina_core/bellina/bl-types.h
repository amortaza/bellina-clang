#pragma once

#include <functional>
#include "Xel/Xel.h"

namespace bl { extern class Node; }

namespace bl {
	typedef std::function<void(int mx, int my, Node* bubbledFrom)> NodeMouseMoveCallback;
	typedef std::function<void(Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom)> NodeMouseDownCallback;
	typedef std::function<void(Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom)> NodeMouseUpCallback;
	typedef std::function<void(int amount, int mx, int my, Node* bubbledFrom)> NodeMouseScrollCallback;

	typedef std::function<void(unsigned long long xcode, Node* bubbledFrom)> NodeKeyDownCallback;
	typedef std::function<void(unsigned long long xcode, Node* bubbledFrom)> NodeKeyUpCallback;

	//

	typedef std::function<void(void)> PluginInit;
	typedef std::function<void(void)> PluginUninit;
	typedef std::function<void(void)> PluginTick;
	typedef std::function<void(void*)> PluginCallback;
	typedef std::function<void(PluginCallback)> PluginOnNode;

	//

	typedef std::function<void(void*)> ListenerCallback;
}