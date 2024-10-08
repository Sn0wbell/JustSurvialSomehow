#include "Player.h"
#include "Item.h"
#include "Resource.h"
#include "BuildObject.h"
#include "Building.h"
#include <vector>

USING_NS_CC;

Player* Player::create(float health, float maxHealth, float armor, float attack, float attackRange, float speed, float stamina, float maxStamina, float hunger, int level)
{
    auto player = new Player();
    if (player != nullptr) {
        player->init(health, maxHealth, armor, attack, attackRange, speed, stamina, maxStamina, hunger, level);
        player->autorelease();
        return player;
    }

    CC_SAFE_DELETE(player);
    return nullptr;
}

bool Player::init(float health, float maxHealth, float armor, float attack, float attackRange, float speed, float stamina, float maxStamina, float hunger, int level) {
    if (!Character::init(health, maxHealth, armor, attack, attackRange, speed)) {
        return false;
    }
    this->stamina = stamina;
    this->maxStamina = maxStamina;
    this->hunger = hunger;
    this->level = level;

    this->scheduleUpdate();
    return true;
}

// Add an item to the inventory
void Player::addItem(Item* item) {
    if (item) {
        inventory.push_back(item);
        CCLOG("Added item: %s", item->getName().c_str());
    }
}

// Use an item from the inventory
void Player::useItem(const std::string& itemName) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if ((*it)->getName() == itemName) {
            (*it)->use();
            inventory.erase(it); // Remove item after use (optional)
            return;
        }
    }
    CCLOG("Item %s not found in inventory.", itemName.c_str());
}

// Craft an item using the crafting system
void Player::craftItem(const std::string& itemName) {
    if (craftingSystem.craft(itemName)) {
        // For demonstration, add a crafted item directly
        addItem(nullptr); // Replace with actual crafted item
    }
}

// Other methods
void Player::run(const cocos2d::Vec2& direction) {
    if (stamina > 0) {
        Vec2 newPosition = getPosition() + direction * speed * Director::getInstance()->getDeltaTime();

        // Optionally, check for screen boundaries to prevent moving off-screen
        if (newPosition.x >= 0 && newPosition.x <= Director::getInstance()->getVisibleSize().width &&
            newPosition.y >= 0 && newPosition.y <= Director::getInstance()->getVisibleSize().height) {
            setPosition(newPosition);
            stamina -= 1.0f; // Decrease stamina while moving
        }
    }
}

void Player::update(float delta) {
    Character::update(delta);
}

void Player::eat(float amount) {
    // Eating logic here
}

void Player::restoreStamina(float amount) {
    stamina += amount;
}

void Player::restoreHealth(float amount) {
    // Restore health logic here
}

void Player::increaseArmor(int amount) {
    armor += amount; // Assuming armor is a member variable
    CCLOG("Player armor increased by %d. New armor: %.2f", amount, armor);
}

void Player::decreaseArmor(int amount) {
    armor -= amount;
    if (armor < 0) {
        armor = 0; // Prevent negative armor
    }
    CCLOG("Player armor decreased by %d. New armor: %.2f", amount, armor);
}

void Player::decreaseSpeed(float amount) {
    speed -= amount; // Adjust player speed downwards
    if (speed < 0) {
        speed = 0; // Prevent negative speed
    }
    CCLOG("Player speed decreased by %.2f. New speed: %.2f", amount, speed);
}

void Player::increaseSpeed(float amount) {
    speed += amount; // Restore player speed
    CCLOG("Player speed increased by %.2f. New speed: %.2f", amount, speed);
}

void Player::decreaseAttack(float amount) {
    attack -= amount;
    if (attack < 0) {
        attack = 0;
    }
    CCLOG("Player attack decreased by %.2f. New attack: %.2f", amount, attack);
}

void Player::increaseAttack(float amount) {
    attack += amount;
    CCLOG("Player attack increased by %.2f. New attack: %.2f", amount, attack);
}

void Player::decreaseMaxHealth(float amount) {
    maxHealth -= amount;
    if (maxHealth < 0) {
        maxHealth = 0;
    }
    if (health > maxHealth) {
        health = maxHealth;
    }
    CCLOG("Player max health decreased by %.2f. New max health: %.2f", amount, maxHealth);
}

void Player::increaseMaxHealth(float amount) {
    maxHealth += amount;
    restoreHealth(amount);
    CCLOG("Player max health increased by %.2f. New max health: %.2f", amount, maxHealth);
}

bool Player::equipClothes(Clothes* clothes) {
    if (!clothes) return false;

    switch (clothes->getClothingType()) {
    case Clothes::ClothingType::HELMET:
        if (_helmet) {
            unequipClothes(Clothes::ClothingType::HELMET);
        }
        _helmet = clothes;
        clothes->applyToPlayer(this);
        CCLOG("Equipped %s as helmet.", clothes->getItemName().c_str());
        break;
    case Clothes::ClothingType::BODY_ARMOR:
        if (_bodyArmor) {
            unequipClothes(Clothes::ClothingType::BODY_ARMOR);
        }
        _bodyArmor = clothes;
        clothes->applyToPlayer(this);
        CCLOG("Equipped %s as body armor.", clothes->getItemName().c_str());
        break;
    case Clothes::ClothingType::ARM_ARMOR:
        if (_armArmor) {
            unequipClothes(Clothes::ClothingType::ARM_ARMOR);
        }
        _armArmor = clothes;
        clothes->applyToPlayer(this);
        CCLOG("Equipped %s as arm armor.", clothes->getItemName().c_str());
        break;
    case Clothes::ClothingType::LEG_ARMOR:
        if (_legArmor) {
            unequipClothes(Clothes::ClothingType::LEG_ARMOR);
        }
        _legArmor = clothes;
        clothes->applyToPlayer(this);
        CCLOG("Equipped %s as leg armor.", clothes->getItemName().c_str());
        break;
    default:
        return false; // Unsupported clothing type
    }
    return true;
}

void Player::unequipClothes(Clothes::ClothingType type) {
    switch (type) {
    case Clothes::ClothingType::HELMET:
        if (_helmet) {
            _helmet->unapplyFromPlayer(this);
            CCLOG("Unequipped %s from helmet.", _helmet->getItemName().c_str());
            _helmet = nullptr;
        }
        break;
    case Clothes::ClothingType::BODY_ARMOR:
        if (_bodyArmor) {
            _bodyArmor->unapplyFromPlayer(this);
            CCLOG("Unequipped %s from body armor.", _bodyArmor->getItemName().c_str());
            _bodyArmor = nullptr;
        }
        break;
    case Clothes::ClothingType::ARM_ARMOR:
        if (_armArmor) {
            _armArmor->unapplyFromPlayer(this);
            CCLOG("Unequipped %s from arm armor.", _armArmor->getItemName().c_str());
            _armArmor = nullptr;
        }
        break;
    case Clothes::ClothingType::LEG_ARMOR:
        if (_legArmor) {
            _legArmor->unapplyFromPlayer(this);
            CCLOG("Unequipped %s from leg armor.", _legArmor->getItemName().c_str());
            _legArmor = nullptr;
        }
        break;
    default:
        break;
    }
}

bool Player::equipHandheld(Handheld* handheld) {
    if (!handheld || (_handheld && (_handheld->getHandheldType() == Handheld::HandheldType::WEAPON || _handheld->getHandheldType() == Handheld::HandheldType::TOOL))) {
        // Can't equip another handheld if one is already equipped
        return false;
    }

    if (_handheld) {
        unequipHandheld();
    }

    _handheld = handheld;
    handheld->applyToPlayer(this);
    CCLOG("Equipped %s as handheld.", handheld->getItemName().c_str());
    return true;
}

void Player::unequipHandheld() {
    if (_handheld) {
        _handheld->unapplyFromPlayer(this);
        CCLOG("Unequipped %s from handheld.", _handheld->getItemName().c_str());
        _handheld = nullptr;
    }
}

bool Player::equipShield(Handheld* shield) {
    if (!shield || (_shield && (_shield->getHandheldType() == Handheld::HandheldType::SHIELD))) {
        // Can't equip another handheld if one is already equipped
        return false;
    }

    if (_shield) {
        unequipHandheld();
    }

    _shield = shield;
    shield->applyToPlayer(this);
    CCLOG("Equipped %s as handheld.", shield->getItemName().c_str());
    return true;
}

void Player::unequipShield() {
    if (_shield) {
        _shield->unapplyFromPlayer(this);
        CCLOG("Unequipped %s from handheld.", _shield->getItemName().c_str());
        _shield = nullptr;
    }
}

void Player::buildStructure(BuildObject::BuildObjectType type, const cocos2d::Vec2& position) {
    Building Building; // You would typically want to keep this as a member
    BuildObject* BuildObject = Building.createBuildObject(type);
    if (Building.canBuild(*BuildObject)) {
        Building.placeBuildObject(BuildObject, position);
    }
    else {
        CCLOG("Not enough resources to build %s!", BuildObject->getName().c_str());
    }
}

void Player::performAttack() {
    _isAttacking = true;
    Character::performAttack(cntAttack);
    cntAttack++;
    if (cntAttack > 3) cntAttack = 1;

    this->scheduleOnce([this](float) { _isAttacking = false; }, 0.3, "resetAttack");
}