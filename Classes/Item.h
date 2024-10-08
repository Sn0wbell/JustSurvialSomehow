#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include <vector>
#include <string>

class Item : public cocos2d::Sprite {
public:
    // Enum for item types
    enum class ItemType {
        FOOD,
        DRINK,
        HANDHELD,
        CLOTHES,
        RESOURCE
    };

    
    static Item* create(ItemType type, const std::string& name, const std::string& description, const std::string& spriteFile, float effectValue = 0, float durability = 0);
    virtual bool init(ItemType type, const std::string& name, const std::string& description, float effectValue, float durability);

    // Getter methods
    ItemType getItemType() const;
    std::string getItemName() const;
    std::string getDescription() const;
    float getEffectValue() const;
    float getDurability() const;

    // Method to use the item
    void use();

protected:
    ItemType itemType;
    std::string name;
    std::string description;
    std::string spriteFile;
    float effectValue; // Example: health restoration amount, hydration level, etc.
    float durability;   // Durability of the item
};

#endif // __ITEM_H__
