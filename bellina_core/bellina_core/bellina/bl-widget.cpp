#include "stdafx.h"

#include "bl-widget.h"

using namespace bl;

Widget::Widget(char* id_) {
	id = _strdup(id_);
}

Widget::~Widget() {
	if (id) delete[] id;

	printf("Widget: deleting\n");
}