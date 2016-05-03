#include "stdafx.h"

#include "bellina/bellina.h"

#include "../mouse-drag/mouse-drag.h"

#include "resize.h"
#include "ResizeCtx.h"

using namespace bl;

namespace resize {
	char* plugin_name = "resize";	

	void on_node(char* signature, PluginCtxFactory factory) {
		bl::pluginCtxOnNode(plugin_name, signature, factory);
	}

	ResizeCtx* default_factory() {
		return new ResizeCtx();
	}
}

void resize::load() {
	pango::load(mouse_drag::load);

	pango::registerPlugin(
		resize::plugin_name,
		nullptr,
		resize::default_factory,
		resize::on_node,
		nullptr);
}