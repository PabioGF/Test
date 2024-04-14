#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <list>
#include <string>

using namespace std;

enum Type
{
	ENTITY,
	CREATURE,
	PLAYER,
	NPC,
	EXIT,
	ROOM,
	ITEM
};

class Entity {
public:
	Type type;
	string name, description;
	list<Entity*> contains;
public:
	Entity(const std::string& name, const std::string& description) : name(name), description(description) {}
	virtual void Update();
	string GetName();
	string GetDescription();
	bool LookType(Entity* entity, Type type);

};
#endif // !EXIT
