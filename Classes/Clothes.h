#ifndef __CLOTHES_H__
#define __CLOTHES_H__

#include "Item.h"
#include <vector>
#include <string>

class Player; // Forward declaration

class Clothes : public Item {
public:
    // Enum for clothing types
    enum class ClothingType {
        HELMET,
        BODY_ARMOR,
        ARM_ARMOR,
        LEG_ARMOR
    };

    static Clothes* create(ItemType itemType, const std::string& name, const std::string& description, const std::string& spriteFile, ClothingType clothingType, int armor, float weight, float healthBoost, float effectValue = 0, float durability = 0);
    virtual bool init(ItemType itemType, const std::string& name, const std::string& description, ClothingType type, int armor, float weight, float healthBoost, float effectValue, float durability);

    // Getters
    ClothingType getClothingType() const;
    float getArmor() const;
    float getWeight() const;
    float getHealthBoost() const;

    // Method to wear the clothes
    void wear() const;

    // Method to apply effects to the player
    void applyToPlayer(Player* player) const;

    // Method to unapply effects from the player
    void unapplyFromPlayer(Player* player) const;

private:
    ClothingType clothingType;  // Clothing type
    float armor;          // Armor value
    float weight;       // Weight value, affects player speed
    float healthBoost;  // Health increase
};

#endif // __CLOTHES_H__
