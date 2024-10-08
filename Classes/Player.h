#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Character.h"
#include "Item.h"
#include "Crafting.h"
#include "Building.h"
#include "Resource.h"
#include "Clothes.h"
#include "Handheld.h"
#include "BuildObject.h"
#include <vector>

class Player : public Character {
public:
    static Player* create(float health, float maxHealth, float armor, float attack, float attackRange, float speed, float stamina, float maxStamina, float hunger, int level);
    virtual bool init(float health, float maxHealth, float armor, float attack, float attackRange, float speed, float stamina, float maxStamina, float hunger, int level);

    void run(const cocos2d::Vec2& direction);

    void update(float delta);

    // Player-specific methods
    void eat(float amount);
    void restoreStamina(float amount);
    void restoreHealth(float amount);
    void increaseArmor(int amount);
    void decreaseArmor(int amount);
    void decreaseSpeed(float amount);
    void increaseSpeed(float amount);
    void decreaseAttack(float amount);
    void increaseAttack(float amount);
    void decreaseMaxHealth(float amount);
    void increaseMaxHealth(float amount);

    // Inventory methods
    void addItem(Item* item);
    void useItem(const std::string& itemName);
    void craftItem(const std::string& itemName);

    // Equip and unequip methods
    bool equipClothes(Clothes* clothes);
    void unequipClothes(Clothes::ClothingType type);
    bool equipHandheld(Handheld* handheld); // For weapons/tools
    void unequipHandheld();
    bool equipShield(Handheld* shield);
    void unequipShield();

    void buildStructure(BuildObject::BuildObjectType type, const cocos2d::Vec2& position);

    float getStamina() const { return stamina; }
    float getMaxStamina() const { return maxStamina; }
    float getHunger() const { return hunger; }
    int getLevel() const { return level; }
    int getCountAttack() const { return cntAttack; }
    bool isAttacking() const { return this->_isAttacking; }

    void setStamina(float newStamina) { stamina = newStamina; }
    void setMaxStamina(float newMaxStamina) { maxStamina = newMaxStamina; }
    void setHunger(float newHunger) { hunger = newHunger; }
    void setLevel(int newLevel) { level = newLevel; }

    void performAttack();

private:
    bool _isAttacking;
    int cntAttack = 1;
    float stamina;
    float maxStamina;
    float hunger;
    const float maxHunger = 100;
    int level;
    std::vector<Item*> inventory;  // Inventory to hold items
    Crafting craftingSystem;        // Crafting system for crafting items

    // Equipped items
    Clothes* _helmet = nullptr;
    Clothes* _bodyArmor = nullptr;
    Clothes* _armArmor = nullptr;
    Clothes* _legArmor = nullptr;
    Handheld* _handheld = nullptr; // Can be weapon/tool
    Handheld* _shield = nullptr;
};

#endif // __PLAYER_H__
