#include "stdafx.h"

#include "bl-core.h"
#include "bl-mouse.h"
#include "bl-pump.h"
#include "bl-listener.h"

using namespace bl;
using namespace bl::pump;
using namespace bl::listener;

namespace bl {
	namespace pump {
		bool mouseMoved = false;
		bool mouseScrolled = false;
		bool mouseButtoned = false;

		bool keyUpped = false;
		bool keyDowned = false;

		int mx, my;
		int scrollAmount;

		Xel::Mouse::Button button;
		Xel::Mouse::Action action;

		unsigned long long xcode;
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

	if (keyDowned) {
		keyDowned = false;

		KeyDownEvent event;
		event.xcode = xcode;

		bl::fire("key-down", &event);
	}

	if (keyUpped) {
		keyUpped = false;

		KeyDownEvent event;
		event.xcode = xcode;

		bl::fire("key-up", &event);
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
	if (mouseButtoned) printf("!!!!!!!!!!!!!!!!!!!!! Mouse button up an down running into each other in onMouseButton\n");

	mouseButtoned = true;

	pump::mx = mx;
	pump::my = my;

	pump::button = button;
	pump::action = action;
}

void pump::onKeyUp(unsigned long long xcode) {
	if (keyDowned) printf("!!!!!!!!!!!!!!!!!!!!! Key up and down are running into each other in onKeyUp\n");

	keyUpped = true;

	pump::xcode = xcode;
}

void pump::onKeyDown(unsigned long long xcode) {
	if (keyUpped) printf("!!!!!!!!!!!!!!!!!!!!! Key up and down are running into each other in onKeyDown\n");

	keyDowned = true;

	pump::xcode = xcode;
}

