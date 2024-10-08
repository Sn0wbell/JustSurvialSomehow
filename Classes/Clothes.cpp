#include "Clothes.h"
#include "Player.h" // Include the Player class

USING_NS_CC;

Clothes* Clothes::create(ItemType itemType, const std::string& name, const std::string& description, const std::string& spriteFile, ClothingType clothingType, int armor, float weight, float healthBoost, float effectValue, float durability)
{
    auto clothes = new Clothes();
    if (clothes != nullptr && clothes->initWithFile(spriteFile)) {
        clothes->init(itemType, name, description, clothingType, armor, weight, healthBoost, effectValue, durability);
        clothes->autorelease();
        return clothes;
    }

    CC_SAFE_DELETE(clothes);
    return nullptr;
}

bool Clothes::init(ItemType type, const std::string& name, const std::string& description, ClothingType clothingType, int armor, float weight, float healthBoost, float effectValue, float durability) {
    if (!Item::init(type, name, description, effectValue, durability)) {
        return false;
    }
    this->clothingType = clothingType;
    this->armor = armor;
    this->weight = weight;
    this->healthBoost = healthBoost;

    this->scheduleUpdate();
    return true;
}

// Getters
Clothes::ClothingType Clothes::getClothingType() const { return clothingType; }
float Clothes::getArmor() const { return armor; }
float Clothes::getWeight() const { return weight; }
float Clothes::getHealthBoost() const { return healthBoost; }

// Method to wear the clothes
void Clothes::wear() const {
    CCLOG("Wearing %s with armor value %d, weight %.2f, and health boost %.2f", getName().c_str(), armor, weight, healthBoost);
}

// Method to apply effects to the player
void Clothes::applyToPlayer(Player* player) const {
    wear();
    if (player) {
        player->increaseArmor(armor);
        player->decreaseSpeed(weight);
        player->increaseMaxHealth(healthBoost); // Apply health boost
        CCLOG("%s applied to player. Armor increased by %d, speed decreased by %.2f, health increased by %.2f",
            getName().c_str(), armor, weight, healthBoost);
    }
}

// Method to unapplied effects from the player
void Clothes::unapplyFromPlayer(Player* player) const {
    wear();
    if (player) {
        player->decreaseArmor(armor); // Assuming decreaseArmor method exists
        player->increaseSpeed(weight); // Assuming increaseSpeed method exists
        player->decreaseMaxHealth(healthBoost); // Remove health boost (subtract)
        CCLOG("%s unapplied from player. Armor decreased by %d, speed increased by %.2f, health decreased by %.2f",
            getName().c_str(), armor, weight, healthBoost);
    }
}
