#include "stdafx.h"

#include "bellina/bl-core.h"
#include "bl-fluent-border.h"

using namespace bl;

FluentBorder* FluentBorder::border(unsigned int borderFlag) {
	border_flag = borderFlag;
	return this;
}

FluentBorder* FluentBorder::color(unsigned char r, unsigned char g, unsigned char b) {
	bl::borderColor(r, g, b);
	return this;
}

FluentBorder* FluentBorder::thickness(int t) {
	bl::borderThickness(t);
	return this;
}

FluentBorder* FluentBorder::tops(bool b) {
	bl::borderTops(b);
	return this;
}

FluentBorder* FluentBorder::opacity(float a) {
	bl::borderOpacity(a);
	return this;
}
