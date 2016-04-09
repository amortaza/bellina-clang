#include "stdafx.h"

#include "bl-node.h"
#include "bl-fluent-border.h"
#include "bl-fluent-font.h"

namespace bl {
	Node* node = 0;

	namespace flags {
		unsigned int BL_BORDER_LEFT = 1 << 31;
		unsigned int BL_BORDER_TOP = 1 << 30;
		unsigned int BL_BORDER_RIGHT = 1 << 29;
		unsigned int BL_BORDER_BOTTOM = 1 << 28;;
		unsigned int BL_BORDER_ALL = BL_BORDER_LEFT | BL_BORDER_TOP | BL_BORDER_RIGHT | BL_BORDER_BOTTOM;
		unsigned int BL_BORDER_ANY = BL_BORDER_ALL;
	}

	namespace Internal {
		Node *root = 0;
		Node *current_node = 0;		

		unsigned int border_flag = bl::flags::BL_BORDER_ALL;

		std::stack<Node *> nodeStack;

		FluentBorder fluent_border;
		FluentFont fluent_font;
	}
}