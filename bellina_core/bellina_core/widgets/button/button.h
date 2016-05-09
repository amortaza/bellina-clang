#pragma once

#include "bellina/bl-types.h"
#include "bellina/bl-widget.h"

#include "types.h"

namespace button {
	extern class ButtonCtx;

	extern ButtonCtx* This;

	void begin(char* bid);
	void end();
	void render();

	Widget* construct(char* id);

	void title(char*);
	void dim(int w, int h);

	void click(ClickCallback);
}
