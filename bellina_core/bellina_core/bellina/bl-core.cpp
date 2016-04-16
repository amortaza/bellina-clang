#include "stdafx.h"

#include "g2/g2.h"
#include "bl-echo.h"

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
using namespace bl::plugin;

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

	bl::plugin::uninit();

	delete _::short_term_echo;
	delete _::long_term_echo;

	g2::uninit();
}

void bl::listenShortTerm(char* event_name, ListenerCallback event_callback) {
	_::short_term_echo->listen(event_name, event_callback);
}

void bl::listenLongTerm(char* event_name, ListenerCallback event_callback) {
	_::long_term_echo->listen(event_name, event_callback);
}

void bl::fire(char* event_name, void* event_data) {
	_::short_term_echo->fire(event_name, event_data);
	_::long_term_echo->fire(event_name, event_data);
}
