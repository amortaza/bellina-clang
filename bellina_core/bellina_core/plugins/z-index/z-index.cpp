#include "stdafx.h"

#include "bellina/bellina.h"

#include "z-index.h"
#include "order-info.h"
#include "ZIndexContext.h"

using namespace z_index;

namespace z_index {
	char* plugin_name = "z-index";
}

void z_index::onNode(char* signature, PluginCtxFactory factory) {
	/*todo bl::pluginCtxOnNode(plugin_name, "default", [] () {
		return new ZIndexContext("default");
	});*/
}

void z_index::load() {
	bl::pluginRegister(	z_index::plugin_name, 
						nullptr, 
						z_index::onNode, 
						nullptr);
}