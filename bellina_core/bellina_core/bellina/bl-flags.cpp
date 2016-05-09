#include "stdafx.h"

namespace bl {

	namespace flags {
		unsigned int BL_BORDER_LEFT = 1 << 31;
		unsigned int BL_BORDER_TOP = 1 << 30;
		unsigned int BL_BORDER_RIGHT = 1 << 29;
		unsigned int BL_BORDER_BOTTOM = 1 << 28;;
		unsigned int BL_BORDER_ALL = BL_BORDER_LEFT | BL_BORDER_TOP | BL_BORDER_RIGHT | BL_BORDER_BOTTOM;
		unsigned int BL_BORDER_ANY = BL_BORDER_ALL;

		unsigned int BL_TEXT_ALIGN_LEFT = 1 << 27;
		unsigned int BL_TEXT_ALIGN_TOP = 1 << 26;
		unsigned int BL_TEXT_ALIGN_RIGHT = 1 << 25;
		unsigned int BL_TEXT_ALIGN_BOTTOM = 1 << 24;
		unsigned int BL_TEXT_CENTER_HORIZ = 1 << 23;
		unsigned int BL_TEXT_CENTER_VERT = 1 << 22;

		unsigned int BL_TEXT_CENTER_ALL = BL_TEXT_CENTER_HORIZ | BL_TEXT_CENTER_VERT;
		unsigned int BL_TEXT_ALIGN_DEFAULT = BL_TEXT_ALIGN_LEFT | BL_TEXT_ALIGN_TOP;
		unsigned int BL_TEXT_ALIGN_ANY = BL_TEXT_ALIGN_DEFAULT | BL_TEXT_CENTER_ALL | BL_TEXT_ALIGN_RIGHT | BL_TEXT_ALIGN_BOTTOM;
	}
}
