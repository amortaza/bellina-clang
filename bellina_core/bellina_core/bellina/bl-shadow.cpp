#include "stdafx.h"

#include "bl-core.h"
#include "bl-shadow-node.h"
#include "bl-node.h"
#include "bl-globals.h"
#include "bl-shadow.h"
#include "bl-util.h"
#include "bl-widget.h"

using namespace std;

namespace bl {
	namespace shadow_ {
		map<string, ShadowNode *> shadowNodes;		
		map<string, Widget*> shadowObjs;
	}
}

using namespace bl;
using namespace bl::_;

ShadowNode* bl::get_shadow() {
	return shadow_::getShadowNode(current_node);
}

void bl::shadow(ShadowCallback cb) {
	ShadowNode* shadowNode;

	shadowNode = shadow_::getShadowNode(current_node);

	cb(shadowNode);

	shadowNode->copyTo(current_node);
}

Widget* bl::shadows(char* id, Constructor constructor) {

	string key(id);
	Widget* obj;

	auto e2 = shadow_::shadowObjs.find(key);
	
	if (e2 == shadow_::shadowObjs.end()) {
		obj = constructor(id);
		shadow_::shadowObjs[key] = obj;
		printf("created shadow\n");
	}
	else obj = e2->second;

	return obj;
}

void bl::shadow_::uninit() {
	typedef map<string, ShadowNode*>::iterator it1;

	for (it1 it = shadowNodes.begin(); it != shadowNodes.end(); it++) {
		ShadowNode* snode = it->second;

		delete snode;
		// test new ShadowNode();
	}

	//
	typedef map<string, Widget*>::iterator it2;
	for (it2 it = shadow_::shadowObjs.begin(); it != shadow_::shadowObjs.end(); it++) {
		Widget* obj = it->second;

		delete obj;
		//test new Widget();
	}
}

ShadowNode* shadow_::getShadowNode(Node* node) {
	ShadowNode* snode = 0;

	string key(node->nid);

	auto e2 = shadow_::shadowNodes.find(key);
	if (e2 == shadow_::shadowNodes.end()) {
		snode = new ShadowNode();
		snode->x = node->x;
		snode->y = node->y;
		snode->w = node->w;
		snode->h = node->h;
		shadow_::shadowNodes[key] = snode;
	}
	else {
		snode = e2->second;
	}

	return snode;
}
