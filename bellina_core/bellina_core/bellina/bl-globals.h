#pragma once

#include <map>

namespace bl { extern class Node; }
namespace bl { extern class FluentFont; }
namespace bl { extern class FluentBorder; }
namespace bl { namespace echo { extern class Echo; } }
namespace bl { namespace plugin { namespace bubble { extern class PluginBubble; } } }

using namespace bl::echo;
using namespace bl::plugin::bubble;

namespace bl {
	extern Node* node;

	namespace _ {
		extern unsigned int next_global_id;
		extern Node *root_node;
		extern Node *current_node;

		extern unsigned int border_flag;

		extern std::stack<Node *> nodeStack;

		extern FluentBorder fluent_border;
		extern FluentFont fluent_font;
		
		extern Echo* short_term_echo;
		extern Echo* long_term_echo;

		extern std::map<std::string, Node*> nodeById;

		extern PluginBubble* pluginBubble;
	}
}