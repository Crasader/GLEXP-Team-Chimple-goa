
#include "Circle.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "../lang/LangUtil.h"
#include "../lang/TextGenerator.h"
#include "../effects/FShake.h"
#include "../menu/MenuContext.h"

USING_NS_CC;

Circle::Circle()
{
	
}

Circle::~Circle()
{

}

Circle * Circle::create()
{
	Circle* CircleGame = new (std::nothrow) Circle();
	if (CircleGame && CircleGame->init()) {
		CircleGame->autorelease();
		return CircleGame;
	}
	CC_SAFE_DELETE(CircleGame);
	return nullptr;
}

cocos2d::Scene * Circle::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = Circle::create();
	scene->addChild(layer);

	layer->menu = MenuContext::create(layer,Circle::gameName());
	scene->addChild(layer->menu);
	return scene;
}

bool Circle::init()
{

	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float toplabelX = visibleSize.width / 2 - 30;
	std::map<std::string, std::map<std::string, std::string>> differntSceneMapping = {
		{
			{ "city",  //sonu designs
			{
				{ "plist", "dash/dash.plist" },
				{ "bg", "circlehero/circlehero.csb" },
				{ "friend", "circlehero/stoneman.csb" },
				{ "friend_dot", "stoneman" },
				{ "enemy", "circlehero/meteor.csb" },
				{ "enemy1", "meteor1" },
				{ "enemy2", "meteor2" },
				{ "enemy3", "meteor3" },
				{ "enemy4", "meteor4" },
				{ "enemy5", "meteor5" },
				{ "enemy6", "meteor6" },
				{ "animation_select", "one" },
				{"topLabelX",""},
				
			} },
			{ "iceLand",  //anu designs
			{
				{ "plist", "dashisland/dashisland.plist" },
				{ "bg", "circle/circle.csb" },
				{ "friend", "circle/octopus.csb" },
				{ "friend_dot", "dot_14" },
				{ "enemy", "circle/fish.csb" },
				{ "enemy1", "dot_2_2" },
				{ "enemy2", "dot_2_3" },
				{ "enemy3", "dot_2_4" },
				{ "enemy4", "dot_2_1" },
				{ "enemy5", "dot_2_0" },
				{ "enemy6", "dot_2" },
				{ "animation_select", "two" }
				
			} },
			{ "candy",  //teju design
			{
				{ "plist", "dashisland/dashisland.plist" },
				{ "bg", "circlecandy/circlecandy.csb" },
				{ "friend", "circlecandy/cake.csb" },
				{ "friend_dot", "dot_14" },
				{ "enemy", "circlecandy/ingredients.csb" },
				{ "enemy1", "board_2_0_0" },
				{ "enemy2", "board_2" },
				{ "enemy3", "board_2_0_0_0" },
				{ "enemy4", "board_2_0_0_0_0" },
				{ "enemy5", "board_2_0_0_0_0_0" },
				{ "enemy6", "board_2_0_0_0_0_0_0" },
				{ "animation_select", "three" }
			} },

		}
	};

	std::vector<std::string> theme = { "city","iceLand","candy"};
	_scenePath = differntSceneMapping.at(theme.at(cocos2d::RandomHelper::random_int(0, 2)));

	auto spritecache1 = SpriteFrameCache::getInstance();
	spritecache1->addSpriteFramesWithFile(_scenePath.at("plist"));

	background = CSLoader::createNode(_scenePath.at("bg"));//"circle/circle.csb"
	if(visibleSize.width > 2560) {
		extraX = (visibleSize.width - 2560) / 2;
		background->setPositionX((visibleSize.width - 2560) / 2);
	}
	this->addChild(background, 0);
	
	

	_enemyRef.push_back(background->getChildByName(_scenePath.at("enemy1")));
	_enemyRef.push_back(background->getChildByName(_scenePath.at("enemy2")));
	_enemyRef.push_back(background->getChildByName(_scenePath.at("enemy3")));
	_enemyRef.push_back(background->getChildByName(_scenePath.at("enemy4")));
	_enemyRef.push_back(background->getChildByName(_scenePath.at("enemy5")));
	_enemyRef.push_back(background->getChildByName(_scenePath.at("enemy6")));

	if (_scenePath.at("animation_select").compare("one") == 0)
	{
		CCLOG("one");
		auto dot = background->getChildByName(_scenePath.at("friend_dot"));
		_friend = CSLoader::createNode(_scenePath.at("friend"));//"circle/octopus.csb"
		_friend->setPositionX(dot->getPositionX() + extraX);
		_friend->setPositionY(dot->getPositionY());
		
		this->addChild(_friend);

		for (int i = 0; i < 6; i++)
		{
			auto enemyadding = CSLoader::createNode(_scenePath.at("enemy"));
			enemyadding->setPositionX(_enemyRef.at(i)->getPositionX() + extraX);
			enemyadding->setPositionY(_enemyRef.at(i)->getPositionY());
			_enemyRef1.push_back(enemyadding);
			this->addChild(enemyadding);
		}

	}
	

	_synonyms = TextGenerator::getInstance()->getSynonyms(10);
	for (auto it = _synonyms.begin(); it != _synonyms.end(); ++it) {
		_mapKey.push_back(it->first);
	}

	if (_scenePath.at("animation_select").compare("two") == 0)
	{
		CCLOG("two");
		auto dot = background->getChildByName(_scenePath.at("friend_dot"));
		_friend = CSLoader::createNode(_scenePath.at("friend"));//"circle/octopus.csb"
		_friend->setPositionX(dot->getPositionX() + extraX);
		_friend->setPositionY(dot->getPositionY());
		this->addChild(_friend);

		for (int i = 0; i < 6; i++)
		{
			auto enemyadding = CSLoader::createNode(_scenePath.at("enemy"));
			enemyadding->setPositionX(_enemyRef.at(i)->getPositionX() + extraX);
			enemyadding->setPositionY(_enemyRef.at(i)->getPositionY());
			if (i < 3) {
				enemyadding->setScaleX(-1*enemyadding->getScaleX());
			}
			_enemyRef1.push_back(enemyadding);
			this->addChild(enemyadding);
		}
		for (int i = 0; i < _enemyRef1.size(); i++)
		{
			auto timeline = CSLoader::createTimeline(("circle/fish.csb"));
			auto fish = _enemyRef1.at(i);
			fish->runAction(timeline);
			timeline->gotoFrameAndPlay(0, true);

		}
	
	}
	if (_scenePath.at("animation_select").compare("three") == 0)
	{
		CCLOG("three");
		_friend = background->getChildByName("cake");
		

	}
	wordGenerateWithOptions();
	return true;
}

void Circle::eat(char str)
{
	std::stringstream ss; 
	ss << str;
	ss >> _target;
	int num = atoi(_target.c_str());
	if (str < '4')
	{
		auto mouthTimeline = CSLoader::createTimeline(("circle/tail.csb"));
		_friend->getChildByName("tail_" + _target)->runAction(mouthTimeline);
		mouthTimeline->gotoFrameAndPlay(0, false);
	}
	else
	{
		auto mouthTimeline = CSLoader::createTimeline(("circle/tail1.csb"));
		_friend->getChildByName("tail_" + _target)->runAction(mouthTimeline);
		mouthTimeline->gotoFrameAndPlay(0, false);
	}
//	auto fishRemove = background->getChildByName("fish_" + _target);
	auto fishRemove = _enemyRef1.at(num - 1);
	FShake* shake = FShake::actionWithDuration(1.0f, 10.0f);
	//fishRemove->runAction(shake);
	fishRemove->runAction(Sequence::create(shake, CallFunc::create([=]() {
	//	wordGenerateWithOptions();
  }), NULL));
	if (_score == 5)
	{
	//	this->scheduleOnce(schedule_selector(Circle::bigpuff), 1.5f);
		auto correct = CSLoader::createNode("circle/correct.csb");
		correct->setPositionX(_friend->getPositionX());
		correct->setPositionY(_friend->getPositionY());
		this->addChild(correct);
		auto timeline = CSLoader::createTimeline("circle/correct.csb");
		correct->runAction(timeline);
		timeline->play("correct", true);
		_friend->setVisible(false);
		this->scheduleOnce(schedule_selector(Circle::scoreBoard), 3.0f);
	}
	else
	{
		wordGenerateWithOptions();
	}


}

void Circle::change(char  str)
{
	CCLOG("animation");
	std::stringstream ss;
	ss << str;
	ss >> _target;
	int num = atoi(_target.c_str());
	auto timeline = CSLoader::createTimeline(_scenePath.at("enemy"));
	auto blastref = _enemyRef1.at(num - 1);
	//blastref->runAction(timeline);
	std::vector<int> angleRef = { 70, 40, 10, -10, -45, -80 };
	_friend->setRotation(angleRef.at(num - 1));
	auto timeline1 = CSLoader::createTimeline("circlehero/punch.csb");
/*	this->runAction(Sequence::create(CallFunc::create([=]() {
		_friend->runAction(timeline1);
		timeline1->gotoFrameAndPlay(0,false);

	}), DelayTime::create(1.0f), CallFunc::create([=]() {
		_friend->setRotation(0.0f);
	//	addEnemy(num);
	}), NULL));*/

	this->runAction(Sequence::create(CallFunc::create([=]() {
		if (num < 4)
		{
			_friend->getChildByName("righthand")->runAction(timeline1);
			timeline1->play("punch", false);
		}
		else
		{
			_friend->getChildByName("lefthand")->runAction(timeline1);
			timeline1->play("punch", false);
		}

	}), CallFunc::create([=]() {
		blastref->runAction(timeline);
		timeline->play("blast", false);
		
	}), DelayTime::create(1.0f), CallFunc::create([=]() {
	//	_friend->setRotation(0.0f);
		addEnemy(num);
	}), NULL));
	
	
}

void Circle::addEnemy(int num)
{
	auto mouthTimeline = CSLoader::createTimeline(("circlehero/punch.csb"));
	_friend->runAction(mouthTimeline);
//	mouthTimeline->gotoFrameAndPlay(0, true);
	auto blastref = _enemyRef1.at(num - 1);
	this->removeChild(blastref);
	auto enemyadding = CSLoader::createNode(_scenePath.at("enemy"));
	
	this->addChild(enemyadding);
	if (num < 4)
	{
		enemyadding->setPositionX(_enemyRef.at(num - 1)->getPositionX() - 1000);
		enemyadding->setPositionY(_enemyRef.at(num - 1)->getPositionY() - 300);
	}
	else
	{
		enemyadding->setPositionX(_enemyRef.at(num - 1)->getPositionX() + 1000 );
		enemyadding->setPositionY(_enemyRef.at(num - 1)->getPositionY() + 100);
	}
	auto action = MoveTo::create(1.0, Vec2(_enemyRef.at(num - 1)->getPositionX() + extraX, _enemyRef.at(num - 1)->getPositionY()));
	enemyadding->runAction(Sequence::create(action,CallFunc::create([=]() {
		wordGenerateWithOptions();
	}), NULL));
	auto timeline = CSLoader::createTimeline(_scenePath.at("enemy"));
	//auto blastref = _enemyRef1.at(num - 1);

	enemyadding->runAction(timeline);
	timeline->play("meteorfloat", false);

	if (_score == 5)
	{
		this->scheduleOnce(schedule_selector(Circle::scoreBoard), 2.0f);
	}

}

void Circle::topping(char  str)
{
	std::stringstream ss;
	ss << str;
	ss >> _target;
	int num = atoi(_target.c_str());
	_candyRef = { "lollipop" ,"cherry", "candy", "strawberry", "chocolate" , "cookie" };
	auto path = "circlecandy/"+ _candyRef.at(num - 1) + ".csb";
	cocos2d::Node * candyMove = CSLoader::createNode(path);
	candyMove->setPositionX(background->getChildByName(_candyRef.at(num - 1))->getPositionX());
	candyMove->setPositionY(background->getChildByName(_candyRef.at(num - 1))->getPositionY());
	this->addChild(candyMove);
	candyMove->setScale(0.3);
	std::vector<std::string> dotRef = {"dot_43_1","dot_43_1_0","dot_43_1_0_0","dot_43_1_0_0_0","dot_43_1_0_0_0_0","dot_43_1_0_0_0_0_0"};
	auto action = JumpTo::create(1.0, Vec2(background->getChildByName(dotRef.at(_score - 1))->getPositionX()+extraX, background->getChildByName(dotRef.at(_score - 1))->getPositionY()),500,1);
	//candyMove->runAction(action);
	auto callbackStart = CallFunc::create(CC_CALLBACK_0(Circle::puff, this));
	auto seq = Sequence::create(action,callbackStart, NULL);
	candyMove->runAction(seq);
	
	
}
void Circle::puff()
{
	auto puff = CSLoader::createNode("circlecandy/puff.csb");
	puff->setPosition(background->getChildByName("cake")->getPositionX(), background->getChildByName("cake")->getPositionY());
	this->addChild(puff);
	auto timeline = CSLoader::createTimeline("circlecandy/puff.csb");
	puff->runAction(timeline);
	timeline->play("puff", false);
	if (_score == 6)
	{
		this->scheduleOnce(schedule_selector(Circle::bigpuff), 1.5f);
	}
	else
	{
		wordGenerateWithOptions();
	}
	

}
void Circle::scoreBoard(float dt)
{
	menu->showScore();
}
void Circle::bigpuff(float dt)
{
	if (_scenePath.at("animation_select").compare("three") == 0)
	{
		CCLOG("bigpuff");
		auto bigpuff = CSLoader::createNode("circlecandy/bigpuff.csb");
		bigpuff->setPosition(background->getChildByName("cake")->getPositionX(), background->getChildByName("cake")->getPositionY());
		this->addChild(bigpuff, 1);
		auto timeline = CSLoader::createTimeline("circlecandy/bigpuff.csb");
		bigpuff->runAction(timeline);
		timeline->play("bigpuff", false);

		auto cakeRef = CSLoader::createNode("circlecandy/cake.csb");
		cakeRef->setPosition(background->getChildByName("cake")->getPositionX() + extraX, background->getChildByName("cake")->getPositionY() + 80);
		this->addChild(cakeRef);
		//cakeRef->setAnchorPoint(Vec2(1, 1));
		auto cake = CSLoader::createTimeline("circlecandy/cake.csb");
		cakeRef->runAction(cake);
		timeline->play("cake2", false);
		this->scheduleOnce(schedule_selector(Circle::scoreBoard), 2.0f);
	}
	if (_scenePath.at("animation_select").compare("two") == 0)
	{
		auto timeline = CSLoader::createTimeline("circle/correct.csb");
		_friend->runAction(timeline);
		timeline->gotoFrameAndPlay(0, false);
		this->scheduleOnce(schedule_selector(Circle::scoreBoard), 2.0f);
	}
}
void Circle::wordGenerateWithOptions()
{
	std::vector<std::string> answer;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int size = _mapKey.size();
	_gameWord = _mapKey.at(cocos2d::RandomHelper::random_int(0, size - 1));
	answer.push_back(_synonyms.at(_gameWord));
	_topLabel = Label::createWithSystemFont(_gameWord.c_str(), "Arial", 100);
	_topLabel->setColor(Color3B(0, 0, 0));
	if (_scenePath.at("animation_select").compare("one") == 0)
	{
        _topLabel->setPositionX(visibleSize.width / 2 );
		_topLabel->setPositionY(visibleSize.height - _topLabel->getContentSize().height );
	}
	else
	{
		_topLabel->setPositionX(visibleSize.width / 2 -20 );
		_topLabel->setPositionY(visibleSize.height - _topLabel->getContentSize().height - 600);
    }
	this->addChild(_topLabel,2);

	int randomInt1 = cocos2d::RandomHelper::random_int(0, size - 1);
	for (int j = 0; j < 5; j++) {
		answer.push_back(_synonyms.at(_mapKey.at(randomInt1 % size)));
		randomInt1++;
	}
	int answerSize = answer.size() - 1;
	//CCLOG(answer);
	int randomInt = cocos2d::RandomHelper::random_int(0, answerSize);
	for (int i = 0; i < _enemyRef.size(); i++) {

		auto str = answer.at(randomInt % (answerSize + 1));
		auto myLabel = Label::createWithSystemFont(str, "Arial", 100);
		std::stringstream ss;
		ss << (i+1);
		std::string str1 = ss.str();
	//	myLabel->setPositionX(_enemyRef1.at(i)->getContentSize().width/2);
	//	myLabel->setPositionY(_enemyRef1.at(i)->getContentSize().height/ 2);

		myLabel->setPositionX(_enemyRef.at(i)->getPositionX() + extraX);
		myLabel->setPositionY(_enemyRef.at(i)->getPositionY());
		
		//myLabel->setColor(Color3B(0, 0, 0));
		myLabel->setName(str+str1);
		this->addChild(myLabel,1);
		_choiceLabel.pushBack(myLabel);
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = CC_CALLBACK_2(Circle::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, myLabel);
		randomInt++;
	}

}

bool Circle::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto target = event->getCurrentTarget();
	auto  location = target->convertToNodeSpace(touch->getLocation());
	//auto  location = target->convertToNodeSpace(touch->getLocation() - ;
	if (target->getBoundingBox().containsPoint(Vec2(touch->getLocation().x , touch->getLocation().y)))
	{
		std::string wordStr = target->getName();
		char sss[100];
		strcpy(sss, wordStr.c_str());
		//auto strArray = (char[]) wordStr;
		//auto test = strtok(sss, " _");
		//std::string number;
		/*while (test != NULL)
		{
			number = strtok(NULL, "_");
		}*/
		 char ssss = wordStr.at(wordStr.length()-1);
		 wordStr.at(wordStr.length() - 1) = ' ';
		CCLOG("");
		if (wordStr.compare(_synonyms.at(_gameWord)+" ") == 0) {
			//    CCLOG("11111111111111111");
			this->removeChild(_topLabel);
			for (int i = 0; i < _choiceLabel.size(); i++) {
				this->removeChild(_choiceLabel.at(i));
				}
		//	_eventDispatcher->removeEventListenersForTarget(target);
			_choiceLabel.clear();
			if (_scenePath.at("animation_select").compare("one") == 0)
			{
				_score++;
				change(ssss);
			}
			else if (_scenePath.at("animation_select").compare("two") == 0)
			{
				_score++;
				eat(ssss);
			}
			else
			{ 
				_score++;
				topping(ssss);
				
			}
			
			
		}
		else
		{
			FShake* shake = FShake::actionWithDuration(1.0f, 10.0f);
			_friend->runAction(shake);
		}
		return true;
	}
	return false;
}
