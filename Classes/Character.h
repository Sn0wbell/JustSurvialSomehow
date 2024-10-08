#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"

enum class Direction {
    NONE,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT
};

class Character : public cocos2d::Sprite {
public:
    static Character* create(float health, float maxHealth, float armor, float attack, float attackRange, float speed);
    virtual bool init(float health, float maxHealth, float armor, float attack, float attackRange, float speed);
    void update(float deltaTime);
    bool isRunningAction() const;

    void decreaseHealth(float amount);

    float getHealth() const { return health; }
    float getMaxHealth() const { return maxHealth; }
    float getArmor() const { return armor; }
    float getAttack() const { return attack; }
    float getAttackRange() const { return attackRange; }
    float getSpeed() const { return speed; }
    Direction getDirection() const { return direction; }
    std::string getAnimationName(const std::string& animationName);

    void setHealth(float newHealth);
    void setMaxHealth(float newMaxHealth) { maxHealth = newMaxHealth; }
    void setArmor(float newArmor) { armor = newArmor; }
    void setAttack(float newAttack) { attack = newAttack; }
    void setAttackRange(float newAttackRange) { attackRange = newAttackRange; }
    void setSpeed(float newSpeed) { speed = newSpeed; }
    void setDirection(Direction newDirection) { direction = newDirection; }
    void setAnimationName(const std::string& newAnimationName) { animationName = newAnimationName; }

    // Movement functions
    void moveInDirection(Direction moveDirection);

    bool loadAnimation(const std::string& plistFile, const std::string& animationName);
    void playAnimation(const std::string& animationName, bool loop = false);
    void stopAnimation();
    void standIdle();

    void performAttack(int cntAttack = 0);
    void takeDamage(float damage);

protected:
    float health;
    float maxHealth;
    float armor;
    float attack;
    float attackRange;
    float speed;
    cocos2d::Map<std::string, cocos2d::Animate*> animations; 
    Direction direction = Direction::LEFT;
    std::string animationName;
};

#endif // __CHARACTER_H__
