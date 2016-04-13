#include "stdafx.h"

#include "eos/eos.h"

#include "bl-extern.h"
#include "bl-core.h"

using namespace g2::flags;

using namespace bl;
using namespace bl::_;
using namespace bl::flags;

void bl::paint() {
	if (!root) return;

	int winW = Xel::Window::width;
	int winH = Xel::Window::height;

	bl::util::calcGlobalPositions();

	root->dim(winW, winH);

	g2::viewport(winW, winH);
	g2::ortho(winW, winH);

	g2::clear();

	eos::render(root);

	g2::texture(root->canvas);
	g2::rectFlipped(G2_TEXTURE, 0, 0, winW, winH);

	if (root->label_ && root->label_tops_canvas) {
		eos::_::renderLabel(root, 0, 0);
	}

	if (root->flags & BL_BORDER_ANY) {
		eos::_::renderBorder(root, true, 0, 0);
	}
}
