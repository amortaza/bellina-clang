#include "stdafx.h"

namespace bl {

	namespace flags {
		unsigned int BL_BORDER_LEFT = 1 << 31;
		unsigned int BL_BORDER_TOP = 1 << 30;
		unsigned int BL_BORDER_RIGHT = 1 << 29;
		unsigned int BL_BORDER_BOTTOM = 1 << 28;;
		unsigned int BL_BORDER_ALL = BL_BORDER_LEFT | BL_BORDER_TOP | BL_BORDER_RIGHT | BL_BORDER_BOTTOM;
		unsigned int BL_BORDER_ANY = BL_BORDER_ALL;

		unsigned int BL_MOUSE_MOVE = 1 << 0;
		unsigned int BL_MOUSE_MOVE_BUBBLE = 1 << 1;
		unsigned int BL_MOUSE_DOWN = 1 << 2;
		unsigned int BL_MOUSE_DOWN_BUBBLE = 1 << 3;
		unsigned int BL_MOUSE_UP = 1 << 4;
		unsigned int BL_MOUSE_UP_BUBBLE = 1 << 5;
		unsigned int BL_MOUSE_SCROLL = 1 << 6;
		unsigned int BL_MOUSE_SCROLL_BUBBLE = 1 << 7;
	}
}
