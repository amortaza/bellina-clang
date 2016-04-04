#include "stdafx.h"

#include "bellina.h"

using namespace bl;
using namespace bl::Internal;

void Init_OnGL() {
	bl::init();

	Node *root = bl::Internal::root;
	root->pos(0, 0);
	root->color(0, 0, 0);
	root->label("Welcome to Bellina!");

	Node *kid = new Node();

	kid->dim(300, 280);
	kid->pos(150, 50);
	kid->color(50, 0, 0);
	kid->font("arial", 40);
	kid->label("Whats up?");

	root->addKid(kid);
}

void UnInit() {
	bl::uninit();
}