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

	void on_node(char* signature, PluginCtxFactory factory) {
		bl::pluginCtxOnNode(plugin_name, signature, factory);
	}

	NodeDragContext* default_factory() {
		return new NodeDragContext();
	}
}

void node_drag::load() {
	bl::pluginLoad(mouse_drag::load);

	bl::pluginRegister(
		node_drag::plugin_name,
		nullptr,
		node_drag::default_factory,
		node_drag::on_node,
		nullptr);
}
