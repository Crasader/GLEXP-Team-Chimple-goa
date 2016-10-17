#include "Owl.h"

USING_NS_CC;

Scene* Owl::createScene()
{
	auto scene = Scene::create();
	auto layer = Owl::create();
	scene->addChild(layer);
	layer->_menuContext = MenuContext::create(layer, "owl");
	scene->addChild(layer->_menuContext);
	return scene;
}

bool Owl::init()
{
	if (!Layer::init()) { return false; }

	    _sceneMap = {
		{
			{ "owlCity",
				{
					{ "bg", "owlcity/owlcity.csb"},
					{ "character1", "owlcity/character.csb"},
					{ "character2", "owlcity/character_enemy.csb"},
					{ "plist", "owlcity/owlcity.plist"},
					{"smallbar","owlcity/smallbar_orange.png"},
					{"orangebase","owlcity/orangebase.png"},
					{"greenbase","owlcity/greenbase.png"},
					{"gridOrange","owlcity/smallbar_orange.png"},
					{"gridGreen","owlcity/smallbar_green.png" },
					{"gridWhite","owlcity/smallbar_white.png"},
					{"topBoard","orangebar"},
					{"whiteBoard","smallbar_white"},
					{ "whiteBoard2","smallbar_white" },
					{"bodyCharacter","body"},
					{"hideBlack","owlcity/dash_black.png"},
					{ "hideGreen","owlcity/dash_green.png" },
					{ "hideOrange","owlcity/dash_orange.png" }
				} 
			},
			{ "owlisland",
				{
					{ "bg", "owlisland/owlisland.csb" },
					{ "character1", "owlisland/character.csb" },
					{ "character2", "owlisland/character_enemy.csb" },
					{ "plist", "owlisland/owlisland.plist"},
					{ "smallbar","owlisland/smallbar.png"},
					{ "orangebase","owlisland/orangebase.png"},
					{ "greenbase","owlisland/greenbase.png" },
					{ "gridOrange","owlisland/smallbar.png" },
					{ "gridGreen","owlisland/smallbar_green.png" },
					{ "gridWhite","owlisland/white.png" },
					{ "topBoard","orangebar" },
					{ "whiteBoard","white_2" },
					{"whiteBoard2","white_5"},
					{ "bodyCharacter","Sprite_6" },
					{ "hideGreen","owlisland/dash_green.png" },
					{ "hideOrange","owlisland/dash_orange.png" },
					{ "bubble","owlisland/bubble.csb" }
				}
			},
			{ "owlForest",
				{
					{ "bg", "owlcity/owlcity.csb" },
					{ "character1", "owlcity/character.csb" },
					{ "character2", "owlcity/character_enemy.csb" },
					{ "plist", "owlcity/owlcity.plist" }				
				}
			}
		}
	};

	_owlPropertyMap = {
		{
			{"owlCity",
				{
					{"rowFirst",0.19f},
					{"blockX1",0.08f},
					{"blockY1",0.34f},
					{ "blockX2",0.6f },
					{ "blockY2",0.37f },
					{"owlheightToAlpha",1.5f},
					{"scaleSecond",0.65f}
				}
			},
			{ "owlisland",
				{
					{ "rowFirst",0.19f },
					{ "blockX1",0.08f },
					{ "blockY1",0.34f },
					{ "blockX2",0.6f },
					{ "blockY2",0.37f },
					{ "owlheightToAlpha",1.5f },
					{ "scaleSecond",0.65f }
				}
			}
		}
	};

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	string test[2] = {"owlisland","owlCity"};
	_owlCurrentTheme = test[RandomHelper::random_int(0, 1)];
	auto themeResourcePath = _sceneMap.at(_owlCurrentTheme);
	Node* bg = CSLoader::createNode(themeResourcePath.at("bg"));
	addChild(bg);
	
	if (visibleSize.width > 2560) {
		auto myGameWidth = (visibleSize.width - 2560) / 2;
		bg->setPositionX(myGameWidth);
	}

	auto timelinecharacter1 = CSLoader::createTimeline(themeResourcePath.at("character1"));
	_sprite = CSLoader::createNode(themeResourcePath.at("character1"));
	_sprite-> runAction(timelinecharacter1);
	addChild(_sprite,2);
	timelinecharacter1->play("fly",true);

	auto timelinecharacter2 = CSLoader::createTimeline(themeResourcePath.at("character2"));
	_opponent = CSLoader::createNode(themeResourcePath.at("character2"));
	_opponent->runAction(timelinecharacter2);
	_opponent->setScale(_owlPropertyMap.at(_owlCurrentTheme).at("scaleSecond"));
	addChild(_opponent, 2);
	timelinecharacter2->play("fly", true);

	if (_owlCurrentTheme == "owlisland") {

		auto timelinecharacter3 = CSLoader::createTimeline(themeResourcePath.at("bubble"));
		auto bubbles = CSLoader::createNode(themeResourcePath.at("bubble"));
		bubbles->runAction(timelinecharacter3);
		bubbles->setPosition(Vec2(visibleSize.width * 0.04 , visibleSize.height * 0.4));
		addChild(bubbles,1);
		timelinecharacter3->gotoFrameAndPlay(0, true);

		auto timelinecharacter4 = CSLoader::createTimeline(themeResourcePath.at("bubble"));
		auto bubble = CSLoader::createNode(themeResourcePath.at("bubble"));
		bubble->runAction(timelinecharacter4);
		bubble->setPosition(Vec2(visibleSize.width - visibleSize.width * 0.08, visibleSize.height * 0.4));
		addChild(bubble,1);
		timelinecharacter4->gotoFrameAndPlay(0, true);

		_opponent->getChildByName(_sceneMap.at(_owlCurrentTheme).at("whiteBoard2"))->setVisible(false);

	}

	auto board = bg->getChildByName(themeResourcePath.at("topBoard"));
	board->setName("topBoard");
	_textLabel = LabelTTF::create(_displayWord[_textBoard], "Helvetica", board->getContentSize().height *0.8);
	_textLabel->setPosition(board->getContentSize().width/2,board->getContentSize().height/2);
	_textLabel->setAnchorPoint(Vec2(0.5, 0.5));
	_textLabel->setName("text");
	board->addChild(_textLabel);

	_textOwlBoard = LabelTTF::create("", "Helvetica", _sprite->getChildByName(themeResourcePath.at("whiteBoard"))->getContentSize().height *0.8);
	_textOwlBoard->setPosition(Vec2(_sprite->getChildByName(themeResourcePath.at("whiteBoard"))->getContentSize().width/2, _sprite->getChildByName(themeResourcePath.at("whiteBoard"))->getContentSize().height / 2));
	_textOwlBoard->setName("owlBoard");
	_textOwlBoard->setColor(Color3B::BLACK);
	_sprite->getChildByName(themeResourcePath.at("whiteBoard"))->addChild(_textOwlBoard);
	_sprite->getChildByName(themeResourcePath.at("whiteBoard"))->setVisible(false);

	createGrid();

	setBuildingBlock(++_blockLevel1);
	crateLetterGridOnBuilding(_blockLevel1, _displayWord[_textBoard]);
	
	setBuildingBlockSecond(++_blockLevel2);
	crateLetterGridOnBuildingSecond(_blockLevel2, _displayWord[_textBoard2]);

	InitAnimation();
	this->schedule(schedule_selector(Owl::autoPlayerController), RandomHelper::random_int(4,8));
	scheduleUpdate();
	return true;
}

void Owl::autoPlayerController(float data) {

	std::ostringstream blockName;	blockName << "blockLevel2" << _blockLevel2; std::string blockNameInString = blockName.str();
	auto blockBox = this->getChildByName(blockNameInString);
	auto blockChild = blockBox->getChildren();
	blockChild.at(_textCounter2)->getChildByName("hideBoard")->setVisible(false);
	_textCounter2++;

	if (_textCounter2 == blockChild.size()) {
		if ((_blockLevel2 >= (sizeof(_displayWord) / sizeof(_displayWord[0])))) {
			CCLOG("< ------ DONE COMPLETE -----  >     I AM IN AUTOPLAYERCONTROLLER METHOD");
			this->runAction(Sequence::create(DelayTime::create(3), CallFunc::create([=]() { _menuContext->showScore(); }), NULL));
		}
		else {
			setBuildingBlockSecond(++_blockLevel2);
			crateLetterGridOnBuildingSecond(_blockLevel2, _displayWord[++_textBoard2]);
		}
		_textCounter2 = 0;
	}
}

void Owl::update(float delta) {
	if(_flagDemo)
	UpdateAnimation(delta);
	UpdateAnimationSecond(delta);
}

void Owl::setSpriteProperties(Sprite* ImageObject, float positionX, float positionY, float scaleX, float scaleY, float anchorX, float anchorY, float rotation, int zorder) {
	ImageObject->setPosition(Vec2(positionX, positionY));
	ImageObject->setScaleX(scaleX);
	ImageObject->setScaleY(scaleY);
	ImageObject->setAnchorPoint(Vec2(anchorX, anchorY));
	ImageObject->setRotation(rotation);
	addChild(ImageObject, zorder);
}

void Owl::crateLetterGridOnBuilding(int blockLevel, string displayWord) {

	auto themeResourcePath = _sceneMap.at(_owlCurrentTheme);
	auto blockObject = Sprite::createWithSpriteFrameName(themeResourcePath.at("orangebase"));
	auto letterbox = Sprite::createWithSpriteFrameName(themeResourcePath.at("gridOrange"));
	int boxSize = blockObject->getContentSize().width;
	int space = blockObject->getContentSize().width - (letterbox->getContentSize().width * 6);
	int indiSpace = space / (6+1);
	int initSpace = blockObject->getContentSize().width - letterbox->getContentSize().width * displayWord.length() - ( indiSpace * (displayWord.length()-1));
	initSpace = initSpace / 2;

	float xPosi = initSpace + letterbox->getContentSize().width/2;

	for (int i = 0; i <= (displayWord.length() - 1); i++) {
		auto letterGrid = Sprite::createWithSpriteFrameName(themeResourcePath.at("gridOrange"));
		auto hideGrid = Sprite::createWithSpriteFrameName(themeResourcePath.at("hideOrange"));

		auto label = LabelTTF::create(LangUtil::convertUTF16CharToString(displayWord.at(i)), "Helvetica", letterGrid->getContentSize().height*0.8);
		letterGrid -> setPosition(Vec2(xPosi, blockObject->getContentSize().height *0.45));
		label->setPosition(Vec2(letterGrid->getContentSize().width/2, letterGrid->getContentSize().height /2));
		xPosi = xPosi + indiSpace + letterGrid->getContentSize().width;
		std::ostringstream blockName;	blockName << "blockLevel1" << blockLevel; std::string blockNameInString = blockName.str();
		this->getChildByName(blockNameInString)->addChild(letterGrid);
		letterGrid->addChild(label);
		
		hideGrid->setPosition(Vec2(letterGrid->getContentSize().width / 2, letterGrid->getContentSize().height / 2));
		letterGrid->addChild(hideGrid);
		hideGrid->setName("hideBoard");
		letterGrid->setName(LangUtil::convertUTF16CharToString(displayWord.at(i)));
		letterGrid->setTag(i);
	}
}

void Owl::crateLetterGridOnBuildingSecond(int blockLevel, string displayWord) {

	auto themeResourcePath = _sceneMap.at(_owlCurrentTheme);
	auto blockObject = Sprite::createWithSpriteFrameName(themeResourcePath.at("greenbase"));
	auto letterbox = Sprite::createWithSpriteFrameName(themeResourcePath.at("gridGreen"));
	int space = blockObject->getContentSize().width - (letterbox->getContentSize().width * 6);
	int indiSpace = space / (6 + 1);
	int initSpace = blockObject->getContentSize().width - letterbox->getContentSize().width * displayWord.length() - (indiSpace * (displayWord.length() - 1));
	initSpace = initSpace / 2 ;

	float xPosi = initSpace + letterbox->getContentSize().width / 2;

	for (int i = 0; i <= (displayWord.length() - 1); i++) {
		auto letterGrid = Sprite::createWithSpriteFrameName(themeResourcePath.at("gridGreen"));
		auto hideGrid = Sprite::createWithSpriteFrameName(themeResourcePath.at("hideGreen"));

		letterGrid->setPosition(Vec2(xPosi, blockObject->getContentSize().height *0.45));
		xPosi = xPosi + indiSpace+ letterGrid->getContentSize().width;
		std::ostringstream blockName;	blockName << "blockLevel2" << blockLevel; std::string blockNameInString = blockName.str();
		this->getChildByName(blockNameInString)->addChild(letterGrid);

		hideGrid->setPosition(Vec2(letterGrid->getContentSize().width / 2, letterGrid->getContentSize().height / 2));
		letterGrid->addChild(hideGrid);
		hideGrid->setName("hideBoard");
		letterGrid->setName(LangUtil::convertUTF16CharToString(displayWord.at(i)));
		letterGrid->setTag(i);
	}
}

void Owl::createGrid() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto themeResourcePath = _sceneMap.at(_owlCurrentTheme);
	auto alpha = LangUtil::getInstance()->getAllCharacters();
	
	auto gridObject = Sprite::createWithSpriteFrameName(themeResourcePath.at("smallbar"));
	float space = visibleSize.width - (gridObject->getContentSize().width * 13);
	float IndiSpace = space / (13 + 1);
	float xPosi = IndiSpace + gridObject->getContentSize().width / 2;
	auto getSize = gridObject->getContentSize().width;
	int counter = 0;
	for (int row = 1; row <= 2; row++) {

		int height = visibleSize.height * _owlPropertyMap.at(_owlCurrentTheme).at("rowFirst");
		if (row == 2) {
			height = height - gridObject->getContentSize().height - IndiSpace;
			xPosi = IndiSpace + gridObject->getContentSize().width / 2;
		}

		for (int column = 1; column <= 13; column++) {
			auto gridObject = Sprite::createWithSpriteFrameName(themeResourcePath.at("smallbar"));
			setSpriteProperties(gridObject, xPosi, height, 1, 1, 0.5, 0.5, 0, 1);
			xPosi = xPosi + IndiSpace + gridObject->getContentSize().width;
			addEventsOnGrid(gridObject);
			
			auto label = LabelTTF::create(LangUtil::convertUTF16CharToString(alpha[counter]), "Helvetica", gridObject->getContentSize().width * 0.8);
			label->setPosition(Vec2(gridObject->getContentSize().width / 2, gridObject->getContentSize().height / 2));
			label->setColor(Color3B::WHITE);
			label->setName(LangUtil::convertUTF16CharToString(alpha[counter]));
			
			gridObject->setName(LangUtil::convertUTF16CharToString(alpha[counter]));
			gridObject->addChild(label);
			counter++;
		}
	}
}

void Owl::setBuildingBlock(int blockLevel) {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto themeResourcePath = _sceneMap.at(_owlCurrentTheme);
	auto blockObject = Sprite::createWithSpriteFrameName(themeResourcePath.at("orangebase"));
	int height = 0;

	if (blockLevel == 1)
	{ 
		_heightBlock1 = visibleSize.height * _owlPropertyMap.at(_owlCurrentTheme).at("blockY1"); 
	}
	else {
		_heightBlock1 = _heightBlock1 + blockObject->getContentSize().height - (blockObject->getContentSize().height *0.05);
	}
	height = _heightBlock1;

	setSpriteProperties(blockObject, (visibleSize.width * _owlPropertyMap.at(_owlCurrentTheme).at("blockX1")) + (blockObject->getContentSize().width/2), _heightBlock1, 1, 1, 0.5, 0.5, 0, 1);
	
	std::ostringstream blockName;	blockName << "blockLevel1"<<blockLevel; std::string blockNameInString = blockName.str();
	blockObject->setName(blockNameInString);

}

void Owl::setBuildingBlockSecond(int blockLevel) {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto themeResourcePath = _sceneMap.at(_owlCurrentTheme);
	auto blockObject = Sprite::createWithSpriteFrameName(themeResourcePath.at("greenbase"));
	
	if (blockLevel == 1)
	{
		_heightBlock2 = visibleSize.height * _owlPropertyMap.at(_owlCurrentTheme).at("blockY2");
	}
	else {
		_heightBlock2 = _heightBlock2 + (blockObject->getContentSize().height - (blockObject->getContentSize().height *0.05))*_owlPropertyMap.at(_owlCurrentTheme).at("scaleSecond");
	}
	setSpriteProperties(blockObject, (visibleSize.width * _owlPropertyMap.at(_owlCurrentTheme).at("blockX2")) + (blockObject->getContentSize().width / 2 * _owlPropertyMap.at(_owlCurrentTheme).at("scaleSecond")), _heightBlock2, _owlPropertyMap.at(_owlCurrentTheme).at("scaleSecond"), _owlPropertyMap.at(_owlCurrentTheme).at("scaleSecond"), 0.5, 0.5, 0, 1);

	std::ostringstream blockName;	blockName << "blockLevel2" << blockLevel; std::string blockNameInString = blockName.str();
	blockObject->setName(blockNameInString);

}

void Owl::addEventsOnGrid(cocos2d::Sprite* callerObject)
{
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);

	listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		auto target = event->getCurrentTarget();
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		if (target->getBoundingBox().containsPoint(touch->getLocation())) {
			
			auto childText =  target->getChildByName(target->getName());
			target->setColor(Color3B::GRAY);
			auto x = childText->getName();
			CCLOG("Touched : %c", x.at(0));
			return true;
		}
		return false;
	};

	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		auto target = event->getCurrentTarget();
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
			auto x = target->getName();
			target->setColor(Color3B(255,255,255));
			CCLOG("Touched : %c",x.at(0));

			if (target->getBoundingBox().containsPoint(touch->getLocation())) {

				std::ostringstream blockName;	blockName << "blockLevel1" << _blockLevel1; std::string blockNameInString = blockName.str();
				
				if (_blockLevel1 <= (sizeof(_displayWord) / sizeof(_displayWord[0]))) {
					auto blockChild = target->getParent()->getChildByName(blockNameInString)->getChildren();

					if (blockChild.at(_textCounter)->getName() == target->getName() && _flagToControlMuiltipleTouch) {
						_flagToControlMuiltipleTouch = false;
						auto y = _sprite->getPositionY() - target->getPositionY();
						auto x = -_sprite->getPositionX() + target->getPositionX();
						float dist = sqrt((y*y) + (x*x));
						auto blockBox = target->getParent()->getChildByName(blockNameInString);

						auto moveToAlphaGridAction = MoveTo::create(dist/800,Vec2(target->getPositionX(),target->getPositionY()+_sprite->getChildByName(_sceneMap.at(_owlCurrentTheme).at("bodyCharacter"))->getContentSize().height/ _owlPropertyMap.at(_owlCurrentTheme).at("owlheightToAlpha")));
						auto moveToAnswerGridAction = MoveTo::create(dist / 1000, Vec2((blockBox->getPositionX() - blockBox->getContentSize().width/2)+blockChild.at(_textCounter)->getPositionX(), blockBox->getPositionY()+_sprite->getChildByName(_sceneMap.at(_owlCurrentTheme).at("bodyCharacter"))->getContentSize().height/ _owlPropertyMap.at(_owlCurrentTheme).at("owlheightToAlpha")));
						auto callFunct = CallFunc::create([=]() {
							_flagDemo = true;
							_flagToControlMuiltipleTouch = true;
							_sprite->getChildByName(_sceneMap.at(_owlCurrentTheme).at("whiteBoard"))->setVisible(false);
							blockChild.at(_textCounter)->getChildByName("hideBoard")->setVisible(false);
							_textCounter++;
							_xStart = _sprite->getPositionX();      // Pixels
							_yStart = blockBox->getPositionY() + blockBox->getContentSize().height;
							if (counter % 2 != 0) {
								_xStop = blockBox->getPositionX() - blockBox->getContentSize().width/2;
								_ticks = 0;
								_ticksTotal = 3 / (1.0/60.0);// Pixels
							}else {
								_xStop = blockBox->getPositionX() + blockBox->getContentSize().width / 2;
								_ticks = 0;
								_ticksTotal = 3 / (1.0/60.0);// Pixels
							}

							if (_textCounter == blockChild.size() && _blockLevel1 < (sizeof(_displayWord) / sizeof(_displayWord[0]))) {
								_textLabel->setString(_displayWord[++_textBoard]);
								setBuildingBlock(++_blockLevel1);
								crateLetterGridOnBuilding(_blockLevel1, _displayWord[_textBoard]);
								_textCounter = 0;
							}
							else if (_textCounter == blockChild.size() && _blockLevel1 == (sizeof(_displayWord) / sizeof(_displayWord[0]))) {
								_textCounter = 0;
								_blockLevel1++;
								this->runAction(Sequence::create(DelayTime::create(3), CallFunc::create([=]() { _menuContext->showScore(); }),NULL));
							}
						});
						auto pickBoard = CallFunc::create([=]() { 
							_sprite->getChildByName(_sceneMap.at(_owlCurrentTheme).at("whiteBoard"))->setVisible(true);
							_textOwlBoard->setString(LangUtil::convertUTF16CharToString(target->getName().at(0)));
						});
						_sprite->runAction(Sequence::create(CallFunc::create([=]() { _flagDemo = false; }), moveToAlphaGridAction, pickBoard, moveToAnswerGridAction, callFunct, NULL));
					}
				}
			}
		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, callerObject);
}

Owl::~Owl(void)
{
	this->removeAllChildrenWithCleanup(true);
}

void Owl::InitAnimation()
{
	double DURATION = 3; // Seconds for total animation.
	double SECONDS_PER_TICK = 1.0 / 60;
	std::ostringstream blockName;	blockName << "blockLevel1" << _blockLevel1; std::string blockNameInString = blockName.str();
	auto block = this->getChildByName(blockNameInString);
	_xStart = block->getPositionX() - block->getContentSize().width / 2;      // Pixels
	_yStart = block->getPositionY() + block->getContentSize().height;      // Pixels
	_xStop = block->getPositionX() + block->getContentSize().width / 2;    // Pixels

	std::ostringstream blockNames;	blockNames << "blockLevel2" << _blockLevel2; std::string blockNameInStrings = blockNames.str();
	auto blocks = this->getChildByName(blockNameInStrings);
	_xStartSecond = blocks->getPositionX() - (blocks->getContentSize().width / 2 * _owlPropertyMap.at(_owlCurrentTheme).at("scaleSecond"));      // Pixels
	_yStartSecond = blocks->getPositionY() + (blocks->getContentSize().height*_owlPropertyMap.at(_owlCurrentTheme).at("scaleSecond"));      // Pixels
	_xStopSecond = blocks->getPositionX() + (blocks->getContentSize().width / 2* _owlPropertyMap.at(_owlCurrentTheme).at("scaleSecond"));    // Pixels
	_ticks = 0;
	_ticks2 = 0;
	_ticksTotal = DURATION / SECONDS_PER_TICK;
	DURATION = 5;
	_ticksTotal2 = DURATION / SECONDS_PER_TICK;
}

void Owl::UpdateAnimation(float dt)
{
	double DURATION = 3; // Seconds for total animation.
	double SECONDS_PER_TICK = 1.0 / 60;
	double _xSpeed = (_xStop - _xStart) / DURATION;

	if (_ticks <= _ticksTotal)
	{
		double Y_HEIGHT = 80;
		double _xSpeed = (_xStop - _xStart) / DURATION;
		double seconds = _ticks*SECONDS_PER_TICK;
		
		double xPos = _xStart + seconds*_xSpeed;
		double yPos = _yStart + Y_HEIGHT*sin(seconds * 2 * M_PI / 1.5); // (/1) Seconds for y cycle.
		_sprite->setPosition(Vec2(xPos,yPos));

		_ticks++;
	}
	else {
		counter++;
		Node *block;
		if (_blockLevel1 > (sizeof(_displayWord) / sizeof(_displayWord[0]))) {
			std::ostringstream blockName;	blockName << "blockLevel1" << (sizeof(_displayWord) / sizeof(_displayWord[0])); std::string blockNameInString = blockName.str();
			block = this->getChildByName(blockNameInString);
		}
		else {
			std::ostringstream blockName;	blockName << "blockLevel1" << _blockLevel1; std::string blockNameInString = blockName.str();
			block = this->getChildByName(blockNameInString);
		}

		_yStart = block->getPositionY() + block->getContentSize().height;      // Pixels

		if(counter%2 == 0){
			_xStart = block->getPositionX() - block->getContentSize().width / 2;      // Pixels
			_xStop = block->getPositionX() + block->getContentSize().width / 2;    // Pixels
		}
		else {
			_xStart = block->getPositionX() + block->getContentSize().width / 2;      // Pixels
			_xStop = block->getPositionX() - block->getContentSize().width / 2;    // Pixels
		}
		_ticks = 0;
		_ticksTotal = DURATION / SECONDS_PER_TICK;

	}
}

void Owl::UpdateAnimationSecond(float dt)
{
	double DURATION = 5; // Seconds for total animation.
	double SECONDS_PER_TICK = 1.0 / 60;
	double _xSpeed = (_xStopSecond - _xStartSecond) / DURATION;

	if (_ticks2 <= _ticksTotal2)
	{
		double Y_HEIGHT = 40;
		double _xSpeed = (_xStopSecond - _xStartSecond) / DURATION;
		double seconds = _ticks2*SECONDS_PER_TICK;

		double xPos = _xStartSecond + seconds*_xSpeed;
		double yPos = _yStartSecond + Y_HEIGHT*sin(seconds * 2 * M_PI / 2.5); // (/1) Seconds for y cycle.
		_opponent->setPosition(Vec2(xPos, yPos));

		_ticks2++;
	}
	else {
		counter2++;
		Node *block;
		if (_blockLevel2 > (sizeof(_displayWord) / sizeof(_displayWord[0]))) {
			std::ostringstream blockName;	blockName << "blockLevel2" << (sizeof(_displayWord) / sizeof(_displayWord[0])); std::string blockNameInString = blockName.str();
			block = this->getChildByName(blockNameInString);
		}
		else {
			std::ostringstream blockName;	blockName << "blockLevel2" << _blockLevel2; std::string blockNameInString = blockName.str();
			block = this->getChildByName(blockNameInString);
		}

		_yStartSecond = block->getPositionY() + block->getContentSize().height * _owlPropertyMap.at(_owlCurrentTheme).at("scaleSecond");      // Pixels

		if (counter2 % 2 == 0) {
			_xStartSecond = block->getPositionX() - (block->getContentSize().width / 2 * _owlPropertyMap.at(_owlCurrentTheme).at("scaleSecond"));      // Pixels
			_xStopSecond = block->getPositionX() + (block->getContentSize().width / 2 * _owlPropertyMap.at(_owlCurrentTheme).at("scaleSecond"));    // Pixels
		}
		else {
			_xStartSecond = block->getPositionX() + (block->getContentSize().width / 2 * _owlPropertyMap.at(_owlCurrentTheme).at("scaleSecond"));      // Pixels
			_xStopSecond = block->getPositionX() - (block->getContentSize().width / 2 * _owlPropertyMap.at(_owlCurrentTheme).at("scaleSecond"));    // Pixels
		}
		_ticks2 = 0;
		_ticksTotal2 = DURATION / SECONDS_PER_TICK;

	}
}