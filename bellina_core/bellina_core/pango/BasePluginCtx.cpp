#include "stdafx.h"

#include "BasePluginCtx.h"

pango::BasePluginCtx::BasePluginCtx(char* signature) {
	_signature = _strdup(signature);
}

pango::BasePluginCtx::~BasePluginCtx() {
	if (_signature) delete[] _signature;
}
