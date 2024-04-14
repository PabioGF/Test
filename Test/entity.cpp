#include <iostream>
#include <string>  
#include <conio.h>
#include "room.h"
#include "entity.h"

using namespace std;


void Entity::Update() {

}

string Entity::GetName() {
	return name;
}

string Entity::GetDescription() {
	return description;
}

bool Entity::LookType(Entity* entity, Type type){
	return false;
}