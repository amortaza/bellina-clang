#include "stdafx.h"

#include "bellina/bellina.h"

#include "../mouse-drag/mouse-drag.h"

#include "resize.h"
#include "ResizeContext.h"

using namespace bl;

namespace resize {
	char* plugin_name = "resize";	

	void on_node(char* signature, PluginCtxFactory factory) {
		bl::pluginCtxOnNode(plugin_name, signature, factory);
	}

	ResizeContext* default_factory() {
		return new ResizeContext();
	}
}

void resize::load() {
	bl::pluginLoad(mouse_drag::load);

	bl::pluginRegister(
		resize::plugin_name,
		nullptr,
		resize::default_factory,
		resize::on_node,
		nullptr);
}