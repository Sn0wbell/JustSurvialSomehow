#include "Enemy.h"
#include "Player.h"

USING_NS_CC;

Enemy* Enemy::create(float health, float maxHealth, float armor, float attack, float attackRange, float speed, float attackCooldown) {
    Enemy* enemy = new Enemy();
    if (enemy) {
        enemy->init(health, maxHealth, armor, attack, attackRange, speed, attackCooldown);
        enemy->autorelease();
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return nullptr;
}

bool Enemy::init(float health, float maxHealth, float armor, float attack, float attackRange, float speed, float attackCooldown) {
    if (!Character::init(health, maxHealth, armor, attack, attackRange, speed)) { // Initialize base class
        return false;
    }
    this->attackCooldown = attackCooldown;
    this->lastAttackTime = 0.0f;
    this->scheduleUpdate();
    return true;
}

void Enemy::update(float delta) {
    auto player = dynamic_cast<Player*>(getParent()->getChildByName("player"));
    if (player) {
        // Get positions
        auto enemyPosition = this->getPosition(); // Assuming getPosition() returns a Vec2 or similar type
        auto playerPosition = player->getPosition();

        // Calculate direction towards the player
        Vec2 direction = playerPosition - enemyPosition;
        float distance = direction.length(); // Get the distance to the player

        // Normalize the direction vector to get the unit vector
        if (distance > 0) {
            direction.normalize(); // Normalize the vector to get the direction

            enemyPosition += direction * speed * delta;

            // Set the new position of the enemy
            this->setPosition(enemyPosition);


            if (direction.x < 0) {
                this->setDirection(Direction::LEFT);
            }
            else {
                this->setDirection(Direction::RIGHT);
            }
            std::string animationName = this->getAnimationName("walk");
            //this->playAnimation(animationName);
        }
        else {
            stopAnimation();
        }
    }

    // Update the attack cooldown timer
    lastAttackTime += delta;
}

void Enemy::attackPlayer() {
    auto player = dynamic_cast<Player*>(getParent()->getChildByName("player"));

    // Check cooldown
    if (lastAttackTime >= attackCooldown) {
        // Example damage calculation
        player->takeDamage(this->attack); // Assume getAttack() returns the enemy's attack value
        lastAttackTime = 0.0f; // Reset the attack timer

        // Play attack animation (optional)
        std::string attackAnimation = this->getAnimationName("attack");
        this->playAnimation(attackAnimation);
    }
}
