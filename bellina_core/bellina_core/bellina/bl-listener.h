#pragma once

#include <list>

#include "Xel/Xel.h"

namespace bl { extern class Node; }

namespace bl { 
	namespace listener {

		struct KeyUpEvent {
			unsigned long long xcode;
		};

		struct KeyDownEvent {
			unsigned long long xcode;
		};

		struct MouseScrollEvent {
			int mx;
			int my;
			int amount;
			Node* node;
		};

		struct MouseMoveEvent {
			int mx;
			int my;
			Node* node;
		};

		struct MouseDownEvent{
			int mx;
			int my;
			Node* node;
			Xel::Mouse::Button button;
		};

		struct MouseUpEvent {
			int mx;
			int my;
			Node* node;
			Xel::Mouse::Button button;
		};

		struct ResizeEvent {
			int width;
			int height;
		};

		void uninit();

		namespace _ {
			extern std::list<Node*> key_down_registry;
			extern std::list<Node*> key_up_registry;
		}
	} 
}
