#include "stdafx.h"

#include "echo.h"

using namespace echo;

Echo::~Echo() {
   	listenerRegistry.clear();
}

void Echo::listen(char* eventName, ListenerCallback callback) {
   	std::string key = std::string(eventName);

	std::list<ListenerCallback>* callbacks;

	auto e2 = listenerRegistry.find(key);

	if (e2 == listenerRegistry.end()) {
		callbacks = new std::list<ListenerCallback>();
		listenerRegistry[key] = callbacks;
	}
	else {
		callbacks = e2->second;
	}

	callbacks->push_back(callback);
}

void Echo::fire(char* eventName, void*eventData) {
   	std::string key = std::string(eventName);

	std::list<ListenerCallback>* callbacks;

	auto e2 = listenerRegistry.find(key);

	if (e2 != listenerRegistry.end()) {
		callbacks = e2->second;

		std::list<ListenerCallback>::const_iterator iterator;

		for (iterator = callbacks->begin(); iterator != callbacks->end(); ++iterator) {
			ListenerCallback cb = *iterator;

			cb(eventData);
		}
	}
}