#include "stdafx.h"

#include <ctime>

#include "g2/g2.h"

#include "bellina/bellina.h"

#include "plugins/focus/focus.h"
#include "plugins/click/click.h"
#include "plugins/double-click/double-click.h"
#include "plugins/drag/drag.h"

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
	Node*t;	
	//printf("***************************************\n");
	bl::root();
	{
		bl::color(50, 0, 50);

		bl::div(); {
			
			t = _::current_node;

			bl::id("dragman");
			//printf("setting to 360\n");
			bl::pos(360, 200);
			bl::dim(160, 120);

			bl::on("drag", [](void* e) {
				drag::DragEvent* event = (drag::DragEvent*) e;

				printf("dragging %s, x is %i\n", event->node->nid, event->node->x);

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

//	bl::pluginLoad("focus", focus::init, focus::onNode, focus::tickOnAfterCoreRender, focus::uninit);
//	bl::pluginLoad("click", click::init, click::onNode, click::tickOnAfterCoreRender, click::uninit);

	//bl::pluginSetInt("double click", "duration", 1001);
	//bl::pluginLoad("double click", double_click::init, double_click::onNode, double_click::tickOnAfterCoreRender, double_click::uninit);

	bl::pluginLoad("drag", drag::init, drag::onNode, drag::tickOnAfterCoreRender, drag::uninit);
}

void UnInit() {
	bl::uninit();
}