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

	int dx = 0, dy = 0;
	int lastMx = 0, lastMy = 0;
	int startMx = 0, startMy = 0;
	int deltaX = 0, deltaY = 0;
}

namespace mouse_drag {
	void load();

	void freeId() {
		if (dragNodeId) {
			delete[] dragNodeId;
			dragNodeId = 0;
		}
	}	

	void fire(Node* node, int mx, int my, int dx, int dy, int deltaX, int deltaY) {

		MouseDragEvent event;
		event.node = node;
		event.mx = mx;
		event.my = my;
		event.dx = dx;
		event.dy = dy;
		event.deltaX = deltaX;
		event.deltaY = deltaY;

		bl::pluginCall(plugin_name, node, &event);
	}

	void init() {
		bl::listenLongTerm("mouse-up", [](void* e) {
			MouseUpEvent* event = (MouseUpEvent*)e;
			freeId();
		});

		// we need long term because drag requires apturing mouse
		// otherwise "resize" will not work when going over neighboring nodes
		bl::listenLongTerm("mouse-move", [](void* e) {
			MouseMoveEvent* event = (MouseMoveEvent*)e;
			
			if (dragNodeId) {
				Node* dragNode = util::getNodeById(dragNodeId);

				if (!dragNode) {
					freeId();
					return;
				}

				int mx = event->mx;
				int my = event->my;

				int deltaX = mx - lastMx;
				int deltaY = my - lastMy;

				lastMx = mx; lastMy = my;

				fire(dragNode, mx, my, dx, dy, deltaX, deltaY);
			}
		});
	}

	void uninit() { freeId(); }

	void onNode() {

		bl::onMouseDown([](Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (bubbledFrom) return true; // if this from a bubble, leave it alone.  pass it along.
										   
			freeId();

			dragNodeId = _strdup(bl::node->nid);

			dx = bl::node->x - mx;
			dy = bl::node->y - my;

			lastMx = mx; lastMy = my;
			startMx = mx; startMy = my;

			return false;
		});
	}
}

void mouse_drag::load() {
	bl::pluginLoad(click::load);

	bl::pluginRegister(	
		mouse_drag::plugin_name, 
		mouse_drag::init,
		mouse_drag::onNode,
		nullptr, 
		mouse_drag::uninit);
}