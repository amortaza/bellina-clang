#include "stdafx.h"

#include <ctime>

#include "g2/g2.h"

#include "bellina/bellina.h"

#include "plugins/focus/focus.h"
#include "plugins/click/click.h"
#include "plugins/double-click/double-click.h"

using namespace bl;
using namespace bl::flags;

using namespace g2::flags;

g2::TextureRef* guitar;
g2::TextureRef* jet;

int frame = 0;
long double first = time(0);
unsigned char r=0, g=50, b=150;

int coolid = -1;
struct Cool {
	int age;
};

void Render_My_Bellina() {

	frame++;
	if (frame % 512 == 0) {
		long double delta = time(0) - first;
		printf("FPS = %1.2f\n", (float)frame / delta);
	}
	
	bl::tick();
	bl::root();
	{
		bl::color(50, 0, 50);

		bl::div(); {
			bl::id("triple double");
			bl::pos(360, 200);
			bl::dim(160, 120);

			/*bl::on("double click", [](void* e) {
				click::MouseClickEvent* event = (click::MouseClickEvent*)e;

				printf("double clicks %s\n", event->node->nid);

				return true;
			});*/
		}
		bl::end();

		bl::div();
		{
			bl::id("child A");
			bl::pos(10, 10);
			bl::dim(160, 120);
			bl::color(r, 0, 0);
			Node* n = bl::current();
			bl::listenShortTerm("ace", [n](void* e) {
				//printf("acea cace %s\n",n->nid);
			});
			bl::on("click", [](void* e) {
				click::MouseClickEvent* event = (click::MouseClickEvent*) e;
				printf("clicked on node %s\n", event->node->nid);

				return true;
			});
		}
		bl::end();

		bl::div();
		{
			bl::captureMouse();
			bl::id("child B");
			bl::pos(180, 10);
			bl::dim(160, 120);
			bl::on("focus", [](void* e) {
				focus::FocusOnKeyEvent *event = (focus::FocusOnKeyEvent *) e;
				printf("key down on node %s\n",event->node->nid);

				return true;
			});
		}
		bl::end();

	}
	bl::end();
	
	bl::paint();
}

void Init_OnGL() {
	bl::init();

	bl::pluginLoad("focus", focus::init, focus::onNode, focus::tick, focus::uninit);
	bl::pluginLoad("click", click::init, click::onNode, click::tick, click::uninit);

	bl::pluginSetInt("double click", "duration", 1001);
	bl::pluginLoad("double click", double_click::init, double_click::onNode, double_click::tick, double_click::uninit);

	//guitar = g2::loadTextureRgb("c:\\_c\\g2\\a.jpg");
	//jet = g2::loadTextureRgba("c:\\_c\\g2\\jet.png");

	/*Node *root = bl::_::root;
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