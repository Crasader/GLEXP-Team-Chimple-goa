//
//  ScrollableGameMapScene.hpp
//  safari
//
//  Created by Shyamal  Upadhyaya on 12/08/16.
//
//

#ifndef ScrollableGameMapScene_hpp
#define ScrollableGameMapScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "StartMenuScene.h"
#include "external/json/document.h"


#define ICON_FOLDER "gameicons"
#define NUMBER_OF_BUTTONS_ROWS 4
#define NUMBER_OF_BUTTONS_COLS 5

class MenuContext;

typedef std::map<std::string, cocos2d::Scene*> map_type;

class ScrollableGameMapScene : public cocos2d::Node {
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(ScrollableGameMapScene);
    
    void static nagivateToGame(std::string gameName);
    static std::vector<std::string> getTopBarGames();
    static void pushTopBarGame(std::string game);

CC_CONSTRUCTOR_ACCESS:
    virtual bool init();
    ScrollableGameMapScene();
    virtual ~ScrollableGameMapScene();

protected:
    cocos2d::Layer* _layer;
    cocos2d::ui::PageView* _pageView;
    MenuContext* menuContext;
    cocos2d::ParallaxNode *_parallax;
    map_type mymap;
    void gameSelected(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType eEventType);
    std::vector<std::string> split(std::string s, char delim);
    std::string static parseGameConfig(std::string gameConfig);
    std::map<std::string, std::string> static parseGameConfigToMap(std::string gameConfig);
    cocos2d::ui::Button* createButton(const rapidjson::Value& gameJson);
};

#endif /* ScrollableGameMapScene_hpp */
