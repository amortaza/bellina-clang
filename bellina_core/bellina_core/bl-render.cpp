#include "stdafx.h"

#include "bl-render.h"
#include "bl-extern.h"
#include "bl-core.h"

using namespace bl;
using namespace bl::Internal;
using namespace g2::flags;

void bl::paint() {
	int winW = Xel::Window::width;
	int winH = Xel::Window::height;

	g2::viewport(winW, winH);
	g2::ortho(winW, winH);

	g2::clear();

	bl::render(bl::Internal::root);
}

void bl::render(Node *node) {
	g2::rgb(node->r, node->g, node->b);
	g2::rect(G2_RGB_SOLID, 0,0,node->w, node->h);

}