#ifndef __SETTINGSSCENE_H__
#define __SETTINGSSCENE_H__

#include "cocos2d.h"

class SettingsScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(SettingsScene);
};

#endif // __SETTINGSSCENE_H__
