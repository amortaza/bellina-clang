#include "stdafx.h"

#include "bl-mouse.h"
#include "bl-pump.h"

using namespace bl;
using namespace bl::pump;

namespace bl {
	namespace pump {
		bool mouseMoved = false;
		bool mouseScrolled = false;
		bool mouseButtoned = false;

		int mx, my;
		int scrollAmount;

		Xel::Mouse::Button button;
		Xel::Mouse::Action action;
	}
}

void pump::send() {
	if (mouseMoved) {
		mouseMoved = false;

		mouse::updateSysMouse(mx, my);

		mouse::bl_onMouseMove(mx, my);
	}

	if (mouseScrolled) {
		mouseScrolled = false;

		mouse::bl_onMouseScroll(scrollAmount);
	}

	if (mouseButtoned) {
		mouseButtoned = false;

		mouse::updateSysMouse(mx, my);

		mouse::bl_onMouseButton(button, action, mx, my);
	}
}

void pump::onMouseMove(int mx, int my) {
	mouseMoved = true;

	pump::mx = mx;
	pump::my = my;
}

void pump::onMouseScroll(int amount) {
	mouseScrolled = true;

	pump::scrollAmount = amount;
}

void pump::onMouseButton(Xel::Mouse::Button button, Xel::Mouse::Action action, int mx, int my) {
	mouseButtoned = true;

	pump::mx = mx;
	pump::my = my;

	pump::button = button;
	pump::action = action;
}


