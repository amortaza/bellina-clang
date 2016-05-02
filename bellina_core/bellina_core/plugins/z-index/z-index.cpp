#include "stdafx.h"

#include "bellina/bellina.h"

#include "z-index.h"
#include "order-info.h"
#include "ZIndexCtx.h"

using namespace z_index;

namespace z_index {
	char* plugin_name = "z-index";
}

void z_index::on_node(char* signature, PluginCtxFactory factory) {
	bl::pluginCtxOnNode(plugin_name, signature, factory);
}

ZIndexCtx* z_index::default_factory() {
	return new ZIndexCtx();
}

void z_index::load() {
	bl::pluginRegister(	z_index::plugin_name, 
						nullptr, 
						z_index::default_factory,
						z_index::on_node,
						nullptr);
}