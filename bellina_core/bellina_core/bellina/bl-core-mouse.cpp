#include "stdafx.h"

#include "bl-listener.h"
#include "bl-globals.h"
#include "bl-core.h"
#include "bl-globals.h"
#include "bl-sys.h"
#include "bl-plugin.h"
#include "bl-flags.h"
#include "bl-node.h"

using namespace bl;
using namespace bl::_;
using namespace bl::flags;
using namespace bl::sys;

void bl::onMouseScroll(NodeMouseScrollCallback cb) {
	current_node->onMouseScroll_callbacks.push_back(cb);
}

void bl::onMouseUp(NodeMouseUpCallback cb) {
	current_node->onMouseUp_callbacks.push_back(cb);
}

void bl::onMouseDown(NodeMouseDownCallback cb) {
	current_node->onMouseDown_callbacks.push_back(cb);
}

void bl::onMouseMove(NodeMouseMoveCallback cb) {
	current_node->onMouseMove_callbacks.push_back(cb);
}

void bl::onMouseMoveOnNode(Node* node, NodeMouseMoveCallback cb) {
	Node* original = current_node;

	current_node = node;

	onMouseMove(cb);

	current_node = original;
}

void bl::onMouseDownOnNode(Node* node, NodeMouseDownCallback cb) {
	Node* original = current_node;

	current_node = node;

	onMouseDown(cb);

	current_node = original;
}

void bl::onMouseUpOnNode(Node* node, NodeMouseUpCallback cb) {
	Node* original = current_node;

	current_node = node;

	onMouseUp(cb);

	current_node = original;
}

void bl::onMouseScrollOnNode(Node* node, NodeMouseScrollCallback cb) {
	Node* original = current_node;

	current_node = node;

	onMouseScroll(cb);

	current_node = original;
}
