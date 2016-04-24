#include "stdafx.h"

#include <ctime>

#include "g2/g2.h"

#include "bellina/bellina.h"

#include "plugins/focus/focus.h"
#include "plugins/click/click.h"
#include "plugins/double-click/double-click.h"
#include "plugins/drag/drag.h"
#include "plugins/z-index/z-index.h"
#include "plugins/mouse-in/mouse-in.h"
#include "plugins/resize/resize.h"
#include "plugins/mouse-drag/mouse-drag.h"

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

	//rintf("********************************\n");
	//rintf("start root\n");
	bl::root();
	{
		
		bl::color(50, 0, 10);

		bl::div(); {
			
			bl::id("red");

			bl::color(150, 0, 50);
			bl::pos(100, 100);
			bl::dim(320, 240);
			
			bl::on("resize", [](void* e) {
				resize::ResizeEvent* event = (resize::ResizeEvent*) e;

				printf("%i %i\n", event->w, event->h);

				return true;
			});
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
	}
	bl::end();
	
	bl::paint();
}

void Init_OnGL() {
	bl::init();

	//bl::pluginLoad(focus::load);
	//bl::pluginLoad(click::load);

	//bl::pluginSetInt("double click", "duration", 1001);
	//bl::pluginLoad(double_click::load);

	bl::pluginLoad(mouse_drag::load);
	//bl::pluginLoad(drag::load);
	
	//bl::pluginLoad(z_index::load);

	//bl::pluginLoad(mouse_in::load);

	bl::pluginLoad(resize::load);
}

void UnInit() {
	bl::uninit();
}