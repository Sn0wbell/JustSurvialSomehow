#include "SettingsScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* SettingsScene::createScene() {
    return SettingsScene::create();
}

bool SettingsScene::init() {
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto label = Label::createWithTTF("Settings", "fonts/Marker Felt.ttf", 48);
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.75));
    this->addChild(label);

    auto backButton = MenuItemLabel::create(
        Label::createWithTTF("Back to Menu", "fonts/Marker Felt.ttf", 32),
        [](Ref* sender) {
            auto mainMenuScene = MainMenuScene::createScene();
            Director::getInstance()->replaceScene(TransitionFade::create(1.0f, mainMenuScene));
        });

    auto menu = Menu::create(backButton, nullptr);
    menu->setPosition(visibleSize / 2);
    this->addChild(menu);

    return true;
}
