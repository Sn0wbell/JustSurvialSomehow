#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Character.h"

class Enemy : public Character {
public:
    static Enemy* create(float health, float maxHealth, float armor, float attack, float attackRange, float speed, float attackCooldown);
    virtual bool init(float health, float maxHealth, float armor, float attack, float attackRange, float speed, float attackCooldown);

    void update(float delta);

    float getAttackCooldown() const { return attackCooldown; }
    float getLastAttackTime() const { return lastAttackTime; }

    void setAttackCooldown(float newAttackCooldown) { attackCooldown = newAttackCooldown; }
    void setLastAttackTime(float newLastAttackTime) { lastAttackTime = newLastAttackTime; }

    void attackPlayer();

private:

    float attackCooldown;
    float lastAttackTime;
};

#endif // __ENEMY_H__
