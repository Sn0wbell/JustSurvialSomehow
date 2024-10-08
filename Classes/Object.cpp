#include "Object.h"

USING_NS_CC;

Object* Object::create(ObjectType objectType, const std::string& name, const std::string& spriteFile, float durability)
{
    auto object = new Object();
    if (object != nullptr && object->initWithFile(spriteFile)) {
        object->init(objectType, name, durability);
        object->autorelease();
        return object;
    }

    CC_SAFE_DELETE(object);
    return nullptr;
}

bool Object::init(ObjectType objectType, const std::string& name, float durability) {
    if (!Sprite::init()) {
        return false;
    }
    this->objectType = objectType;
    this->name = name;
    this->durability = durability;
    this->itemsInclude.clear();

    this->scheduleUpdate();
    return true;
}

ObjectType Object::getType() const { return objectType; }
std::string Object::getObjectName() const { return name; }
float Object::getDurability() const { return durability; }
std::vector<std::pair<std::string, int>> Object::getItemsInclude() const { return itemsInclude; }