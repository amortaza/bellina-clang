#pragma once

#include <functional>

using namespace std;

namespace pango { extern class BasePluginCtx; }

namespace pango {	

	typedef function<BasePluginCtx*(void)> PluginCtxFactory;

	typedef function<void(void)> PluginLoad;
	typedef function<void(void)> PluginInit;
	typedef function<void(void)> PluginUninit;
	typedef function<bool(void*)> PluginCallback;
	typedef function<void(char* signature, PluginCtxFactory factory)> PluginOnNode;
}