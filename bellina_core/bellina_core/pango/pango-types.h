#pragma once

#include <functional>

//#include "BasePluginCtx.h"

//using namespace pango;

namespace pango {	

	class BasePluginCtx;

	typedef function<BasePluginCtx*(void)> PluginCtxFactory;

	typedef function<void(void)> PluginLoad;
	typedef function<void(void)> PluginInit;
	typedef function<void(void)> PluginUninit;
	typedef function<bool(void*)> PluginCallback;
	typedef function<void(char* signature, PluginCtxFactory* factory)> PluginOnNode;
}