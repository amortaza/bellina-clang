#include "stdafx.h"
#include <list>

#include "g2/g2.h"

#include "bl-render.h"
#include "bl-extern.h"
#include "bl-core.h"

using namespace bl;
using namespace bl::Internal;

using namespace g2::flags;

void bl::paint() {
	int winW = Xel::Window::width;
	int winH = Xel::Window::height;

	root->dim(winW, winH);

	g2::viewport(winW, winH);
	g2::ortho(winW, winH);

	//g2::clear();

	bl::render(root);

	g2::texture(root->canvas);
	g2::rectFlipped(G2_TEXTURE, 0, 0, winW, winH);
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

		if (node->flags_ & G2_ALPHA_ANY) {
			g2::opacity(node->alpha1);
			g2::opacity2(node->alpha2);
		}

		if (node->flags_ & G2_PAD) {
			g2::padding(node->padding_left, node->padding_top, node->padding_right, node->padding_bottom);
			g2::opacity2(node->alpha2);
		}

		if (node->flags_ & G2_PAD) {
			g2::padding(node->padding_left, node->padding_top, node->padding_right, node->padding_bottom);
			g2::opacity2(node->alpha2);
		}

		// we are in canvas, so x, y is 0,0
		g2::rect(node->flags_, 0, 0, node->w, node->h);

		//g2::rgb(34,78,200);
		//g2::rect(G2_RGB_SOLID, 0, 0, 10, 10); //node->x, node->y, node->w, node->h);

		if (node->label_) {
			g2::color(255, 255, 255);
			g2::font(node->font_name, node->font_size);
			g2::text(0, node->fontHeight, node->label_);
		}

		std::list<Node*>::const_iterator iterator;
		for (iterator = node->kids.begin(); iterator != node->kids.end(); ++iterator) {
			Node *kid = *iterator;

			render(kid);

			g2::texture(kid->canvas);
			g2::rectFlipped(G2_TEXTURE, kid->x, kid->y, kid->w, kid->h);
		}

	g2::endCanvas();
}