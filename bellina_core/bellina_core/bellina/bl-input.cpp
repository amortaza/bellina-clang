#include "stdafx.h"

#include "bl-input.h"
#include "bl-pump.h"

using namespace bl;

void input::onMouseMove(int mx, int my) {
	pump::onMouseMove(mx, my);
}

void input::onMouseScroll(int amount) {
	pump::onMouseScroll(amount);
}

void input::onMouseButton(Xel::Mouse::Button button, Xel::Mouse::Action action, int mx, int my) {
	pump::onMouseButton(button, action, mx, my);
}

void bl::input::onKeyDown(unsigned long long xcode) {
	pump::onKeyDown(xcode);
}

void bl::input::onKeyUp(unsigned long long xcode) {
	pump::onKeyUp(xcode);
}
