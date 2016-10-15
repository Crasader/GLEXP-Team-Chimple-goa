#ifndef __TALK_SCENE_H__
#define __TALK_SCENE_H__

#include "cocos2d.h"
#include <vector>
#include "editor-support/cocostudio/CocoStudio.h"
#include "../menu/MenuContext.h"
#include "../puzzle/Alphabet.h"
#include "../puzzle/CharGenerator.h"
#include "SimpleAudioEngine.h"
#include "../lang/SafariAnalyticsManager.h"
#include "../StartMenuScene.h"
#include "../lang/TextGenerator.h"
#include "ui/CocosGUI.h"
#include <string>
#include <sstream>


class Talk : public cocos2d::Layer
{
	
public:
	static cocos2d::Scene* createScene();
	Talk();
	~Talk();
	virtual bool init();
	
	std::vector<std::pair<std::string, TextGenerator::POS>> _textToShow;

	std::map<std::string, std::map<std::string, int>> differntSceneMapping;
	std::vector<std::string> _scene;
	Node *_talkBg;

	cocostudio::timeline::ActionTimeline *_heroChar, *_enemyChar;

	cocos2d::Sprite *_hhand, *_hero, *_ehand, *_enemy, *_fish, *_hbasket, *_ebasket;
	cocos2d::Action *_action;
	int _handFlag;
	std::vector<cocos2d::Sprite*> _enemyFish, _heroFish;
	int _totalCount, _totalAnswer, _correctAnswer;

//	std::vector<std::string> _allSentense;

	std::vector<std::vector<std::pair<std::string, TextGenerator::POS>>> _allSentense;

	CREATE_FUNC(Talk);
    
	std::string sceneName, _questionType;
	cocos2d::Size visibleSize;


    static const char* gameName() { return TALK.c_str(); };
	void update(float);
	void gameEnd();
	void displayWord();

	struct LabelDetails
	{
		cocos2d::LabelTTF *label;
		std::string id;
		int sequence, flag;
		char answer;
	}LabelDetails;

	std::vector<struct LabelDetails> _labelDetails;

	void addEvents(struct LabelDetails);
	std::vector<std::string> split(std::string, char);
protected:
	MenuContext* _menuContext;
};
#endif // __Talk_SCENE_H__
