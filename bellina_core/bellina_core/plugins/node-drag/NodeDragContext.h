#pragma once

using namespace bl;

namespace node_drag {	

	class NodeDragContext : public BasePluginCtx {

	public:
		bool hasData = false;
		int newX = 0, newY = 0;

	public:

		NodeDragContext() : BasePluginCtx("default") {}

		// does not need signature or factory cause "this" already exits...
		void pluginOnNode() {
			
			NodeDragContext* This = this;

			bl::shadow([This] (ShadowNode* shadow) {
				if (This->hasData) {
					shadow->x = This->newX;
					shadow->y = This->newY;
					This->hasData = false;
				}
			});

			bl::on("mouse-drag", [This] (void *e) {
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

				bl::pluginCall(plugin_name, "default", event->node, &nde);
				bl::fire(plugin_name, &nde);

				return false;
			});
		}
	};
}