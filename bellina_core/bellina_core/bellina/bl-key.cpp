#include "stdafx.h"

/*#include "bl-node.h"
#include "bl-globals.h"
#include "bl-input.h"
#include "bl-sys.h"
#include "bl-listener.h"
#include "bl-core.h"

using namespace bl;
using namespace bl::_;
using namespace bl::input;
using namespace bl::listener;
using namespace bl::listener::_;
*/

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
