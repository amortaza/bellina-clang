#include "stdafx.h"

#include "bl-input.h"
#include "bl-event.h"
#include "bl-core.h"

using namespace bl::event;

void bl::input::onResize(int w, int h) {
	glViewport(0, 0, w, h);
	printf("Set glViewport to %i, %i\n",w,h);

	ResizeEvent event;
	event.width = w;
	event.height = h;

	bl::fire("window resize", &event);
}
