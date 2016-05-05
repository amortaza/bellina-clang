#pragma once

#include "bellina/bl-types.h"

namespace button {

	struct Button {
		char* id;
		Destructor destructor;
	};

	void begin();
	void end();

	Button* construct(char* id);
	void destruct(Button*);
}
