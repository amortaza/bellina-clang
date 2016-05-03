#include "stdafx.h"

#include <map>

#include "Plugin.h"

using namespace std;

namespace pango {

	namespace _ {
		map<string, Plugin*> pluginByName;
	}
}