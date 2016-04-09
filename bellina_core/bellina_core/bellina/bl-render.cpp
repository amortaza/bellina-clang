#include "stdafx.h"
#include <list>

#include "g2/g2.h"

#include "bl-render.h"
#include "bl-extern.h"
#include "bl-core.h"

using namespace bl;
using namespace bl::Internal;
using namespace bl::flags;

using namespace g2::flags;

void _renderLabel(Node *node, int dx, int dy) {
	g2::color(node->font_red, node->font_green, node->font_blue);
	g2::font(node->font_name, node->font_size);

	if (node->flags & G2_PAD)
		g2::text(dx + node->padding_left, dy + node->padding_top + node->fontHeight, node->label_, node->font_alpha);
	else
		g2::text(dx, dy + node->fontHeight, node->label_, node->font_alpha);
}

void _renderBorder(Node *n, bool mustTopCanvas, int deltaX, int deltaY) {
	BorderSide *b = 0;

	int bx = deltaX, bw = n->w;

	if (n->flags & BL_BORDER_LEFT) {
		b = &n->border_left;

		if (b->topsCanvas == mustTopCanvas) {
			g2::opacity(b->alpha);
			g2::color(b->red, b->green, b->blue);
			g2::rect(G2_COLOR_SOLID | G2_ALPHA_SOLID, deltaX, deltaY, b->thickness, n->h);
		}

		bx += b->thickness;
		bw -= b->thickness;
	}

	if (n->flags & BL_BORDER_RIGHT) {
		b = &n->border_right;

		if (b->topsCanvas == mustTopCanvas) {
			g2::opacity(b->alpha);
			g2::color(b->red, b->green, b->blue);
			g2::rect(G2_COLOR_SOLID | G2_ALPHA_SOLID, deltaX + n->w - b->thickness, deltaY, b->thickness, n->h);
		}

		bw -= b->thickness;
	}

	if (n->flags & BL_BORDER_TOP) {
		b = &n->border_top;

		int by = deltaY;
		int bh = b->thickness;

		if (b->topsCanvas == mustTopCanvas) {
			g2::opacity(b->alpha);
			g2::color(b->red, b->green, b->blue);
			g2::rect(G2_COLOR_SOLID | G2_ALPHA_SOLID, bx, by, bw, bh);
		}
	}


	if (n->flags & BL_BORDER_BOTTOM) {
		b = &n->border_bottom;

		int by = deltaY + n->h - b->thickness;
		int bh = b->thickness;

		if (b->topsCanvas == mustTopCanvas) {
			g2::opacity(b->alpha);
			g2::color(b->red, b->green, b->blue);
			g2::rect(G2_COLOR_SOLID | G2_ALPHA_SOLID, bx, by, bw, bh);
		}
	}
}

void bl::paint() {
	if (!root) return;

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

	if (root->flags & BL_BORDER_ANY) {
		_renderBorder(root, true, 0, 0);
	}
}

void bl::render(Node *node) {
	g2::paintCanvas(node->canvas);
	{
		if (node->flags & G2_COLOR_ANY) {
			g2::color(node->r1, node->g1, node->b1);
			g2::color2(node->r2, node->g2, node->b2);
		}

		if (node->flags & G2_TEXTURE) {
			g2::texture(node->texture_);
		}

		if (node->flags & G2_MASK) {
			g2::mask(node->mask_);
		}

		if (node->flags & G2_PAD) {
			g2::padding(node->padding_left, node->padding_top, node->padding_right, node->padding_bottom);
		}

		// we are in canvas, so x, y is 0,0
		g2::rect(node->flags, 0, 0, node->w, node->h);

		// ---------------------------------------------------------------------
		if (node->label_ && !node->label_tops_canvas) {
			_renderLabel(node, 0,0);
		}

		std::list<Node*>::const_iterator iterator;
		for (iterator = node->kids.begin(); iterator != node->kids.end(); ++iterator) {
			Node *kid = *iterator;

			render(kid);

			int kidAlphaFlags = kid->flags & G2_ALPHA_ANY;

			if (kidAlphaFlags) {
				g2::opacity(kid->alpha1_canvas);
				g2::opacity2(kid->alpha2_canvas);
			}

			g2::texture(kid->canvas);
			g2::rectFlipped(G2_TEXTURE | kidAlphaFlags, kid->x, kid->y, kid->w, kid->h);

			if (kid->label_ && kid->label_tops_canvas) {
				_renderLabel(kid, kid->x, kid->y);
			}

			if (kid->flags & BL_BORDER_ANY) {
				_renderBorder(kid, true, kid->x, kid->y);
			}
		}

		if (node->flags & BL_BORDER_ANY) {
			_renderBorder(node, false, 0,0);
		}
	}
	g2::endCanvas();
}