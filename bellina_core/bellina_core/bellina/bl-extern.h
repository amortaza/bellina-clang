#pragma once

#include "bl-node.h"
#include "bl-fluent-border.h"
#include "bl-fluent-font.h"
#include "bl-flags.h"

#include <stack>

namespace bl {
	extern Node* node;

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