#include "stdafx.h"

#include "bl-node.h"
#include "bl-fluent-border.h"
#include "bl-fluent-font.h"
#include "bl-flags.h"

namespace bl {
	Node* node = 0;

	namespace _ {
		Node *root = 0;
		Node *current_node = 0;

		unsigned int border_flag = bl::flags::BL_BORDER_ALL;

		std::stack<Node *> nodeStack;

		FluentBorder fluent_border;
		FluentFont fluent_font;

		std::list<Node*> key_down_registry;
		std::list<Node*> key_up_registry;
	}
}