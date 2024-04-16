#include <iostream>
#include <string>  
#include <conio.h>
#include "room.h"
#include "entity.h"

using namespace std;

Entity::Entity(const std::string& name, const std::string& description) : name(name), description(description) {
    contains.push_back(this);
}

void Entity::Update() {

}

string Entity::GetName() {
	return name;
}

string Entity::GetDescription() {
	return description;
}

Entity* Entity::GetEntityByType(Type typeToCheck) {
    for (Entity* entity : contains) {
        if (entity->type == typeToCheck) {
            return entity;
        }
    }
    return nullptr; 
}
