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
#include "bl-util.h"
#include "bl-plugin-bubble.h"
#include "bl-lifecycle.h"
#include "bl-shadow.h"

using namespace std;

using namespace bl;
using namespace bl::_;
using namespace bl::flags;
using namespace bl::sys;
using namespace bl::plugin;

void bl::root() {

	lifecycle::tickBeforeCoreRender();

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
	if (current_node->nid == 0) {
		current_node->nid = bl::util::nextGlobalId();
	}

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

	bl::plugin::uninit();
	bl::shadow_::uninit();

	if (root_node) delete root_node;

	nodeById.clear();

	delete _::short_term_echo;
	delete _::long_term_echo;	

	if (pluginBubble) delete pluginBubble;

	g2::uninit();
}

void bl::listenShortTerm(char* eventName, ListenerCallback eventCallback) {
	_::short_term_echo->listen(eventName, eventCallback);
}

void bl::listenLongTerm(char* eventName, ListenerCallback eventCallback) {
	_::long_term_echo->listen(eventName, eventCallback);
}

void bl::fire(char* eventName, void* eventData) {
	_::short_term_echo->fire(eventName, eventData);
	_::long_term_echo->fire(eventName, eventData);
}

Node* bl::current() {
	return current_node;
}

