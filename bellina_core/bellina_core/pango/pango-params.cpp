#include "stdafx.h"

#include "pango-params.h"

namespace pango {
	namespace _ {
		map<string, int> intProperty;
		map<string, bool> boolProperty;
	}
}

using namespace pango::_;

void pango::setInt(char* name, char* prop_name, int value) {
	string key(name);
	key.append(":");
	key.append(prop_name);

	intProperty[key] = value;
}

void pango::setBool(char* name, char* prop_name, bool value) {
	string key(name);
	key.append(":");
	key.append(prop_name);

	boolProperty[key] = value;
}

int pango::getInt(char* name, char* prop_name) {
	string key(name);
	key.append(":");
	key.append(prop_name);

	auto e2 = intProperty.find(key);
	if (e2 == intProperty.end()) throw "plugin value not found in pluginGetInt";

	return e2->second;
}

bool pango::getBool(char* name, char* prop_name) {
	string key(name);
	key.append(":");
	key.append(prop_name);

	auto e2 = boolProperty.find(key);
	if (e2 == boolProperty.end()) throw "plugin value not found in pluginGetBool";

	return e2->second;
}

bool pango::hasInt(char* name, char* prop_name) {
	string key(name);
	key.append(":");
	key.append(prop_name);

	auto e2 = intProperty.find(key);
	if (e2 == intProperty.end()) return false;

	return true;
}

bool pango::hasBool(char* name, char* prop_name) {
	string key(name);
	key.append(":");
	key.append(prop_name);

	auto e2 = boolProperty.find(key);
	if (e2 == boolProperty.end()) return false;

	return true;
}
