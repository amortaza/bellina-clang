#include "stdafx.h"

#include "bellina/bellina.h"

#include "../click/click.h"

#include "mouse-drag.h"

using namespace bl;
using namespace bl::listener;
using namespace click;
using namespace std;

namespace mouse_drag {
	char* plugin_name = "mouse-drag";

	char* dragNodeId = 0;

	int relativeX = 0, relativeY = 0;
	int lastMx = 0, lastMy = 0;
	int startMx = 0, startMy = 0;
	int deltaX = 0, deltaY = 0;

	Xel::Mouse::Button lastButton;
}

namespace mouse_drag {
	void load();

	void freeId() {
		if (dragNodeId) {
			delete[] dragNodeId;
			dragNodeId = 0;
		}
	}	

	void fire(Node* node, int mx, int my, int relativeX, int relativeY, int deltaX, int deltaY) {

		MouseDragEvent event;
		event.node = node;
		event.mx = mx;
		event.my = my;
		event.relativeX = relativeX;
		event.relativeY = relativeY;
		event.deltaX = deltaX;
		event.deltaY = deltaY;
		event.button = lastButton;
		//rintf("firing\n");
		bl::pluginCall(plugin_name, "default", "default", node, &event);
		bl::fire(plugin_name, &event);
	}

	void init() {

		bl::listenLongTerm("mouse-up", [] (void* e) {
			MouseUpEvent* event = (MouseUpEvent*)e;
			freeId();
		});

		// we need long term because drag requires apturing mouse
		// otherwise "resize" will not work when going over neighboring nodes
		bl::listenLongTerm("mouse-move", [] (void* e) {
			MouseMoveEvent* event = (MouseMoveEvent*)e;

			if (dragNodeId) {
				Node* dragNode = bl::util::getNodeById(dragNodeId);

				if (!dragNode) {
					freeId();
					
					return;
				}

				int mx = event->mx;
				int my = event->my;

				int deltaX = mx - lastMx;
				int deltaY = my - lastMy;

				lastMx = mx; lastMy = my;
				
				fire(dragNode, mx, my, relativeX, relativeY, deltaX, deltaY);
			}
		});
	}

	void uninit() { freeId(); }

	void on_node(char* signature, PluginCtxFactory factory) {

		bl::onMouseDown([] (Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (bubbledFrom) return true; // if this from a bubble, leave it alone.  pass it along.
										   
			freeId();

			lastButton = button;

			dragNodeId = _strdup(bl::node->nid);

			relativeX = bl::node->x - mx;
			relativeY = bl::node->y - my;

			lastMx = mx; lastMy = my;
			startMx = mx; startMy = my;

			//rintf("mouse-drag: mouse down\n");

			return false;
		});
	}
}

void mouse_drag::load() {
	pango::load(click::load);

	pango::registerPlugin(
		mouse_drag::plugin_name, 
		mouse_drag::init,
		nullptr,
		mouse_drag::on_node,
		mouse_drag::uninit);
}