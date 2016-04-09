#include "stdafx.h"

#include "Xel/Xel.h"
#include "bl-extern.h"
#include "bl-ui.h"
#include "bl-sys.h"

using namespace bl;
using namespace bl::Internal;
using namespace bl::sys;

void bl::ui::onKeyDown(unsigned long long xcode) {
}

void bl::ui::onKeyUp(unsigned long long xcode) {
}

void bl::ui::onResize(int w, int h) {
	glViewport(0, 0, w, h);

	printf("Set glViewport\n");
}