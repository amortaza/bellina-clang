#include "stdafx.h"
#include <functional>
#include <ctime>

#include "bellina/bellina.h"

using namespace bl;
using namespace bl::Internal;
using namespace bl::flags;

using namespace g2::flags;

g2::TextureRef* guitar;
g2::TextureRef* jet;

int frame = 0;
long double first = time(0);

void Render_My_Bellina() {
	frame++;	
	if (frame % 32 == 0) {
		long double delta = time(0) - first;
		printf("FPS = %1.2f\n", (float)frame / delta);
	}

	if (root) {delete root; root = 0;}

	root = bl::nd(); 
	{
		bl::id("root node");
		bl::color(50, 0, 50);

		bl::onMouseMove([](int mx, int my) {
			printf("from root: node is %s\n", bl::node->nid);
		});

		bl::nd();
		{
			bl::onMouseMove([](int mx, int my) {
				printf("from child: node is %s\n", bl::node->nid);
			});
			bl::enable(BL_MOUSE_MOVE);

			bl::id("child A");
			bl::pos(10, 10);
			bl::dim(320, 240);
			bl::color(0, 50, 50);
			bl::padding(10, 3, 0, 0);

			//bl::font("arial", 35)->text("Hi, Clown!")->color(255, 255, 255);
			bl::text("Hi, Clown!")->font("arial", 35)->color(255, 255, 255);

			bl::border(BL_BORDER_ALL)->color(50, 0, 50)->thickness(4);

			bl::nd();
			{
				bl::id("child A.1");
				bl::pos(20, 170);
				bl::dim(160, 120);
				bl::color(0, 150, 150);
			}
			bl::end();
		}
		bl::end();
	}
	bl::end();
}

void Init_OnGL() {
	bl::init();

	//guitar = g2::loadTextureRgb("c:\\_c\\g2\\a.jpg");
	//jet = g2::loadTextureRgba("c:\\_c\\g2\\jet.png");

	/*Node *root = bl::Internal::root;
	root->pos(0, 0);
	root->color1(50, 0, 50);
	root->color2(0, 0, 50);
	root->setColorHorizGradientFlag();

	root->label("Welcome to Bellina!");
	
	Node *kid = new Node();

	kid->dim(300, 280);
	kid->pos(150, 50);
	kid->labelTops(true);

	kid->canvasOpacity1(.10f);
	//kid->canvasOpacity1(1.f);
	//kid->canvasOpacity2(.1015);
	//kid->addFlag(G2_ALPHA_HORIZ_GRADIENT);
	kid->addFlag(G2_ALPHA_SOLID);

	//kid->setTextureFlag();
	//kid->texture(guitar);

	//kid->addFlag(G2_MASK);
	//kid->mask(jet);

	kid->borderColor(BL_BORDER_ALL, 255, 255, 0);
	kid->borderThickness(BL_BORDER_ALL, 8);
	kid->borderOpacity(BL_BORDER_ALL, 1.f);
	//kid->borderTops(BL_BORDER_ALL, false);
	//kid->borderTops(BL_BORDER_RIGHT, true);

	kid->addFlag(BL_BORDER_ALL);

	kid->padding(10, 10, 60, 60);
	kid->addFlag(G2_PAD);

	kid->fontColor(255, 0, 0);
	kid->fontOpacity(1.f);
	kid->font("arial", 30);
	kid->label("Hello world!");
	
	root->addKid(kid);*/
}

void UnInit() {
	bl::uninit();
}