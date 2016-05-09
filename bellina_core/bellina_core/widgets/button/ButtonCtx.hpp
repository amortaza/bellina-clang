#pragma once

#include "bellina/bl-widget.h"
#include "types.h"

using namespace bl;

namespace button {

	extern int State_Default;

	class ButtonCtx : public Widget {

	public:

		char* title;
		ClickCallback click_cb;

		int w, h;

		int state;

		ButtonCtx(char *id) : Widget(id) {
			title = 0;

			click_cb = nullptr;

			w = 128;
			h = 64;

			state = State_Default;
		}

		~ButtonCtx() {
			if (title) delete[] title;
		}
	};

}