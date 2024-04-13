#include <iostream>
#include <string>  
#include <conio.h>
#include "item.h"
#include "entity.h"

using namespace std;

Item::Item(const std::string& name, const std::string& description, Entity* owner) : Entity(name, description), owner(owner) {}

Entity* Item::GetOwner() {
	return owner;
}