#ifndef __HANDHELD_H__
#define __HANDHELD_H__

#include "Item.h"
#include <vector>
#include <string>

class Player; // Forward declaration

class Handheld : public Item {
public:
    // Enum for handheld item types
    enum class HandheldType {
        TOOL,
        WEAPON,
        SHIELD
    };

    static Handheld* create(ItemType itemType, const std::string& name, const std::string& description, const std::string& spriteFile, HandheldType handheldType, float attack, float defense = 0, float effectValue = 0, float durability = 0);
    virtual bool init(ItemType itemType, const std::string& name, const std::string& description, HandheldType handheldType, int attack, int defense, float effectValue, float durability);

    // Getter methods
    HandheldType getHandheldType() const;
    float getAttack() const;
    float getDefense() const;

    void attack();
    void defense();

    void use();

    // Method to apply effects to the player
    void applyToPlayer(Player* player) const;

    // Method to unapplied effects from the player
    void unapplyFromPlayer(Player* player) const;

private:
    HandheldType handheldType;
    float attackPower; // Attack power for weapons
    float defensePower;     // Defense value for shields
};

#endif // __HANDHELD_H__
