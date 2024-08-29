#ifndef EVENTS_H
#define EVENTS_H

#include <functional>
#include <memory>
#include <unordered_map>
#include <algorithm>
#include "Character.h"

class Character; //Forward declaration of character

class Events {
private:
	std::unordered_map<int, std::function<void(std::shared_ptr<Character>)>> onChracterDeathCallbacks; //Use to store callbacks
	int nextId = 0;
public:

	//Add/Subscribe to character death
	int AddListenerToCharacterDeath(std::function<void(std::shared_ptr<Character>)> callback) {
		int id = nextId++;
		onChracterDeathCallbacks[id] = std::move(callback);//Add the callback to its corrisponding id
		return id; //return the id for future ref
	}

	//Remove/unsubscribe a callback from character death
	void RemoveListenerFromCharacterDeath(const int callBackId) {
		auto i = onChracterDeathCallbacks.find(callBackId);//Find the callback iterator to remove
		if(i != onChracterDeathCallbacks.end())
			onChracterDeathCallbacks.erase(i);
	}

	//Remove/unsubscribe all callbacks
	void RemoveAllListenersFromCharacterDeath()
	{
		onChracterDeathCallbacks.clear();
	}

	//Notify subscribed when character death
	void NotifyCharacterDeath(const std::shared_ptr<Character>& character)
	{
		//Loop through the map and call the callbacks
		for (auto i = onChracterDeathCallbacks.begin(); i != onChracterDeathCallbacks.end(); i++) {
			const std::function<void(std::shared_ptr<Character>)>& callback = i->second;
			callback(character);
		}
	}
};

#endif // !EVENTS_H
