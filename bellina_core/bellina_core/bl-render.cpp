#include "stdafx.h"
#include <list>

#include "g2.h"

#include "bl-render.h"
#include "bl-extern.h"
#include "bl-core.h"

using namespace bl;
using namespace bl::Internal;

using namespace g2::flags;

void bl::paint() {
	//printf("win %i %i\n", winW, winH);
	int winW = Xel::Window::width;
	int winH = Xel::Window::height;

	bl::Internal::root->dim(winW, winH);

	g2::viewport(winW, winH);
	g2::ortho(winW, winH);

	//g2::clear();

	bl::render(bl::Internal::root);

	g2::texture(bl::Internal::root->canvasRef);
	g2::rectFlipped(g2::flags::G2_TEXTURE, 0, 0, winW, winH);
}

void bl::render(Node *node) {
	g2::paintCanvas(node->canvasRef);
		g2::rgb(node->r, node->g, node->b);
		g2::rect(G2_RGB_SOLID, 0, 0, node->w, node->h);

		//g2::rgb(34,78,200);
		//g2::rect(G2_RGB_SOLID, 0, 0, 10, 10); //node->x, node->y, node->w, node->h);

		if (node->text) {
			g2::rgb(255, 255, 255);
			g2::font(node->font_name, node->font_size);
			g2::text(0, node->textY, node->text);
		}

		std::list<Node*>::const_iterator iterator;
		for (iterator = node->kids.begin(); iterator != node->kids.end(); ++iterator) {
			Node *kid = *iterator;

			render(kid);

			g2::texture(kid->canvasRef);
			g2::rectFlipped(g2::flags::G2_TEXTURE, kid->x, kid->y, kid->w, kid->h);
		}

	g2::endCanvas();
}