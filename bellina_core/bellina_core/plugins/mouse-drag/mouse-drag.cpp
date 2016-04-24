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
	void load();

	char* dragNodeId = 0;

	int dx = 0, dy = 0;	
	int lastMx = 0, lastMy = 0;

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
		bl::listenLongTerm("mouse up", [](void* e) {
			MouseUpEvent* event = (MouseUpEvent*)e;
			freeId();
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

			return false;
		});

		bl::onMouseMove([](int mx, int my, Node* bubbledFrom) {
			if (!dragNodeId) return false;

			if (util::isNode(bl::node, dragNodeId)) {
				int deltaX = mx - lastMx;
				int deltaY = my - lastMy;

				lastMx = mx; lastMy = my;
				
				fire(bl::node, mx, my, dx, dy, deltaX, deltaY);
			}

			return false;
		});
	}
}

void mouse_drag::load() {
	bl::pluginRegister(	
		mouse_drag::plugin_name, 
		mouse_drag::init,
		mouse_drag::onNode,
		nullptr, 
		mouse_drag::uninit);
}