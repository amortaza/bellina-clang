#pragma once

#include "bl-node.h"
#include "bl-fluent-border.h"
#include "bl-fluent-font.h"

#include <stack>

namespace bl {
	extern Node* node;

	namespace flags {
		extern unsigned int BL_BORDER_LEFT;
		extern unsigned int BL_BORDER_TOP;
		extern unsigned int BL_BORDER_RIGHT;
		extern unsigned int BL_BORDER_BOTTOM;
		extern unsigned int BL_BORDER_ALL;
		extern unsigned int BL_BORDER_ANY;
	}

	namespace Internal {
		extern Node *root;
		extern Node *current_node;		

		extern unsigned int border_flag;

		extern std::stack<Node *> nodeStack;

		extern FluentBorder fluent_border;
		extern FluentFont fluent_font;
	}

	namespace util {
		void calcGlobalPositions();
		Node* getNodeAtPos(int wx, int wy);
	}
}