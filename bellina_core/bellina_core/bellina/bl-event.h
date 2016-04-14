#pragma once

#include "Xel/Xel.h"

namespace bl { extern class Node; }

namespace bl { 
	namespace event {

		struct KeyUpEvent {
			unsigned long long xcode;
			Node* node;
		};

		struct KeyDownEvent {
			unsigned long long xcode;
			Node* node;
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

		void uninit();
	} 
}
