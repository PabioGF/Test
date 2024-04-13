#pragma once
#ifndef ITEM_HPP
#define ITEM_HPP


#include "entity.h"

using namespace std;


class Item : public Entity {
public:
	Entity* owner;
public:
	Item(const std::string& name, const std::string& description, Entity* owner);
	Entity* GetOwner();
};
#endif // !EXIT