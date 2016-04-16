#include "stdafx.h"

#include "bl-input.h"
#include "bl-listener.h"
#include "bl-core.h"

using namespace bl;
using namespace bl::input;
using namespace bl::listener;


void bl::input::onKeyDown(unsigned long long xcode) {
	KeyDownEvent event;
	event.xcode = xcode;

	bl::fire("key down", &event);
}

void bl::input::onKeyUp(unsigned long long xcode) {
	KeyDownEvent event;
	event.xcode = xcode;

	bl::fire("key up", &event);
}
