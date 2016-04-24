#include "stdafx.h"

#include "bellina/bellina.h"

#include "../click/click.h"

#include "drag.h"

using namespace bl;
using namespace bl::listener;
using namespace click;
using namespace std;

namespace drag {

	char* plugin_name = "drag";
	char* clickNodeId = 0;

	int dx = 0, dy = 0;

	void freeId() {
		if (clickNodeId) {
			delete[] clickNodeId;
			clickNodeId = 0;
		}
	}	

	void init() {
		bl::listenLongTerm("mouse up", [](void* e) {
			MouseUpEvent* event = (MouseUpEvent*)e;

			if (clickNodeId) {
				freeId();
			}
		});
	}

	void uninit() { freeId(); }

	void tickOnAfterCoreRender() {
	}
	
	void onNode() {

		bl::shadow([](Node* shadow) {
			if (clickNodeId && bl::util::isNode(_::current_node, clickNodeId)) {
				shadow->x = bl::sys::mouse_x + dx;
				shadow->y = bl::sys::mouse_y + dy;
			}
		});

		bl::onMouseDown([](Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (bubbledFrom) return true; // if this from a bubble, leave it alone.  pass it along.
										  // 
			freeId();

			clickNodeId = _strdup(bl::node->nid);

			dx = bl::node->x - mx;
			dy = bl::node->y - my;

			// printf("dx dy %i %i\n", dx, dy);

			return false;
		});
	}
}