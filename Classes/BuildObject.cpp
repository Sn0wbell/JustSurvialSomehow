#include "BuildObject.h"

USING_NS_CC;

// Constructor implementation

BuildObject* BuildObject::create(ObjectType objectType, const std::string& name, const std::string& spriteFile, BuildObjectType buildObjectType, float durability)
{
    auto handheld = new BuildObject();
    if (handheld != nullptr && handheld->initWithFile(spriteFile)) {
        handheld->init(objectType, name, buildObjectType, durability);
        handheld->autorelease();
        return handheld;
    }

    CC_SAFE_DELETE(handheld);
    return nullptr;
}

bool BuildObject::init(ObjectType objectType, const std::string& name, BuildObjectType buildObjectType, float durability) {
    if (!Object::init(objectType, name, durability)) {
        return false;
    }
    this->buildObjectType = buildObjectType;

    this->scheduleUpdate();
    return true;
}

// Getters
BuildObject::BuildObjectType BuildObject::getBuildObjectType() const { return buildObjectType; }

// Method to build the BuildObject
bool BuildObject::build() {
    // Here you would handle the logic for actually constructing the BuildObject,
    // such as checking for sufficient resources and placing the BuildObject in the game world.
    CCLOG("BuildObject %s constructed!", _name.c_str());
    return true; // Assume success for now
}
