#ifndef __CREDITSCENE_H__
#define __CREDITSCENE_H__

#include "cocos2d.h"

class CreditsScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(CreditsScene);
};

#endif // __CREDITSCENE_H__
