#ifndef __BASIC_MULTIPLICATION_SCENE_H__
#define __BASIC_MULTIPLICATION_SCENE_H__

#include "cocos2d.h"
#include "../menu/MenuContext.h"
#include "../menu/StartMenuScene.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "../lang/LangUtil.h"
#include "../lang/TextGenerator.h"
#include "../effects/FShake.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace std;

class BasicMultiplication : public cocos2d::Layer
{

protected:
	MenuContext *_menuContext;
	int _answer = 0, _counter = 0 , _row = 0 , _column = 0;
	string _topBoardEquation = "", _animationName = "";
	
	
public:
	~BasicMultiplication();
	static cocos2d::Scene* createScene();
	virtual bool init();
	static BasicMultiplication* create();
	void onEnterTransitionDidFinish();
	void update(float) override;

	void LearningPlay();

	void topBoardSetting();

	void gridGrayAndListnerController(int row, int column);

	void addEventsOnGrid(cocos2d::Sprite * object);

	void topBoardEquationController(Sprite* target);

	void playAnimationAnimal();

	void IndexValuePopup(Sprite * target);

	string getGridNameInString(int row, int column);

	Sprite * getGridWithIndex(int row, int column);

	void QuizPlay();

	void TextOnBox(Sprite * sprite, string text);

	void optionCreate();

	void popUp(Sprite * target);

	Sprite * createSprite(string name, int width, int height, int posiX, int posiY, int scaleXY);

	static const char* gameName() { return BASICMULTIPLICATION.c_str(); }
};

#endif // __BASIC_MULTIPLICATION_SCENE_H__
