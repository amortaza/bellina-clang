#include "stdafx.h"

#include "bellina/bellina.h"

#include "../mouse-drag/mouse-drag.h"

#include "resize.h"

using namespace bl;
using namespace bl::listener;

namespace resize {
	char* plugin_name = "resize";

	void init() {}

	void uninit() {}

	int newW = 0, newH = 0;

	void onNode() {
		bl::shadow([](Node* shadow) {
			if (newW > 0 && newH > 0) {
				if (newW > 16 && newH > 16) {
					shadow->w = newW;
					shadow->h = newH;

					printf("%i %i\n", newW, newH);
				}

				newW = newH = 0;
			}
		});

		bl::on("mouse-drag", [](void* e) {
			mouse_drag::MouseDragEvent* event = (mouse_drag::MouseDragEvent*) e;

			newW = event->node->w + event->deltaX;
			newH = event->node->h + event->deltaY;
			
			//printf("%i %i\n", event->deltaX, event->deltaY);

			return true;
		});
	}
}

void resize::load() {
	bl::pluginLoad(mouse_drag::load);

	bl::pluginRegister(
		resize::plugin_name,
		resize::init,
		resize::onNode,
		nullptr, 
		resize::uninit);
}