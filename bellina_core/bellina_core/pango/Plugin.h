#pragma once

#include "pango-types.h"

using namespace std;

namespace pango {
	struct Plugin {
		string name;

		PluginInit init;
		PluginOnNode on_node;
		PluginCtxFactory default_factory;
		PluginUninit uninit;
	};
}
