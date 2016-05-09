#pragma once

#include <map>
#include <stack>

using namespace std;

namespace bl { extern class Node; }
namespace bl { extern class FluentFont; }
namespace bl { extern class FluentBorder; }
namespace bl { namespace echo { extern class Echo; } }

using namespace bl::echo;

namespace bl {
	extern Node* node;

	namespace _ {
		extern unsigned int next_global_id;
		extern Node *root_node;
		extern Node *current_node;

		extern unsigned int border_flag;

		extern stack<Node *> nodeStack;

		extern FluentBorder fluent_border;
		extern FluentFont fluent_font;
		
		extern Echo* short_term_echo;
		extern Echo* long_term_echo;

		extern map<string, Node*> nodeById;
	}
}