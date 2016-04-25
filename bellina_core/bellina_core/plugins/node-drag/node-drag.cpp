#include "stdafx.h"

#include "bellina/bellina.h"

#include "../mouse-drag/mouse-drag.h"

#include "node-drag.h"

using namespace bl;
using namespace bl::listener;
using namespace mouse_drag;
using namespace std;

namespace node_drag {

	char* plugin_name = "node-drag";

	void load();

	bool hasData = false;
	int newX = 0, newY = 0;

	void onNode() {

		bl::shadow([](Node* shadow) {
			if (hasData) {
				shadow->x = newX;
				shadow->y = newY;
				hasData = false;
			}
		});

		bl::on("mouse-drag", [](void *e) {
			mouse_drag::MouseDragEvent* event = (mouse_drag::MouseDragEvent*) e;

			newX = bl::sys::mouse_x + event->relativeX;
			newY = bl::sys::mouse_y + event->relativeY;
			hasData = true;

			return false;
		});
	}
}

void node_drag::load() {
	bl::pluginLoad(mouse_drag::load);

	bl::pluginRegister(
		node_drag::plugin_name,
		nullptr,
		node_drag::onNode,
		nullptr);
}
