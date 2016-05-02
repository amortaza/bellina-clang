#include "stdafx.h"

#include "bellina/bellina.h"

#include "mouse-in.h"

using namespace bl;
using namespace bl::listener;

namespace mouse_in {
	char* plugin_name = "mouse-in";

	char* lastNodeId = 0;

	void freeId() {
		if (lastNodeId) {
			delete [] lastNodeId;
			lastNodeId = 0;
		}
	}

	void fire(char* outId, char* inId, int mx, int my) {
		Node* out = bl::util::getNodeById(outId);
		Node* in = bl::util::getNodeById(inId);

		MouseInOutEvent event;
		event.inNode = in;
		event.outNode = out;
		event.mx = mx;
		event.my = my;

		if (in) {
			event.isInEvent = true;
			bl::pluginCall(plugin_name, "mouse-in", in, &event);			
		}

		if (out) {
			event.isInEvent = false;
			bl::pluginCall(plugin_name, "mouse-in", out, &event);
		}

		// note that event.isInEvent is non-sensical here
		if (in || out ) bl::fire(plugin_name, &event);
	}
	
	void init() {
		bl::listenLongTerm("mouse-move", [] (void* e) {
			MouseMoveEvent* event = (MouseMoveEvent*)e;

			Node* This = event->node;
			int mx = event->mx;
			int my = event->my;

			if (lastNodeId) {
				if (bl::util::isNode(This, lastNodeId)) {
					// same node...move along...nothing interesting is happening
				}
				else {
					// we went from a node to a node
					
					// rintf("%s\n", "****************************");
					// rintf("from %s to %s\n", lastNodeId, This->nid);
					fire(lastNodeId, This->nid, mx, my);
					// rintf("%s\n","****************************");

					freeId();
					lastNodeId = _strdup(This->nid);
				}
			}
			else {
				// went from no node to a node
				fire(0, This->nid, mx, my);

				freeId();
				lastNodeId = _strdup(This->nid);
			}
		});
	}

	void uninit() {
		freeId();
	}

}

void mouse_in::load() {
	bl::pluginRegister(
		mouse_in::plugin_name,
		mouse_in::init,
		nullptr,
		nullptr,
		mouse_in::uninit);
}