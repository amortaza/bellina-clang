#include "stdafx.h"
#include"bl-node.h"

using namespace bl;

Node::Node() {
	dim(16, 16);

	color(255, 0, 0);
}

void Node::color(unsigned char _r, unsigned char _g, unsigned char _b) {
	r = _r; g = _g; b = _b;
}

void Node::dim(int _w, int _h) {
	w = _w; h = _h;
}
