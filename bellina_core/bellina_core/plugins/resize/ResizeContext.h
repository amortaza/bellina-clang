#pragma once

#include "bellina/BasePluginCtx.h"

namespace resize {
	class ResizeContext : public BasePluginCtx {

	private:
		int newW = 0, newH = 0;

	public:
		ResizeContext() : BasePluginCtx("default") {}

		// does not need signature or factory cause "this" already exits...
		void pluginOnNode() {
			
			ResizeContext* This = this;

			bl::shadow([This] (ShadowNode* shadow) {

				if (This->newW > 0 && This->newH > 0) {
					if (This->newW > 16 && This->newH > 16) {
						shadow->w = This->newW;
						shadow->h = This->newH;
					}

					This->newW = This->newH = 0;
				}
			});

			bl::on("mouse-drag", [This] (void* e) {
				mouse_drag::MouseDragEvent* event = (mouse_drag::MouseDragEvent*) e;

				This->newW = event->node->w + event->deltaX;
				This->newH = event->node->h + event->deltaY;

				resize::ResizeEvent e2;
				e2.w = This->newW;
				e2.h = This->newH;
				e2.node = event->node;

				bl::pluginCall(plugin_name, "default", event->node, &e2);
				bl::fire(plugin_name, &e2);

				return true;
			});
		}
	};
}