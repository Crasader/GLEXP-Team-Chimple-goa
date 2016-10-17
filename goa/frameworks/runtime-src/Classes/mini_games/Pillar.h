#ifndef __PILLAR_SCENE_H__
#define __PILLAR_SCENE_H__

#include "cocos2d.h"
#include "../menu/MenuContext.h"


class Pillar : public cocos2d::Layer
{
public:
	Pillar();
	~Pillar();
	static Pillar* create();
	virtual bool init();
	void update(float dt);
	static cocos2d::Scene* createScene();
	std::map<std::string, std::string> _scenePath;
	float extraX;
	int _num = 0;
	int _score = 0;
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
    cocos2d::Node* background;
	cocos2d::Sprite* _cake;
	cocos2d::Sprite* _cakeMove;
	cocos2d::Node* _ladder;
	cocos2d::Node* _character;
	cocos2d::Label* _topLabel;
	cocos2d::Sprite* _pointRef;
	std::vector<cocos2d::Node *>  _Ref;
	std::vector<std::string> _wordCorrect;
	std::vector<std::string> _wordList;
	void ladderMove();
	void newCake();
	void blink(std::string animationName, bool loop);
	static const char* gameName() { return PILLAR.c_str(); }
protected:
	bool _rotateFlag = true;
	MenuContext * menu;
};

#endif