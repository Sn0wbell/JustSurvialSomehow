#include "Item.h"

USING_NS_CC;

Item* Item::create(ItemType type, const std::string& name, const std::string& description, const std::string& spriteFile, float effectValue, float durability)
{
    auto item = new Item();
    if (item != nullptr && item->initWithFile(spriteFile)) {
        item->init(type, name, description, effectValue, durability);
        item->autorelease();
        return item;
    }

    CC_SAFE_DELETE(item);
    return nullptr;
}

bool Item::init(ItemType type, const std::string& name, const std::string& description, float effectValue, float durability) {
    if (!Sprite::init()) {
        return false;
    }
    this->itemType = type;
    this->name = name;
    this->description = description;
    this->effectValue = effectValue;
    this->durability = durability;

    this->scheduleUpdate();
    return true;
}

// Getter methods
Item::ItemType Item::getItemType() const { return itemType; }
std::string Item::getItemName() const { return name; }
std::string Item::getDescription() const { return description; }
float Item::getEffectValue() const { return effectValue; }
float Item::getDurability() const { return durability; }

// Method to use the item
void Item::use() {
    switch (itemType) {
    case ItemType::FOOD:
        CCLOG("You have eaten %s. Restored %d health.", _name.c_str(), effectValue);
        durability--;
        break;
    case ItemType::DRINK:
        CCLOG("You have drunk %s. Restored %d hydration.", _name.c_str(), effectValue);
        durability--;
        break;
    default:
        break;
    }
}
