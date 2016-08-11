//
//  StartMenuScene.cpp
//  safari
//
//  Created by Srikanth Talapadi on 14/07/16.
//
//

#include "StartMenuScene.h"
#include "HelloWorldScene.h"
#include "alphamon/SelectAlphamonScene.h"
#include "puzzle/DuelScene.h"
#include "mini_games/PatchTheWallScene.h"
#include "mini_games/CrossTheBridgeScene.h"
#include "mini_games/SmashTheRockScene.h"
#include "mini_games/EndlessRunner.h"
#include "mini_games/Cannon_Ball_Main.h"
#include "mini_games/TraceScene.h"
#include "mini_games/AlphamonFeedScene.h"
#include "mini_games/BajaWordScene.h"

USING_NS_CC;


StartMenu::StartMenu(){
    
}

StartMenu::~StartMenu() {
    
}

Scene *StartMenu::createScene() {
    auto scene = Scene::create();
    auto layer = StartMenu::create();
    scene->addChild(layer);
    return scene;
}

bool StartMenu::init() {
    if (!LayerGradient::initWithColor(Color4B(255, 159, 0, 255), Color4B::BLUE)){
        return false;
    }
	auto menu = Menu::create(createMenu(CAMP),
                             createMenu(FARM_HOUSE),
                             createMenu(MINING_BG),
                             createMenu(ALPHAMON_COMBAT),
                             createMenu(PATCH_THE_WALL),
                             createMenu(CROSS_THE_BRIDGE),
                             createMenu(SMASH_THE_ROCK),
                             createMenu(CANNON_BALL),
                             createMenu(ENDLESS_RUNNER),
                             createMenu(KUNG_FU_ALPHA),
							 createMenu(ALPHAMON_FEED),
                             NULL);
    menu->alignItemsVertically();
    
    addChild(menu);
    
    return true;
}

void StartMenu::startScene(std::string gameName, std::string firstParam, std::string secondParam, std::string thirdParam) {
    if(gameName == ALPHAMON_COMBAT) {
        Director::getInstance()->replaceScene(SelectAlphamon::createScene());
    } else if(gameName == DUEL_SCENE) {
        std::u16string firstParamUTF16;
        StringUtils::UTF8ToUTF16(firstParam, firstParamUTF16);

        std::u16string secondParamUTF16;
        StringUtils::UTF8ToUTF16(secondParam, secondParamUTF16);

        Director::getInstance()->replaceScene(DuelScene::createScene(firstParamUTF16.at(0), secondParamUTF16.at(0)));
    }
    else if(gameName == PATCH_THE_WALL) {
        Director::getInstance()->replaceScene(PatchTheWall::createScene());
    } else if(gameName == CROSS_THE_BRIDGE) {
        Director::getInstance()->replaceScene(CrossTheBridge::createScene());
    } else if(gameName == PATCH_THE_WALL) {
        Director::getInstance()->replaceScene(PatchTheWall::createScene());
    } else if(gameName == SMASH_THE_ROCK) {
        Director::getInstance()->replaceScene(SmashTheRock::createScene());
    } else if(gameName == CANNON_BALL) {
        Director::getInstance()->replaceScene(MainGame::createScene());
    } else if(gameName == ENDLESS_RUNNER) {
        Director::getInstance()->replaceScene(BajaWordScene::createScene());
    } else if(gameName == KUNG_FU_ALPHA) {
        Director::getInstance()->replaceScene(Trace::createScene(0));
    } else if(gameName == ALPHAMON_FEED) {
        Director::getInstance()->replaceScene(AlphamonFeed::createScene());
    } else {
        if(!gameName.empty()) {
            Director::getInstance()->replaceScene(HelloWorld::createScene(gameName,firstParam));
        } else {
            CCLOG("Failed starting scene: %s", gameName.c_str());
        }
        
    }
}

MenuItem* StartMenu::createMenu(std::string name) {
    return MenuItemLabel::create(Label::createWithTTF(name, "fonts/arial.ttf", 100),
                          [&](Ref *sender) {
                              auto labelName = (static_cast<cocos2d::MenuItemLabel*>(sender))->getString();
                              startScene(labelName);
                          });
}


