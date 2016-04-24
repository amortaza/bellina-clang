#include "stdafx.h"

#include <ctime>

#include "g2/g2.h"

#include "bellina/bellina.h"

#include "plugins/focus/focus.h"
#include "plugins/click/click.h"
#include "plugins/double-click/double-click.h"
#include "plugins/drag/drag.h"
#include "plugins/z-index/z-index.h"

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

	printf("start root *********************** \n");
	bl::root();
	{
		bl::color(10, 0, 10);

		bl::div(); {
			
			bl::id("red");

			bl::color(150, 0, 50);
			bl::pos(100, 100);
			bl::dim(320, 240);
		}
		bl::end();

		bl::div(); {

			bl::id("green");

			bl::color(50, 150, 50);
			bl::pos(200, 200);
			bl::dim(320, 240);
		}
		bl::end();

		bl::div(); {

			bl::id("blue");

			bl::color(50, 50, 150);
			bl::pos(300, 300);
			bl::dim(320, 240);
		}
		bl::end();

		bl::on("z-index", [](void* e) {
			return true;
		});
	}
	bl::end();
	
	printf("paint ***\n");
	bl::paint();
}

void Init_OnGL() {
	bl::init();

//	bl::pluginLoad("focus", focus::init, focus::onNode, focus::tickOnAfterCoreRender, focus::uninit);
//	bl::pluginLoad("click", click::init, click::onNode, click::tickOnAfterCoreRender, click::uninit);

	//bl::pluginSetInt("double click", "duration", 1001);
	//bl::pluginLoad("double click", double_click::init, double_click::onNode, double_click::tickOnAfterCoreRender, double_click::uninit);

	//bl::pluginLoad("drag", drag::init, drag::onNode, drag::tickOnAfterCoreRender, nullptr, drag::uninit);
	bl::pluginLoad("z-index", z_index::init, z_index::onNode, nullptr, z_index::uninit);
}

void UnInit() {
	bl::uninit();
}