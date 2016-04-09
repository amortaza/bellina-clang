#pragma once

#include "Xel/Xel_Mouse.h"

namespace bl {
	namespace ui {
		void onMouseMove(int mx, int my);
		void onMouseScroll(int amount);
		void onMouseButton(Xel::Mouse::Button button, Xel::Mouse::Action action, int x, int y);

		void onKeyDown(unsigned long long xcode);
		void onKeyUp(unsigned long long xcode);

		void onResize(int w, int h);
	}
}

