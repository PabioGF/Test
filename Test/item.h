#pragma once
#ifndef ITEM_HPP
#define ITEM_HPP


#include "entity.h"

using namespace std;


class Item : public Entity {
public:
	Item(const std::string& name, const std::string& description);


};
#endif // !EXIT