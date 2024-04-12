#pragma once
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <list>
#include <string>

using namespace std;


class Entity {
public:
	enum type;
	string name, description;
	list<Entity*> contains;
public:
	//virtual void Update();
	string GetName();
	string GetDescription();
	Entity(const std::string& name, const std::string& description): name(name), description(description) {}


};
#endif // !EXIT
