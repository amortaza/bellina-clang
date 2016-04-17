#include "stdafx.h"

#include <map>

#include "bl-echo.h"
#include "bl-node.h"
#include "bl-fluent-border.h"
#include "bl-fluent-font.h"
#include "bl-flags.h"
#include "bl-plugin-bubble.h"

using namespace bl::echo;
using namespace bl::plugin::bubble;

namespace bl {
	Node* node = 0;

	namespace _ {
		Node *root_node = 0; // "root" is a function
		Node *current_node = 0;

		Node* capture_mouse_node = 0;//

		unsigned int border_flag = bl::flags::BL_BORDER_ALL;

		std::stack<Node *> nodeStack;

		FluentBorder fluent_border;
		FluentFont fluent_font;
		
		Echo* short_term_echo = new Echo();
		Echo* long_term_echo = new Echo();

		 std::map<std::string, Node*> nodeById;

		 PluginBubble *pluginBubble = new PluginBubble();

		 unsigned int next_global_id = 0;
	}
}