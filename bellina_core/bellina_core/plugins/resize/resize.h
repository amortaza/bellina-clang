#pragma once

namespace bl { extern class Node; };

using namespace bl;

namespace resize {
	void load();

	extern char* plugin_name;

	struct ResizeEvent {
		int w;
		int h;
		Node* node;
	};
}