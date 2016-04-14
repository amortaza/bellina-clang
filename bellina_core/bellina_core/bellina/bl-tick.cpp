#include "stdafx.h"

#include "eos/eos.h"

#include "bl-util.h"
#include "bl-extern.h"
#include "bl-core.h"
#include "bl-flags.h"
#include "bl-event.h"

using namespace g2::flags;

using namespace bl;
using namespace bl::_;
using namespace bl::flags;
using namespace bl::event::_;

void bl::tick() {
	key_down_registry.clear();
	key_up_registry.clear();

	bl::plug::tick();

	if (!root_node) return;

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
