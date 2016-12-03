//
//  LevelHelpScene.h
//  goa
//
//  Created by Srikanth Talapadi on 01/12/2016.
//
//

#ifndef LevelHelpScene_h
#define LevelHelpScene_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class LevelHelpScene: public cocos2d::Node {
public:
    static cocos2d::Scene *createScene(std::string gameName);
    static LevelHelpScene *create(std::string gameName);
    void onEnterTransitionDidFinish() override;
CC_CONSTRUCTOR_ACCESS:
    LevelHelpScene();
    virtual ~LevelHelpScene();
    virtual bool init() override;
    bool initWithGame(std::string gameName);
protected:
    int _currentLevel;
    std::string _gameName;
    std::string _helpText;
    void gotoGame(Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    void videoEventCallback(Ref* sender, cocos2d::experimental::ui::VideoPlayer::EventType eventType);
#endif
    
    void videoPlayStart(std::string gameName);
    void videoPlayOverCallback();
    
};

#endif /* LevelHelpScene_h */
