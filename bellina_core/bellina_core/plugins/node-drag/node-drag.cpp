#include "stdafx.h"

#include "bellina/bellina.h"

#include "../mouse-drag/mouse-drag.h"

#include "node-drag.h"
#include "NodeDragContext.h"

using namespace bl;
using namespace bl::listener;
using namespace mouse_drag;
using namespace std;

namespace node_drag {

	char* plugin_name = "node-drag";	

	void load();	

	void onNode(char* signature, PluginCtxFactory factory) {

		/*todo bl::pluginCtxOnNode(plugin_name, "default", [] () {
			return new NodeDragContext();
		});*/
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
