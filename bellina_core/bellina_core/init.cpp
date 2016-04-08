#include "stdafx.h"

#include "bellina.h"

using namespace bl;
using namespace bl::Internal;
using namespace g2::flags;

g2::TextureRef* guitar;
g2::TextureRef* jet;

void Init_OnGL() {
	bl::init();

	guitar = g2::loadTextureRgb("c:\\_c\\g2\\a.jpg");
	jet = g2::loadTextureRgba("c:\\_c\\g2\\jet.png");

	Node *root = bl::Internal::root;
	root->pos(0, 0);
	root->color1(50, 0, 50);
	root->color2(0, 0, 50);
	root->setColorHorizGradientFlag();
	root->borderColor(255, 0, 0);
	root->borderThickness(4);
	root->borderOpacity(1.0f);
	root->borderTops(true);
	root->addFlag(G2_BORDER_ALL);
	//root->label("Welcome to Bellina!");
	
	Node *kid = new Node();

	kid->dim(300, 280);
	kid->pos(150, 50);
	kid->labelTops(true);
	kid->borderTops(true);
	kid->canvasOpacity1(.945);
	kid->canvasOpacity2(.015);
	kid->addFlag(G2_ALPHA_HORIZ_GRADIENT);
	kid->setTextureFlag();
	kid->texture(guitar);

	kid->addFlag(G2_MASK);
	kid->mask(jet);

	kid->borderColor(255, 255, 0);
	kid->borderThickness(8);
	kid->borderOpacity(1.f);
	kid->borderTops(true);

	kid->addFlag(G2_BORDER_LEFT);

	kid->padding(10, 10, 60, 60);
	kid->addFlag(G2_PAD);

	kid->fontColor(255, 0, 0);
	kid->fontOpacity(1.f);
	kid->font("arial", 30);
	kid->label("Hello world!");

	//kid->color1(50, 0, 0);
	//kid->font("arial", 40);
	//kid->label("Whats up?");

	root->addKid(kid);
}

void UnInit() {
	bl::uninit();
}