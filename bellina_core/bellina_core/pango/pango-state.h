#pragma once

#include <map>

using namespace std;

namespace pango {

	extern struct Plugin;

	namespace _ {
		extern map<string, Plugin*> pluginByName;
	}
}