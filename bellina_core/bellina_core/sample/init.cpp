#include "stdafx.h"

#include <ctime>

#include "g2/g2.h"

#include "bellina/bellina.h"

#include "plugins/focus/focus.h"
#include "plugins/click/click.h"
#include "plugins/double-click/double-click.h"
#include "plugins/node-drag/node-drag.h"
#include "plugins/z-index/z-index.h"
#include "plugins/mouse-in/mouse-in.h"
#include "plugins/resize/resize.h"
#include "plugins/mouse-drag/mouse-drag.h"

using namespace node_drag;
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
		bl::color(50, 0, 10);

		bl::div(); {

			bl::id("green");

			bl::color(0, 150, 50);
			bl::pos(200, 200);
			bl::dim(160, 120);

			auto a = [](void* e) { printf("green2\n"); return true; };

			bl::on("click", a);

			/*bl::on("resize", [](void* e) {
				printf("resize green\n");
				return true; });*/
		}
		bl::end();

		bl::div(); {

			bl::id("red");

			bl::color(150, 0, 50);
			bl::pos(100, 100);
			bl::dim(160, 120);

			/*bl::on("resize", [](void* e) {
				printf("resize red\n");
				return true; });*/
		} 
		bl:end();

		//bl::use("z-index");
	}
	bl::end();
	
	bl::paint();
}

void Init_OnGL() {
	bl::init();

	pango::load(focus::load);
	pango::load(click::load);

	//bl::pluginSetInt("double-click", "duration", 1001);
	pango::load(double_click::load);

	//bl::pluginLoad(mouse_drag::load);
	pango::load(node_drag::load);

	//bl::pluginSetBool(z_index::plugin_name, "")
	pango::load(z_index::load);

	pango::load(mouse_in::load);

	pango::load(resize::load);
}

void UnInit() {
	bl::uninit();
}