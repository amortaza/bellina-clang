#include "stdafx.h"

#include "bellina/bl-extern.h"
#include "bellina/bl-core.h"

#include "focus.h"

using namespace bl;

namespace focus {
	char* focusNodeId = 0;

	void init() {
	}

	void uninit() {
		if (focusNodeId) delete[] focusNodeId;
	}

	void tick(Node *node) {
		bl::color(200, 255, 35);

		bl::onMouseDown([](Xel::Mouse::Button button, int mx, int my, Node* bubbledFrom) {
			focusNodeId = _strdup(bl::node->nid);
		});

		bl::onKeyDown([](unsigned long long xcode, Node* bubbledFrom) {
			if (focusNodeId && strcmp(focusNodeId, bl::node->nid) == 0) {
				printf("Receiveing key %s\n", bl::node->nid);
			}
		});
	}
}