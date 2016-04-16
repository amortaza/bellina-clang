#pragma once

namespace echo { extern class Echo; }

namespace bl { extern class Node; }
namespace bl { extern class FluentFont; }
namespace bl { extern class FluentBorder; }

namespace bl {
	extern Node* node;

	namespace _ {
		extern Node *root_node;
		extern Node *current_node;

		extern unsigned int border_flag;

		extern std::stack<Node *> nodeStack;

		extern FluentBorder fluent_border;
		extern FluentFont fluent_font;
		
		extern echo::Echo* node_echo;
		extern echo::Echo* plugin_echo;
	}
}