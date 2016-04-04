#include "stdafx.h"

#include "bellina.h"

using namespace bl;
using namespace bl::Internal;

void Init_OnGL() {
	bl::init();

	Node *root = bl::Internal::root;
	root->pos(0, 0);
	root->color(0, 255, 255);

	Node *kid = new Node();

	kid->dim(300, 80);
	kid->pos(1250, 50);
	kid->color(255, 0, 255);

	root->addKid(kid);
}

void UnInit() {
	bl::uninit();
}