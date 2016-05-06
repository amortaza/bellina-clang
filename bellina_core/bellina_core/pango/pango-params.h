#pragma once

#include <map>

using namespace std;

namespace pango {
	namespace _ {
		extern map<string, int> intProperty;
		extern map<string, bool> boolProperty;
	}

	void setInt(char* pluginName, char* propName, int value);
	int  getInt(char* pluginName, char* propName);
	bool hasInt(char* pluginName, char* propName);

	void setBool(char* pluginName, char* propName, bool value);
	bool getBool(char* pluginName, char* propName);
	bool hasBool(char* pluginName, char* propName);
}