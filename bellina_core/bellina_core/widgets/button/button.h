#pragma once

#include "bellina/bl-types.h"

namespace button {

	typedef function<void(void)> ClickCallback;

	struct Button {
		char* id;
		Destructor destructor;

		char* title;
		ClickCallback click_cb;
	};

	extern Button* This;

	void begin(char* bid);
	void end();
	void render();

	void* construct(char* id);
	void destruct(void*);

	void title(char*);

	void click(ClickCallback);
}
