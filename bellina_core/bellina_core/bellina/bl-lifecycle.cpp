#include "stdafx.h"

#include "g2/g2.h"

#include "eos/eos.h"

#include "bl-util.h"
#include "bl-globals.h"
#include "bl-core.h"
#include "bl-flags.h"
#include "bl-listener.h"
#include "bl-echo.h"
#include "bl-plugin-bubble.h"
#include "bl-lifecycle.h"

using namespace g2::flags;

using namespace bl;
using namespace bl::_;
using namespace bl::flags;
using namespace bl::echo;

void lifecycle::tickBeforeCoreRender() {	

	// delete after the plugin ticks, so nodes have chance to react
	delete short_term_echo;
	short_term_echo = new Echo();

	delete pluginBubble; 
	pluginBubble = new PluginBubble();

	nodeById.clear();

	next_global_id = 0;

	if (root_node) { delete root_node; root_node = 0; }
}

void bl::paint() {
	if (!root_node) return;

	plugin::tickAfterCoreRender();

	int winW = Xel::Window::width;
	int winH = Xel::Window::height;

	bl::util::calcGlobalPositions();

	root_node->dim(winW, winH);

	g2::viewport(winW, winH);
	g2::ortho(winW, winH);

	g2::clear();

	eos::render(root_node);

	g2::texture(root_node->canvas);
	g2::rectFlipped(G2_TEXTURE, 0, 0, winW, winH);

	if (root_node->label_ && root_node->label_tops_canvas) {
		eos::_::renderLabel(root_node, 0, 0);
	}

	if (root_node->flags & BL_BORDER_ANY) {
		eos::_::renderBorder(root_node, true, 0, 0);
	}
}
