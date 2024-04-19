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
	Entity(const std::string& name, const std::string& description);
	virtual ~Entity();
	virtual void Update();
	string GetName();
	string GetDescription();
	Entity* GetEntityByType(Type type);
	Entity* GetEntityByTypeName(Type typeToCheck, string name);
	//bool LookType(Entity* entity, Type type);
	
};
#endif // !EXIT
