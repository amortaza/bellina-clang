#include "stdafx.h"

#include "g2/g2.h"

#include "bl-core.h"
#include "bl-extern.h"

using namespace bl;
using namespace bl::Internal;

void bl::init() {
	g2::init();

	// window not available yet
	root = new Node();
}

void bl::uninit() {
	delete root;

	g2::uninit();
}
