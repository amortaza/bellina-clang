#pragma once

#include <map>

#include "bl-types.h"

namespace bl { extern class BasePluginContext; };

using namespace std;

namespace bl {

	class ShadowNode {

	private:
		map<string, BasePluginContext*> basePluginMap;

	public:
		BasePluginContext* getPlugin(char* pluginName, PluginFactory );
		void addPlugin(char* pluginName, BasePluginContext* plugin);

		void copyTo(Node* target);

	public:

		char* nid;

		int x, y;
		int w, h;
		
	public:
		~ShadowNode();
	};
}
