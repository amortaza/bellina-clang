#include "stdafx.h"

#include "bl-node.h"
#include "bl-fluent-border.h"
#include "bl-fluent-font.h"
#include "bl-flags.h"

namespace bl {
	Node* node = 0;

	namespace Internal {
		Node *root = 0;
		Node *current_node = 0;
		char* last_mouse_down_node_id = 0;

		Xel::Mouse::Button last_mouse_down_button;

		unsigned int border_flag = bl::flags::BL_BORDER_ALL;

		std::stack<Node *> nodeStack;

		FluentBorder fluent_border;
		FluentFont fluent_font;
	}
}