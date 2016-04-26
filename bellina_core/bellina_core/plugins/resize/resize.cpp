#include "stdafx.h"

#include "bellina/bellina.h"

#include "../mouse-drag/mouse-drag.h"

#include "resize.h"
#include "ResizeContext.h"

using namespace bl;
using namespace bl::listener;

namespace resize {
	char* plugin_name = "resize";	

	void onNode() {
		ResizeContext* resizeCtx = (ResizeContext*)bl::current()->getPluginFromShadow(plugin_name, []() {
			return new ResizeContext();
		});

		resizeCtx->onNode();
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