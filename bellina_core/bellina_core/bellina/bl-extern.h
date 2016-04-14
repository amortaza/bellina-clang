#pragma once

namespace bl { extern class Node; }
namespace bl { extern class FluentFont; }
namespace bl { extern class FluentBorder; }

namespace bl {
	extern Node* node;

	namespace _ {
		extern Node *root;
		extern Node *current_node;

		extern unsigned int border_flag;

		extern std::stack<Node *> nodeStack;

		extern FluentBorder fluent_border;
		extern FluentFont fluent_font;

		extern std::list<Node*> key_down_registry;
		extern std::list<Node*> key_up_registry;

	}
}