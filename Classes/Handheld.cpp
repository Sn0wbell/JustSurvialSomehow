#include "cocos2d.h"
#include "Handheld.h"
#include "Player.h" // Include the Player class

USING_NS_CC;


Handheld* Handheld::create(ItemType itemType, const std::string& name, const std::string& description, const std::string& spriteFile, HandheldType handheldType, float attack, float defense, float effectValue, float durability)
{
    auto handheld = new Handheld();
    if (handheld != nullptr && handheld->initWithFile(spriteFile)) {
        handheld->init(itemType, name, description, handheldType, attack, defense, effectValue, durability);
        handheld->autorelease();
        return handheld;
    }

    CC_SAFE_DELETE(handheld);
    return nullptr;
}

bool Handheld::init(ItemType itemType, const std::string& name, const std::string& description, HandheldType handheldType, int attack, int defense, float effectValue, float durability) {
    if (!Item::init(itemType, name, description, effectValue, durability)) {
        return false;
    }
    this->handheldType = handheldType;
    this->attackPower = attack;
    this->defensePower = defense;

    this->scheduleUpdate();
    return true;
}

// Getter methods
Handheld::HandheldType Handheld::getHandheldType() const { return handheldType; }
float Handheld::getAttack() const { return attackPower; }
float Handheld::getDefense() const { return defensePower; }

// Overridden use method
void Handheld::use() {
    switch (handheldType) {
    case HandheldType::TOOL:
        CCLOG("Using tool: %s", getItemName().c_str());
        // Implement tool-specific behavior here
        attack();
        break;
    case HandheldType::WEAPON:
        CCLOG("Attacking with weapon: %s, Attack: %d", getItemName().c_str(), attackPower);
        attack();
        break;
    case HandheldType::SHIELD:
        CCLOG("Equipping shield: %s, Defense: %d", getItemName().c_str(), defensePower);
        defense();
        break;
    default:
        break;
    }
}

// Attack method for weapons and tools
void Handheld::attack() {
    if (durability > 0) {
        CCLOG("%s has attacked! Durability left: %f", name.c_str(), durability);
        durability--; // Decrease durability with each attack
    }
    else {
        CCLOG("%s is broken and cannot be used!", name.c_str());
    }
}

void Handheld::defense() {
    if (durability > 0) {
        CCLOG("%s has defensed! Durability left: %f", name.c_str(), durability);
        durability--; // Decrease durability with each attack
    }
    else {
        CCLOG("%s is broken and cannot be used!", name.c_str());
    }
}


// Method to apply effects to the player
void Handheld::applyToPlayer(Player* player) const {
    if (player) {
        if (handheldType == HandheldType::WEAPON ||
            handheldType == HandheldType::TOOL) {
            player->increaseAttack(attackPower); // Assuming Player has an increaseAttack method
            CCLOG("%s equipped. Attack increased by %f.", getItemName().c_str(), attackPower);
        }
    }
}

// Method to unapplied effects from the player
void Handheld::unapplyFromPlayer(Player* player) const {
    if (player) {
        if (handheldType == HandheldType::WEAPON ||
            handheldType == HandheldType::TOOL) {
            player->decreaseAttack(attackPower); // Assuming Player has an decreaseAttack method
            CCLOG("%s equipped. Attack increased by %d.", getItemName().c_str(), attackPower);
        }
    }
}
