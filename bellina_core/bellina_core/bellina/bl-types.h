#pragma once

#include <functional>
#include "Xel/Xel.h"

namespace bl { extern class Node; }

namespace bl {
	typedef std::function<void(int mx, int my, Node* bubbledFrom)> MouseMoveCallback;
	typedef std::function<void(Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom)> MouseDownCallback;
	typedef std::function<void(Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom)> MouseUpCallback;
	typedef std::function<void(int amount, int mx, int my, Node* bubbledFrom)> MouseScrollCallback;

	typedef std::function<void(unsigned long long xcode, Node* bubbledFrom)> KeyDownCallback;
	typedef std::function<void(unsigned long long xcode, Node* bubbledFrom)> KeyUpCallback;
}