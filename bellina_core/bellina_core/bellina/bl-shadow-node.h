#pragma once

#include <map>

#include "bl-types.h"

using namespace std;

//namespace pango { extern class BasePluginCtx; }

class pango::BasePluginCtx;
using namespace pango;

namespace bl {

	class ShadowNode {

	private:
		map<string, BasePluginCtx*> pluginCtxByNameSignatureKey;

	public:
		BasePluginCtx* getPluginCtx(char* pluginName, char* signature, PluginCtxFactory );
		void setPluginCtx(char* pluginName, char* signature, BasePluginCtx* pluginCtx);

		void copyTo(Node* target);

	public:

		char* nid;

		int x, y;
		int w, h;
		
	public:
		~ShadowNode();
	};
}
