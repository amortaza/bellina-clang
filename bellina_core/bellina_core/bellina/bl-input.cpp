#include "stdafx.h"

#include "Xel/Xel.h"
#include "bl-extern.h"
#include "bl-input.h"
#include "bl-sys.h"

using namespace bl;
using namespace bl::_;
using namespace bl::sys;

void bl::input::onResize(int w, int h) {
	glViewport(0, 0, w, h);

	printf("Set glViewport\n");
}