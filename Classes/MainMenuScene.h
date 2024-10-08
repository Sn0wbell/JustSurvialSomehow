#ifndef __MAINMENUSCENE_H__
#define __MAINMENUSCENE_H__

#include "cocos2d.h"

class MainMenuScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(MainMenuScene);

private:
    void startGame(cocos2d::Ref* sender);
    void exitGame(cocos2d::Ref* sender);
    void openSettings(cocos2d::Ref* sender);
    void openCredits(cocos2d::Ref* sender);
    void animateButton(cocos2d::MenuItemLabel* button);
    void createBackground();

    cocos2d::Sprite* backgroundSprite;
};

#endif // __MAINMENUSCENE_H__
