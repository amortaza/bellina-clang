#pragma once

#include "bellina/BasePlugin.h"

using namespace bl;

namespace node_drag {

	class NodeDragPlugin : public BasePlugin {

	public:
		bool hasData = false;
		int newX = 0, newY = 0;

	public:
		NodeDragPlugin() {
			printf("NodeDragPlugin\n");
		}

		~NodeDragPlugin() {
			printf("~NodeDragPlugin\n");
		}

		void onNode() {
			bl::shadow([](Node* shadow) {
				NodeDragPlugin* This = (NodeDragPlugin*)shadow->getPlugin(plugin_name);

				if (This->hasData) {
					shadow->x = This->newX;
					shadow->y = This->newY;
					This->hasData = false;
				}
			});

			bl::on("mouse-drag", [](void *e) {
				mouse_drag::MouseDragEvent* event = (mouse_drag::MouseDragEvent*) e;

				NodeDragPlugin* This = (NodeDragPlugin*)event->node->getPluginFromShadow(node_drag::plugin_name);

				if (event->button != Xel::Mouse::Button::Left) return false;

				This->newX = bl::sys::mouse_x + event->relativeX;
				This->newY = bl::sys::mouse_y + event->relativeY;
				This->hasData = true;

				NodeDragEvent nde;
				nde.mx = bl::sys::mouse_x;
				nde.my = bl::sys::mouse_y;
				nde.node = event->node;
				nde.relativeX = event->relativeX;
				nde.relativeY = event->relativeY;

				bl::pluginCall(plugin_name, event->node, &nde);
				bl::fire(plugin_name, &nde);

				return false;
			});
		}
	};
}