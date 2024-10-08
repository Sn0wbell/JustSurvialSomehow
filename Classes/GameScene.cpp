#include "GameScene.h"
#include "MainMenuScene.h"
#include "Player.h"
#include <string>

USING_NS_CC;

static auto visibleSize = Director::getInstance()->getVisibleSize();
static Vec2 origin = Director::getInstance()->getVisibleOrigin();
static int centerX = visibleSize.width / 2;
static int centerY = visibleSize.height / 2;

Scene* GameScene::createScene() {
    return GameScene::create();
}

bool GameScene::init() {
    if (!Scene::initWithPhysics()) {
        return false;
    }

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    _physicsWorld->setGravity(Vec2(0, 0));


    createMap();

    createPlayer();
    player->standIdle();

    createEnemy();
    enemy->standIdle();

    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::update));

    return true;
}

void GameScene::createMap() {
    auto map = Sprite::create("map/map-desert-1.png");
    if (map)
    {
        map->setPosition(Vec2(centerX, centerY));
        this->addChild(map, -100);
    }
}

void GameScene::createPlayer() {
    player = Player::create(100.0, 100.0, 5.0, 10.0, 1.0, 100.0, 100.0, 100.0, 100.0, 1);
    player->initWithFile("player/male/male_player.png");
    player->setPosition(Vec2(centerX, centerY));
    player->loadAnimation("player/male/male_player_attack1_left.plist","male_player_attack1_left");
    player->loadAnimation("player/male/male_player_attack1_right.plist","male_player_attack1_right");
    player->loadAnimation("player/male/male_player_attack2_left.plist","male_player_attack2_left");
    player->loadAnimation("player/male/male_player_attack2_right.plist","male_player_attack2_right");
    player->loadAnimation("player/male/male_player_attack3_left.plist","male_player_attack3_left");
    player->loadAnimation("player/male/male_player_attack3_right.plist","male_player_attack3_right");
    player->loadAnimation("player/male/male_player_craft.plist","male_player_craft");
    player->loadAnimation("player/male/male_player_death_left.plist","male_player_death_left");
    player->loadAnimation("player/male/male_player_death_right.plist","male_player_death_right");
    player->loadAnimation("player/male/male_player_hurt_left.plist","male_player_hurt_left");
    player->loadAnimation("player/male/male_player_hurt_right.plist","male_player_hurt_right");
    player->loadAnimation("player/male/male_player_idle_left.plist","male_player_idle_left");
    player->loadAnimation("player/male/male_player_idle_right.plist","male_player_idle_right");
    player->loadAnimation("player/male/male_player_run_left.plist","male_player_run_left");
    player->loadAnimation("player/male/male_player_run_right.plist","male_player_run_right");
    player->loadAnimation("player/male/male_player_walk_left.plist","male_player_walk_left");
    player->loadAnimation("player/male/male_player_walk_right.plist","male_player_walk_right");
    player->setDirection(Direction::LEFT);
    player->setAnimationName("male_player");
    player->setName("player");
    auto physicsBody = PhysicsBody::createBox(player->getContentSize());
    physicsBody->setDynamic(true);
    physicsBody->setCategoryBitmask(0x1); // Player category
    physicsBody->setContactTestBitmask(0x2); // Contact with enemy category
    physicsBody->setRotationEnable(false);
    player->setPhysicsBody(physicsBody);
    this->addChild(player, 100);
}

void GameScene::createEnemy() {
    enemy = Enemy::create(100.0, 100.0, 5.0, 30.0, 1.0, 20.0, 1.0);
    enemy->initWithFile("enemy/orc/orc1/orc1.png");
    enemy->setPosition(Vec2(centerX + 500, centerY + 300));
    enemy->loadAnimation("enemy/orc/orc1/orc1_attack_left.plist", "orc1_attack_left");
    enemy->loadAnimation("enemy/orc/orc1/orc1_attack_right.plist", "orc1_attack_right");
    enemy->loadAnimation("enemy/orc/orc1/orc1_death_left.plist", "orc1_death_left");
    enemy->loadAnimation("enemy/orc/orc1/orc1_death_right.plist", "orc1_death_right");
    enemy->loadAnimation("enemy/orc/orc1/orc1_hurt_left.plist", "orc1_hurt_left");
    enemy->loadAnimation("enemy/orc/orc1/orc1_hurt_right.plist", "orc1_hurt_right");
    enemy->loadAnimation("enemy/orc/orc1/orc1_idle_left.plist", "orc1_idle_left");
    enemy->loadAnimation("enemy/orc/orc1/orc1_idle_right.plist", "orc1_idle_right");
    enemy->loadAnimation("enemy/orc/orc1/orc1_walk_left.plist", "orc1_walk_left");
    enemy->loadAnimation("enemy/orc/orc1/orc1_walk_right.plist", "orc1_walk_right");
    enemy->setDirection(Direction::LEFT);
    enemy->setAnimationName("orc1");
    auto physicsBody = PhysicsBody::createBox(enemy->getContentSize() / 2);
    physicsBody->setDynamic(true);
    physicsBody->setCategoryBitmask(0x2); // Enemy category
    physicsBody->setContactTestBitmask(0x1); // Contact with player category
    physicsBody->setRotationEnable(false);
    enemy->setPhysicsBody(physicsBody);

    this->addChild(enemy, 50);
}

void GameScene::update(float delta) {
    handleInput();
    auto camera = Director::getInstance()->getRunningScene()->getDefaultCamera();
    camera->setPosition(player->getPosition());
}

void GameScene::handleInput() {
    auto director = Director::getInstance();

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(GameScene::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void GameScene::onMouseDown(EventMouse* event) {
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT) {
        if (player) {
            player->performAttack();
        }
    }
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    // Add the key to the set of pressed keys
    pressedKeys.insert(keyCode);
    updatePlayerMovement();
}

void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
    // Remove the key from the set of pressed keys
    pressedKeys.erase(keyCode);
}

void GameScene::updatePlayerMovement() {
    Direction moveDirection = Direction::NONE;
    if (pressedKeys.count(EventKeyboard::KeyCode::KEY_W)) { // Move up
        moveDirection = Direction::UP;
    }
    if (pressedKeys.count(EventKeyboard::KeyCode::KEY_S)) { // Move down
        moveDirection = Direction::DOWN;
    }
    if (pressedKeys.count(EventKeyboard::KeyCode::KEY_A)) { // Move left
        moveDirection = Direction::LEFT;
    }
    if (pressedKeys.count(EventKeyboard::KeyCode::KEY_D)) { // Move right
        moveDirection = Direction::RIGHT;
    }
    if (pressedKeys.count(EventKeyboard::KeyCode::KEY_W) && pressedKeys.count(EventKeyboard::KeyCode::KEY_A)) {
        moveDirection = Direction::UP_LEFT;
    }
    else if (pressedKeys.count(EventKeyboard::KeyCode::KEY_W) && pressedKeys.count(EventKeyboard::KeyCode::KEY_D)) {
        moveDirection = Direction::UP_RIGHT;
    }
    else if (pressedKeys.count(EventKeyboard::KeyCode::KEY_S) && pressedKeys.count(EventKeyboard::KeyCode::KEY_A)) {
        moveDirection = Direction::DOWN_LEFT;
    }
    else if (pressedKeys.count(EventKeyboard::KeyCode::KEY_S) && pressedKeys.count(EventKeyboard::KeyCode::KEY_D)) {
        moveDirection = Direction::DOWN_RIGHT;
    }

    player->moveInDirection(moveDirection);
}

bool GameScene::onContactBegin(PhysicsContact& contact) {
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    if (enemy) {
        if ((nodeA == player && nodeB == enemy) || (nodeA == enemy && nodeB == player)) {
            // Check if the player is currently attacking
            if (player->isAttacking()) { // Assuming you have a method that checks if the player is attacking
                enemy->takeDamage(player->getAttack()); // Apply damage from the player
            }
            enemy->attackPlayer();
            return true;
        }
    }
    return false;
}
