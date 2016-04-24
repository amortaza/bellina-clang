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
	printf("input-mouse button\n");
	pump::onMouseButton(button, action, mx, my);
}
