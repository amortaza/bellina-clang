#include "stdafx.h"

#include "bellina/bellina.h"

#include "click.h"
#include "plugins/mouse-in/mouse-in.h"

using namespace bl;
using namespace bl::listener;

namespace click {
	char* plugin_name = "click";

	namespace lifecycle {
		char* default = "default";
		char* mouse_in = "mouse-in";
		char* mouse_out = "mouse-out";
		char* mouse_down = "mouse-down";
		char* mouse_drag = "mouse-drag";
		char* mouse_up_and_no_click = "mouse-up-no-click";
	}

	char* lastDownNodeId = 0;
	Xel::Mouse::Button lastDownButton;

	void freeId() {
		if (lastDownNodeId) {
			delete [] lastDownNodeId;
			lastDownNodeId = 0;
		}
	}

	void init() {
		bl::listenLongTerm("mouse-down", [] (void* data) {
			MouseDownEvent* event = (MouseDownEvent*)data;

			if (lastDownNodeId && !bl::util::isNode(event->node, lastDownNodeId) ) {
				freeId();
			}
		});

		bl::listenLongTerm("mouse-up", [] (void* data) {
			MouseDownEvent* inevent = (MouseDownEvent*)data;
			
			if (lastDownNodeId && !bl::util::isNode(inevent->node, lastDownNodeId)) {
				MouseClickEvent event;
				event.mx = inevent->mx;
				event.my = inevent->my;
				event.button = inevent->button;
				event.node = inevent->node;

				Node* green = util::getNodeById(lastDownNodeId);

				bl::pluginCall(plugin_name, "default", lifecycle::mouse_up_and_no_click, green, &event);

				freeId();
			}
		});
	}

	void uninit() {
		freeId();
	}

	void on_node(char* signature, PluginCtxFactory factory) {

		/*bl::on("mouse-in", [](void* data) {
			/*mouse_in::MouseInOutEvent* event = (mouse_in::MouseInOutEvent*) data;

			if (event->isInEvent) printf("click in\n");
			else
				printf("click out\n");

			return false;
		});*/

		bl::onMouseDown([] (Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (lastDownNodeId) delete[] lastDownNodeId;

			lastDownNodeId = _strdup(bl::node->nid);
			lastDownButton = button;

			MouseClickEvent event;
			event.mx = mx;
			event.my = my;
			event.button = button;
			event.node = bl::node;

			//rintf("onmousedown\n");

			bl::pluginCall(plugin_name, "default", lifecycle::mouse_down, bl::node, &event);

			return true;
		});
		
		bl::onMouseUp([] (Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			
			MouseClickEvent event;
			event.mx = mx;
			event.my = my;
			event.button = button;
			event.node = bl::node;

			if (bl::util::isNode(bl::node, lastDownNodeId ) && button == lastDownButton ) {

				//printf("mouse up getting called for signature %s\n", signature);
				bl::pluginCall(plugin_name, "default", lifecycle::default, bl::node, &event);
				bl::fire(plugin_name, &event);
			}
			else {
				bl::pluginCall(plugin_name, "default", lifecycle::mouse_up_and_no_click, bl::node, &event);
			}

			freeId();

			return true;
		});
	}
}

void click::load() {
	pango::registerPlugin(
		click::plugin_name, 
		click::init, 
		nullptr,
		click::on_node,
		click::uninit);
}