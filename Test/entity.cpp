#include <iostream>
#include <string>  
#include <conio.h>
#include "room.h"
#include "entity.h"

using namespace std;

/**
 * Constructs an entity object with the given name and description.
 *
 * @param name The name of the entity
 * @param description The description of the entity
 */
Entity::Entity(const std::string& name, const std::string& description) : name(name), description(description) {
    contains.push_back(this);
}

/**
 * Updates the entity.
 */
void Entity::Update() {

}
/**
 * Retrieves the name of the entity.
 *
 * @return The name of the entity
 */
string Entity::GetName() {
	return name;
}

/**
 * Retrieves the description of the entity.
 *
 * @return The description of the entity
 */
string Entity::GetDescription() {
	return description;
}


/**
 * Retrieves the entity of the specified type.
 *
 * @param typeToCheck The type of entity to retrieve
 * @return The entity of the specified type, or nullptr if not found
 */
Entity* Entity::GetEntityByType(Type typeToCheck) {
    for (Entity* entity : contains) {
        if (entity->type == typeToCheck) {
            return entity;
        }
    }
    return nullptr; 
}

/**
 * Retrieves the entity of the specified type and name.
 *
 * @param typeToCheck The type of entity to retrieve
 * @param name The name of the entity to retrieve
 * @return The entity of the specified type and name, or nullptr if not found
 */
Entity* Entity::GetEntityByTypeName(Type typeToCheck, string name) {
    for (Entity* entity : contains) {
        if (entity->type == typeToCheck) {
            
            if (entity->GetName() == name) {
                
                return entity;
            }
        }
    }
    return nullptr;
}
