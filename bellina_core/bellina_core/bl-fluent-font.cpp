#include "stdafx.h"

#include "bellina/bl-core.h"
#include "bl-fluent-font.h"

using namespace bl;

FluentFont* FluentFont::font(char *name, int size) {
	bl::font(name, size);
	return this;
}

FluentFont* FluentFont::color(unsigned char r, unsigned char g, unsigned char b) {
	bl::fontColor(r, g, b);
	return this;
}

FluentFont* FluentFont::text(char *t) {
	bl::text(t);
	return this;
}

FluentFont* FluentFont::opacity(float a) {
	bl::fontOpacity(a);
	return this;
}
