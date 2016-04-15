#include "stdafx.h"

#include "g2/g2.h"

#include "bl-core.h"
#include "bl-globals.h"
#include "bl-sys.h"
#include "bl-plugin.h"
#include "bl-flags.h"
#include "bl-listener.h"
#include "bl-node.h"

using namespace bl;
using namespace bl::_;
using namespace bl::flags;
using namespace bl::sys;
using namespace bl::listener::_;
using namespace bl::plug;

void bl::root() {
	if (root_node) { delete root_node; root_node = 0; }

	root_node = div();
	id("ROOT");
}

Node* bl::div() {
	Node* parent = current_node;

	current_node = new Node(parent);

	if (parent) {
		parent->addKid(current_node);
		nodeStack.push(parent);
	}

	return current_node;
}

void bl::end() {
	if (nodeStack.size() > 0) {
		current_node = nodeStack.top();
		nodeStack.pop();
	}
	else
		current_node = 0;
}

void bl::init() {
	g2::init();

	// window not available yet
}

void bl::uninit() {
	if (root_node) delete root_node;

	bl::plug::uninit();

	bl::listener::uninit();

	g2::uninit();
}

