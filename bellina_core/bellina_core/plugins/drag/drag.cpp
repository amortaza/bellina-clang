#include "stdafx.h"

#include "bellina/bellina.h"

#include "../click/click.h"

#include "drag.h"

using namespace bl;
using namespace bl::listener;
using namespace click;
using namespace std;

map<string, Node *> pluginNodes;

namespace drag {

	char* plugin_name = "drag";
	char* clickNodeId = 0;
	Node* pnode = 0;

	int dx = 0, dy = 0;

	Node* getPluginNode(Node* node) {
		Node* pnode = 0;
		string key(node->nid);

		auto e2 = pluginNodes.find(key);
		if (e2 == pluginNodes.end()) {
			pnode = new Node(0);
			pnode->x = node->x;
			pnode->y = node->y;
			pluginNodes[key] = pnode;
		}
		else {
			pnode = e2->second;
		}

		return pnode;
	}

	void setNodeFromPluginNode(Node* node, Node* pnode) {
		node->x = pnode->x;
		node->y = pnode->y;
	}

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
				printf("releasing drag\n");
				freeId();
			}
		});
	}

	void uninit() { freeId(); }

	void tickOnAfterCoreRender() {
	}
	
	void onNode(PluginCallback cb) {

		pnode = getPluginNode(_::current_node);

		setNodeFromPluginNode(_::current_node, pnode);

		if (clickNodeId && bl::util::isNode(_::current_node, clickNodeId)) {
			pnode->x = bl::sys::mouse_x +dx;
			pnode->y = bl::sys::mouse_y +dy;
		}

		bl::onMouseDown([](Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (bubbledFrom) return true; // if this from a bubble, leave it alone.  pass it along.

										  // 
			freeId();

			clickNodeId = _strdup(bl::node->nid);

			dx = bl::node->x - mx;
			dy = bl::node->y - my;

			return false;
		});

		
		/*bl::onMouseMove([](int mx, int my, Node* bubbledFrom) {
			printf("%i %i\n",mx,my);
			if (bubbledFrom) return true; // if this from a bubble, leave it alone.  pass it along.

			if (clickNodeId && bl::util::isNode(bl::node, clickNodeId)) {
		
				pnode->x = mx;
				pnode->y = my;
				
				//printf("dragging from plugin %s : frame %i, x=%i\n", bl::node->nid,frame++, bl::node->x);
			}
		});*/

		bl::onMouseUp([](Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			if (bubbledFrom) return true; // if this from a bubble, leave it alone.  pass it along.
										  
			freeId();

			return false;
		});
	}
}