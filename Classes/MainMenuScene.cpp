#include "MainMenuScene.h"
#include "GameScene.h"
#include "SettingsScene.h"
#include "CreditsScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene() {
    return MainMenuScene::create();
}

bool MainMenuScene::init() {
    if (!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();

    createBackground(); // Create animated background

    // Create a title label
    auto titleLabel = Label::createWithTTF("Survival Game", "fonts/Marker Felt.ttf", 48);
    titleLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.75));
    titleLabel->setColor(Color3B(255, 215, 0)); // Gold color
    this->addChild(titleLabel);

    // Start Game Button
    auto startButton = MenuItemLabel::create(
        Label::createWithTTF("Start Game", "fonts/Marker Felt.ttf", 32),
        CC_CALLBACK_1(MainMenuScene::startGame, this));
    startButton->setColor(Color3B(0, 255, 0)); // Green color
    animateButton(startButton);

    // Settings Button
    auto settingsButton = MenuItemLabel::create(
        Label::createWithTTF("Settings", "fonts/Marker Felt.ttf", 32),
        CC_CALLBACK_1(MainMenuScene::openSettings, this));
    settingsButton->setColor(Color3B(255, 255, 0)); // Yellow color
    animateButton(settingsButton);

    // Credits Button
    auto creditsButton = MenuItemLabel::create(
        Label::createWithTTF("Credits", "fonts/Marker Felt.ttf", 32),
        CC_CALLBACK_1(MainMenuScene::openCredits, this));
    creditsButton->setColor(Color3B(0, 0, 255)); // Blue color
    animateButton(creditsButton);

    // Exit Game Button
    auto exitButton = MenuItemLabel::create(
        Label::createWithTTF("Exit Game", "fonts/Marker Felt.ttf", 32),
        CC_CALLBACK_1(MainMenuScene::exitGame, this));
    exitButton->setColor(Color3B(255, 0, 0)); // Red color
    animateButton(exitButton);

    // Create a menu and add the buttons
    auto menu = Menu::create(startButton, settingsButton, creditsButton, exitButton, nullptr);
    menu->alignItemsVerticallyWithPadding(20);
    menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(menu);

    return true;
}

void MainMenuScene::createBackground() {
    // Create an animated or static background
    backgroundSprite = Sprite::create("HelloWorld.png"); // Background image
    backgroundSprite->setPosition(Director::getInstance()->getVisibleSize() / 2);
    this->addChild(backgroundSprite);

    // Optionally, create a simple animation for the background
    auto moveBy = MoveBy::create(5, Vec2(0, 10)); // Sample animation
    backgroundSprite->runAction(RepeatForever::create(moveBy));
}

void MainMenuScene::startGame(Ref* sender) {
    auto gameScene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, gameScene));
}

void MainMenuScene::exitGame(Ref* sender) {
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    exit(0);
#endif
}

void MainMenuScene::openSettings(Ref* sender) {
    auto settingsScene = SettingsScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, settingsScene));
}

void MainMenuScene::openCredits(Ref* sender) {
    auto creditsScene = CreditsScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1.0f, creditsScene));
}

void MainMenuScene::animateButton(MenuItemLabel* button) {
    button->runAction(RepeatForever::create(
        Sequence::create(
            ScaleTo::create(0.5f, 1.1f),
            ScaleTo::create(0.5f, 1.0f),
            nullptr)));
}
