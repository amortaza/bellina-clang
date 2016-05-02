#include "stdafx.h"

#include "bellina/bellina.h"

#include "../mouse-drag/mouse-drag.h"

#include "resize.h"
#include "ResizeContext.h"

using namespace bl;

namespace resize {
	char* plugin_name = "resize";	

	void onNode(char* signature, PluginCtxFactory factory) {
		
		bl::pluginCtxOnNode(plugin_name, "default", [] () {
			return new ResizeContext();
		});
	}
}

void resize::load() {
	bl::pluginLoad(mouse_drag::load);

	bl::pluginRegister(
		resize::plugin_name,
		nullptr,
		resize::onNode,
		nullptr);
}