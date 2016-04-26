#pragma once

namespace resize {
	class ResizeContext {
	private:
		int newW = 0, newH = 0;

	public:
		void onNode() {
			bl::shadow([](Node* shadow) {
				ResizeContext* This = (ResizeContext*)shadow->getPlugin(plugin_name, []() {
					return new ResizeContext();
				});

				if (This->newW > 0 && This->newH > 0) {
					if (This->newW > 16 && This->newH > 16) {
						shadow->w = This->newW;
						shadow->h = This->newH;

						// rintf("%i %i\n", newW, newH);
					}

					This->newW = This->newH = 0;
				}
			});

			bl::on("mouse-drag", [](void* e) {
				mouse_drag::MouseDragEvent* event = (mouse_drag::MouseDragEvent*) e;

				ResizeContext* This = (ResizeContext*)event->node->getPluginFromShadow(resize::plugin_name, nullptr);

				This->newW = event->node->w + event->deltaX;
				This->newH = event->node->h + event->deltaY;

				resize::ResizeEvent e2;
				e2.w = This->newW;
				e2.h = This->newH;
				e2.node = event->node;

				bl::pluginCall(plugin_name, event->node, &e2);
				bl::fire(plugin_name, &e2);

				return true;
			});
		}
	};
}