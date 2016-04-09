#include "stdafx.h"

#include "bl-extern.h"
#include "bl-ui.h"

using namespace bl;
using namespace bl::Internal;

void bl::ui::onMouseMove(int mx, int my) {
	bl::node = util::getNodeAtPos(mx, my);

	if (bl::node) {		
		if (bl::node->callback_onMouseMove != nullptr) {
			bl::node->callback_onMouseMove(mx, my);

			// bubble up the event!
			Node *parent = bl::node->parent;
			while (parent) {
				if (parent->callback_onMouseMove!=nullptr) 
					parent->callback_onMouseMove(mx, my);

				parent = parent->parent;
			}
		}
	}
}

void bl::ui::onMouseButton(Xel::Mouse::Button button, Xel::Mouse::Action action, int x, int y) {
}

void bl::ui::onMouseScroll(int amount) {
}

void bl::ui::onKeyDown(unsigned long long xcode) {
}

void bl::ui::onKeyUp(unsigned long long xcode) {
}

void bl::ui::onResize(int w, int h) {
	glViewport(0, 0, w, h);

	printf("Set glViewport\n");
}