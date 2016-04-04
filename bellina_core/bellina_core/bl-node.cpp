#include "stdafx.h"
#include"bl-node.h"

using namespace bl;

Node::Node() {
	canvasRef = 0;
	w = h = -1;

	pos(0, 0);
	color(255, 0, 0);
}

void Node::color(unsigned char _r, unsigned char _g, unsigned char _b) {
	r = _r; g = _g; b = _b;
}

void resetCanvasRef(Node *node, int w, int h) {
	if (node->canvasRef) delete node->canvasRef;

	printf("creating canvas %i %i\n", w, h);
	node->canvasRef = g2::createCanvas(w,h);
}
void Node::dim(int _w, int _h) {
	if (_w != w || _h != h) {
		w = _w; h = _h;
		resetCanvasRef(this, _w, _h);		
	}
	else {
		w = _w; h = _h;
	}
}

void Node::pos(int _x, int _y) {
	x = _x; y = _y;
}

void Node::addKid(Node* kid) {
	kids.push_back(kid);
}

Node::~Node() {
	// canvas ref
	if (canvasRef) delete canvasRef;

	// kids
	std::list<Node*>::const_iterator iterator;

	for (iterator = kids.begin(); iterator != kids.end(); ++iterator) {
		Node *kid = *iterator;

		delete kid;
	}
}