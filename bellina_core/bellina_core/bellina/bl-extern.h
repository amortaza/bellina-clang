#pragma once

#include "bl-node.h"
#include "bl-fluent-border.h"
#include "bl-fluent-font.h"
#include "bl-flags.h"

#include <stack>

namespace bl {
	extern Node* node;

	namespace _ {
		extern Node *root;
		extern Node *current_node;

		extern unsigned int border_flag;

		extern std::stack<Node *> nodeStack;

		extern FluentBorder fluent_border;
		extern FluentFont fluent_font;

		extern char* focus_node_id;

		extern char* last_mouse_down_node_id;
		extern Xel::Mouse::Button last_mouse_down_button;

		extern std::list<Node*> key_down_registry;
		extern std::list<Node*> key_up_registry;

	}

	namespace util {
		void calcGlobalPositions();
		Node* getNodeAtPos(int wx, int wy);
	}
}