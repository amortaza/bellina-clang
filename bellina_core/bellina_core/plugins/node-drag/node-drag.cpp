#include "stdafx.h"

#include "bellina/bellina.h"

#include "../mouse-drag/mouse-drag.h"

#include "node-drag.h"
#include "NodeDragPlugin.h"

using namespace bl;
using namespace bl::listener;
using namespace mouse_drag;
using namespace std;

namespace node_drag {

	char* plugin_name = "node-drag";

	void load();	

	void onNode() {

		Node* shadow = get_shadow();
		NodeDragPlugin* nodeDragPlugin = (NodeDragPlugin*) shadow->getPlugin(plugin_name);

		if (!nodeDragPlugin) {
			nodeDragPlugin = new NodeDragPlugin();
			shadow->addPlugin(plugin_name, nodeDragPlugin);
		}

		nodeDragPlugin->onNode();
	}
}

void node_drag::load() {
	bl::pluginLoad(mouse_drag::load);

	bl::pluginRegister(
		node_drag::plugin_name,
		nullptr,
		node_drag::onNode,
		nullptr);
}
