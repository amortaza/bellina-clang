#include "stdafx.h"

#include "bl-core.h"
#include "bl-event.h"

using namespace bl;

std::map<std::string, std::list<EventCallback>*> eventRegistry;

void bl::listen(char* event_name, bl::EventCallback event_callback) {
	std::string key = std::string(event_name);

	std::list<EventCallback>* callbacks;

	auto e2 = eventRegistry.find(key);

	if (e2 == eventRegistry.end()) {
		callbacks = new std::list<EventCallback>();
		eventRegistry[key] = callbacks;

	}
	else {
		callbacks = e2->second;
	}

	callbacks->push_back(event_callback);
}

void bl::fire(char* event_name, void* event_data) {
	std::string key = std::string(event_name);

	std::list<EventCallback>* callbacks;

	auto e2 = eventRegistry.find(key);

	if (e2 == eventRegistry.end()) {
		// printf("No event handlers for %s\n", event_name);
	}
	else {
		callbacks = e2->second;

		std::list<EventCallback>::const_iterator iterator;

		for (iterator = callbacks->begin(); iterator != callbacks->end(); ++iterator) {
			EventCallback cb = *iterator;

			cb(event_data);
		}
	}
}

void bl::event::uninit() {
	typedef std::map<std::string, std::list<EventCallback>*>::iterator it1;
	for (it1 it = eventRegistry.begin(); it != eventRegistry.end(); it++) {
		std::list<EventCallback>* callbacks = it->second;

		delete callbacks;
	}
}
