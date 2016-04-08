#include "stdafx.h"
#include <list>

#include "g2/g2.h"

#include "bl-render.h"
#include "bl-extern.h"
#include "bl-core.h"

using namespace bl;
using namespace bl::Internal;

using namespace g2::flags;

void _renderLabel(Node *node, int dx, int dy) {
	g2::color(node->font_red, node->font_green, node->font_blue);
	g2::font(node->font_name, node->font_size);

	if (node->flags_ & G2_PAD)
		g2::text(dx + node->padding_left, dy + node->padding_top + node->fontHeight, node->label_, node->font_alpha);
	else
		g2::text(dx, dy + node->fontHeight, node->label_, node->font_alpha);
}

void bl::paint() {
	int winW = Xel::Window::width;
	int winH = Xel::Window::height;

	root->dim(winW, winH);

	g2::viewport(winW, winH);
	g2::ortho(winW, winH);

	g2::clear();

	bl::render(root);

	g2::texture(root->canvas);
	g2::rectFlipped(G2_TEXTURE, 0, 0, winW, winH);

	if (root->label_ && root->label_tops_canvas) {
		_renderLabel(root,0,0);
	}

	if (root->border_tops_canvas && (root->flags_ & G2_BORDER_ANY)) {
		g2::color(root->border_red, root->border_green, root->border_blue);
		g2::border(root->flags_, 0, 0, root->w, root->h, root->border_thickness, root->border_alpha);
	}

}

void bl::render(Node *node) {
	g2::paintCanvas(node->canvas);
	{
		if (node->flags_ & G2_COLOR_ANY) {
			g2::color(node->r1, node->g1, node->b1);
			g2::color2(node->r2, node->g2, node->b2);
		}

		if (node->flags_ & G2_TEXTURE) {
			g2::texture(node->texture_);
		}

		if (node->flags_ & G2_MASK) {
			g2::mask(node->mask_);
		}

		if (node->flags_ & G2_PAD) {
			g2::padding(node->padding_left, node->padding_top, node->padding_right, node->padding_bottom);
		}

		// we are in canvas, so x, y is 0,0
		g2::rect(node->flags_, 0, 0, node->w, node->h);

		// ---------------------------------------------------------------------
		if (node->label_ && !node->label_tops_canvas) {
			_renderLabel(node, 0,0);
		}

		std::list<Node*>::const_iterator iterator;
		for (iterator = node->kids.begin(); iterator != node->kids.end(); ++iterator) {
			Node *kid = *iterator;

			render(kid);

			int kidAlphaFlags = kid->flags_ & G2_ALPHA_ANY;

			if (kidAlphaFlags) {
				g2::opacity(kid->alpha1_canvas);
				g2::opacity2(kid->alpha2_canvas);
			}

			g2::texture(kid->canvas);
			g2::rectFlipped(G2_TEXTURE | kidAlphaFlags, kid->x, kid->y, kid->w, kid->h);

			if (kid->label_ && kid->label_tops_canvas) {
				_renderLabel(kid, kid->x, kid->y);
			}

			if (kid->border_tops_canvas && (kid->flags_ & G2_BORDER_ANY)) {
				g2::color(kid->border_red, kid->border_green, kid->border_blue);
				g2::border(kid->flags_, kid->x, kid->y, kid->w, kid->h, kid->border_thickness, kid->border_alpha);
			}
		}

		if (!node->border_tops_canvas && (node->flags_ & G2_BORDER_ANY)) {
			g2::color(node->border_red, node->border_green, node->border_blue);
			g2::border(node->flags_, 0, 0,node->w, node->h, node->border_thickness, node->border_alpha);
		}
	}
	g2::endCanvas();
}