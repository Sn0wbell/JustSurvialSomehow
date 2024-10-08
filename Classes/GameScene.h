#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include <string>

USING_NS_CC;

class GameScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(GameScene);

private:
    void update(float delta);
    void createPlayer();
    void createEnemy();
    void createMap();
    void handleInput();
    void onMouseDown(EventMouse* event);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    void updatePlayerMovement();
    bool onContactBegin(PhysicsContact& contact);

    Player* player; 
    Enemy* enemy;
    std::set<EventKeyboard::KeyCode> pressedKeys;
};

#endif // __GAMESCENE_H__
