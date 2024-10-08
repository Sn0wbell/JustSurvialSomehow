#include "Character.h"

USING_NS_CC;

Character* Character::create(float health, float maxHealth, float armor, float attack, float attackRange, float speed)
{
    auto character = new Character();
    if (character != nullptr) {
        character->init(health, maxHealth, armor, attack, attackRange, speed);
        character->autorelease();
        return character;
    }

    CC_SAFE_DELETE(character);
    return nullptr;
}

bool Character::init(float health, float maxHealth, float armor, float attack, float attackRange, float speed) {
    if (!Sprite::init()) {
        return false;
    }
    this->health = health;
    this->maxHealth = maxHealth;
    this->armor = armor;
    this->attack = attack;
    this->attackRange = attackRange;
    this->speed = speed;

    this->scheduleUpdate();
    return true;
}

void Character::update(float deltaTime) {
    if (!isRunningAction()) {
        this->standIdle();
    }
}

bool Character::isRunningAction() const {
    return this->getNumberOfRunningActions() > 0;
}

std::string Character::getAnimationName(const std::string& animationName)
{
    if (this->direction == Direction::LEFT) {
        return this->animationName + "_" + animationName + "_left";
    }
    else {
        return this->animationName + "_" + animationName + "_right";
    }
}

bool Character::loadAnimation(const std::string& plistFile, const std::string& animationName) {

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistFile);

    Vector<SpriteFrame*> frames;

    int count = 1;
    while (true)
    {
        std::string frameNumber = std::to_string(count);

        std::string frameName = "./" + animationName + "_" + frameNumber;

        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName);
        if (frame == nullptr) {
            break;
        }
        else {
            frames.pushBack(frame);
            count++;
        }
    }

    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
    Animate* animate = Animate::create(animation);
    this->animations.insert(animationName, animate);
    return true;
}

void Character::playAnimation(const std::string& animationName, bool loop) {
    for (auto& animation : this->animations) {
        if (animation.first == animationName) {
            this->stopAllActions();
            auto animate = animation.second;
            if (loop) {
                auto repeat = RepeatForever::create(animate);
                this->runAction(repeat);
            }
            else
            {
                this->runAction(animate);
            }
            return;
        }
    }
}

void Character::stopAnimation() {
    this->stopAllActions();
}

void Character::decreaseHealth(float amount) {
    float effectiveDamage = amount - this->armor;
    if (effectiveDamage < 0) {
        effectiveDamage = 0;
    }

    health -= effectiveDamage;

    if (health < 0) {
        health = 0;
        // Handle character death (e.g., remove from scene or trigger death animation)
        this->removeFromParentAndCleanup(true);
    }
}

// Setter for health to ensure it does not exceed maxHealth
void Character::setHealth(float newHealth) {
    if (newHealth > this->maxHealth) {
        newHealth = this->maxHealth;
    }
    health = newHealth;
}

void Character::standIdle() {
    std::string animationName;
    animationName = getAnimationName("idle");
    this->playAnimation(animationName, true);
}

void Character::moveInDirection(Direction moveDirection) {
    cocos2d::Vec2 movementVector;
    switch (moveDirection) {
    case Direction::NONE:
        return;
        break;
    case Direction::LEFT:
        this->direction = Direction::LEFT;
        movementVector = cocos2d::Vec2(-1, 0);
        break;
    case Direction::RIGHT:
        this->direction = Direction::RIGHT;
        movementVector = cocos2d::Vec2(1, 0);
        break;
    case Direction::UP:
        movementVector = cocos2d::Vec2(0, 1);
        break;
    case Direction::DOWN:
        movementVector = cocos2d::Vec2(0, -1);
        break;
    case Direction::UP_LEFT:
        this->direction = Direction::LEFT;
        movementVector = cocos2d::Vec2(-1, 1);
        break;
    case Direction::UP_RIGHT:
        this->direction = Direction::RIGHT;
        movementVector = cocos2d::Vec2(1, 1);
        break;
    case Direction::DOWN_LEFT:
        this->direction = Direction::LEFT;
        movementVector = cocos2d::Vec2(-1, -1);
        break;
    case Direction::DOWN_RIGHT:
        this->direction = Direction::RIGHT;
        movementVector = cocos2d::Vec2(1, -1);
        break;
    }

    std::string animationName = getAnimationName("walk");

    // Normalize the movement vector to keep consistent speed
    movementVector.normalize();

    // Get the animation associated with the provided animation name
    Animate* animate = this->animations.at(animationName);

    // Create the movement action using the speed and direction
    auto move = MoveBy::create(animate->getDuration(), movementVector * this->speed);
        

    // Stop any currently running animation
    this->stopAnimation();

    // Run the combined action
    auto action = Spawn::createWithTwoActions(move, animate);

    this->runAction(action);
}

void Character::performAttack(int cntAttack) {
    std::string animationName;
    if(cntAttack == 0) animationName = getAnimationName("attack");
    else animationName = getAnimationName("attack" + std::to_string(cntAttack));

    if (!animationName.empty()) {
        this->playAnimation(animationName, false); // Play the attack animation
    }
}

void Character::takeDamage(float damage) {
    log("Enemy taked damage!");
    std::string animationName;
    // Calculate effective damage after considering armor
    float effectiveDamage = damage - armor;
    if (effectiveDamage < 0) {
        effectiveDamage = 0; // Prevent healing from damage
    }

    // Reduce health
    health -= effectiveDamage;

    if (effectiveDamage != 0)
    {
        animationName = getAnimationName("hurt");
        this->playAnimation(animationName, false);
    }

    // Check for death
    if (health <= 0) {
        health = 0;
        animationName = getAnimationName("death");
        if (!animationName.empty()) {
            this->playAnimation(animationName, false);
        }
    }
}

