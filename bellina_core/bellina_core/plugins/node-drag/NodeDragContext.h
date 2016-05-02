#pragma once

using namespace bl;

namespace node_drag {	

	class NodeDragContext : public BasePluginCtx {

	public:
		bool hasData = false;
		int newX = 0, newY = 0;

	public:

		NodeDragContext(char* signature) : BasePluginCtx(signature) {

		}

		void onNode() {
			
			NodeDragContext* This = this;

			bl::shadow([This](ShadowNode* shadow) {
				if (This->hasData) {
					shadow->x = This->newX;
					shadow->y = This->newY;
					This->hasData = false;
				}
			});

			char* signature = _signature;

			bl::on("mouse-drag", _signature, [This, signature](void *e) {
				mouse_drag::MouseDragEvent* event = (mouse_drag::MouseDragEvent*) e;

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

				bl::pluginCall(plugin_name, signature, event->node, &nde);
				bl::fire(plugin_name, &nde);

				return false;
			});
		}
	};
}