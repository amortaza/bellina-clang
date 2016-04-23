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

void Render_My_Bellina() {

	frame++;
	if (frame % 512 == 0) {
		long double delta = time(0) - first;
		printf("FPS = %1.2f\n", (float)frame / delta);
	}

	bl::root();
	{
		/*bl::div(); {
			
			bl::id("dragman");

			bl::color(150, 0, 50);
			bl::pos(360, 200);
			bl::dim(160, 120);

			bl::on("drag", [](void* e) {
				drag::DragEvent* event = (drag::DragEvent*) e;
				return true;
			});
		}
		bl::end();*/

		bl::div(); {

			bl::id("parent");

			bl::color(50, 150, 0);
			bl::pos(460, 300);
			bl::dim(260, 220);

			/*bl::shadow([](Node* shadow) {
				shadow->x++;
			});*/

			bl::div(); {

				bl::id("dragman2");

				bl::color(0, 50, 150);
				bl::pos(46, 30);
				bl::dim(80, 60);

				bl::on("drag", [](void* e) {
					return true;
				});
			}
			bl::end();
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