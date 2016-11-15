#include "BlastLetter.h"

USING_NS_CC;

Scene* BlastLetter::createScene()
{
	auto scene = Scene::create();
	auto layer = BlastLetter::create();
	scene->addChild(layer);
	layer->_menuContext = MenuContext::create(layer, BlastLetter::gameName());
	scene->addChild(layer->_menuContext);
	return scene;
}

BlastLetter *BlastLetter::create() {
	BlastLetter *blast = new (std::nothrow) BlastLetter();
	if (blast && blast->init()) {
		blast->autorelease();
		return blast;
	}
	CC_SAFE_DELETE(blast);
	return nullptr;

}

bool BlastLetter::init()
{
	if (!Layer::init()) { return false;}

	return true;
}

void BlastLetter::onEnterTransitionDidFinish() {
	//screen_blast
	Node* bg = CSLoader::createNode("blastletter/blastletter.csb");
	addChild(bg);
	bg->setName("bg");

	if (Director::getInstance()->getVisibleSize().width > 2560) {
		auto myGameWidth = (Director::getInstance()->getVisibleSize().width - 2560) / 2;
		bg->setPositionX(myGameWidth);
	}

	auto currentLevel = _menuContext->getCurrentLevel();
	_data_key = getConvertInUpperCase(TextGenerator::getInstance()->generateAWord(1));
	_data_value = _data_key;
	if (currentLevel >= 1 && currentLevel <= 26) {
		auto charcaterStream = LangUtil::getInstance()->getAllCharacters();
		std::ostringstream namemyLabel;
		_data_key = charcaterStream[(currentLevel - 1)];
		for (int i = 0; i < 6; i++) {
			namemyLabel << _data_key;
		}
		_data_value = namemyLabel.str();

	}else if (currentLevel >= 27 && currentLevel <= 36) {
		wchar_t* const allNumbers = L"0123456789";
		std::ostringstream namemyLabel;
		_data_key = allNumbers[(currentLevel - 27)];
		for (int i = 0; i < 6; i++) {
			namemyLabel << _data_key;
		}
		_data_value = namemyLabel.str();
	}else if (currentLevel >= 37 && currentLevel <= 46) {
		_data_key = TextGenerator::getInstance()->generateAWord((_menuContext->getCurrentLevel() - 36));
		_data_value = _data_key;
	}else if (currentLevel >= 47 && currentLevel <= 56) {
		_data = TextGenerator::getInstance()->getSingularPlurals(1, (_menuContext->getCurrentLevel() - 46));
	}else if (currentLevel >= 57 && currentLevel <= 66) {
		_data = TextGenerator::getInstance()->getAntonyms(1, (_menuContext->getCurrentLevel() - 56));
	}else if (currentLevel >= 67 && currentLevel <= 76) {
		_data = TextGenerator::getInstance()->getSynonyms(1, (_menuContext->getCurrentLevel() - 66));
	}else if (currentLevel >= 77 && currentLevel <= 86) {
		_data = TextGenerator::getInstance()->getHomonyms(1, (_menuContext->getCurrentLevel() - 76));
	}else{
		CCLOG("ERROR : Level code error !!!!!! ");
	}
	if(currentLevel >= 47 && currentLevel <= 86)
	for (std::map<std::string, std::string>::iterator it = _data.begin(); it != _data.end(); ++it) {
		_data_key = (getConvertInUpperCase(it->first));
		_data_value = (getConvertInUpperCase(it->second));
	}
	_menuContext->setMaxPoints(_data_value.size());
	auto coord = getAllGridCoord(1, _data_value.size());
	for (size_t coordIndex = 0; coordIndex < _data_value.size(); coordIndex++) {
		auto letterBoardSprite = Sprite::create();
		letterBoardSprite->setTextureRect(Rect(0, 0, 350, 380));
		letterBoardSprite->setColor(Color3B(219, 224, 252));
		letterBoardSprite->setPosition(Vec2(coord.at(coordIndex).second, coord.at(coordIndex).first));		
		addChild(letterBoardSprite);

//		auto myLabel = Label::createWithBMFont(LangUtil::getInstance()->getBMFontFileName(), LangUtil::convertUTF16CharToString(_data_value[coordIndex]));
		auto myLabel = LabelTTF::create(LangUtil::convertUTF16CharToString(_data_value[coordIndex]), "res/fonts/BalooBhai-Regular.ttf", letterBoardSprite->getContentSize().height);
		myLabel->setPosition(Vec2(letterBoardSprite->getContentSize().width * 0.5, letterBoardSprite->getContentSize().height * 0.45));
		myLabel->setScale(1);
		myLabel->setColor(Color3B::GRAY);
		std::ostringstream namemyLabel;
		namemyLabel << (coordIndex+1);
		myLabel->setName(namemyLabel.str());
		letterBoardSprite->addChild(myLabel);

		std::ostringstream nameLetterBoard;
		nameLetterBoard << myLabel->getString() << (coordIndex + 1);

		letterBoardSprite->setName(nameLetterBoard.str());
		letterBoardSprite->setTag(coordIndex+1);
		addEventsOnGrid(letterBoardSprite);

		if (coordIndex == 0) {
			myLabel->setRotation(20);
			myLabel->runAction(RepeatForever::create(shakingCharacter()));
		}
	}
		auto myLabel = LabelTTF::create(_data_key, "Helvetica", this->getChildByName("bg")->getChildByName("topboard ")->getContentSize().height *0.8);
		myLabel->setPosition(Vec2(this->getChildByName("bg")->getChildByName("topboard ")->getContentSize().width/2, this->getChildByName("bg")->getChildByName("topboard ")->getContentSize().height/2));
		myLabel->setName(myLabel->getString());
		this->getChildByName("bg")->getChildByName("topboard ")->addChild(myLabel);

		if (_menuContext->getCurrentLevel() == 1) {
			std::ostringstream nameLetterBoard;
			nameLetterBoard << LangUtil::convertUTF16CharToString(_data_value[_counterLetter]) << (_counterLetter + 1);
			auto board = this->getChildByName("bg")->getChildByName("topboard ");
			auto downGrid = this->getChildByName(nameLetterBoard.str());
			this->getChildByName("bg")->getChildByName("topboard ")->setPositionX(Director::getInstance()->getVisibleSize().width / 2 - (board->getContentSize().width / 2));
			auto help = HelpLayer::create(Rect(downGrid->getPositionX(), downGrid->getPositionY(), downGrid->getContentSize().width, downGrid->getContentSize().height), Rect(Director::getInstance()->getVisibleSize().width / 2 + 70, board->getContentSize().height / 2 + board->getPositionY(), board->getContentSize().width * 0.9, board->getContentSize().height));
			help->click(Vec2(downGrid->getPositionX(), downGrid->getPositionY()));
			help->setName("helpLayer");
			this->addChild(help, 4);
		}
		this->scheduleUpdate();
}

std::vector<std::pair<int, int>> BlastLetter::getAllGridCoord(int rowData, int columnData)
{
	std::vector<std::pair<int, int>> coord;
	auto win = Director::getInstance()->getVisibleSize();
	int gridWidth = win.width/(columnData +1), gridHeight = win.height/(rowData +1) ;
	int rowCoord = 0, columnCoord = 0;

	for (int row = 0; row < rowData; row++) {
		rowCoord = rowCoord + gridHeight;
		for (int column = 0; column < columnData; column++) {
			columnCoord = columnCoord + gridWidth;
			coord.push_back(std::make_pair(win.height - rowCoord, columnCoord));
		}
		columnCoord = 0;
	}
	return coord;
}

void BlastLetter::update(float delta) {

	if(_checkingAlphabets)
		checkAlphabets();

}

void BlastLetter::removeAllWritingScene()
{
	std::ostringstream stringStream;
	stringStream << "Node" << (_counterLetter + 1);
	auto timelineBlast = CSLoader::createTimeline("blastletter/screen_blast.csb");	
	this->getChildByName("blastScene")->runAction(timelineBlast);
	timelineBlast->play("bang", false);
	((BlastLetterNode *)this->getChildByName(stringStream.str()))->_drawingBoard->removeAllChildren();
	((BlastLetterNode *)this->getChildByName(stringStream.str()))->drawAllowance(false);
	_bang = false;
	_menuContext->addPoints(-1);
	runAction(Sequence::create(DelayTime::create(3), CallFunc::create([=]() {
		std::ostringstream stringStream;
		stringStream << "Node" << (_counterLetter + 1);
		std::ostringstream nameLetterBoard;
		nameLetterBoard << LangUtil::convertUTF16CharToString(_data_value[_counterLetter])<<(_counterLetter + 1);
		auto label = this->getChildByName(nameLetterBoard.str());
		label->getChildByName(LangUtil::convertUTF16CharToString(nameLetterBoard.str().at(1)))->runAction(FadeIn::create(2.0f));
		this->removeChildByName(stringStream.str());
		this->removeChildByName("blastScene");
		this->removeChildByName("tempBoard");
		this->removeChildByName("tempBg");
		_touch = true;
	}), NULL));
	_checkingAlphabets = false;
}

Sequence* BlastLetter::shakingCharacter(){
	auto sequence_A = RotateBy::create(0.5,-40);
	auto sequence_C = RotateBy::create(0.5,40);
	return (Sequence::create(sequence_A, sequence_C, NULL));
}
bool BlastLetter::checkRecognizeLetter(string letter)
{
	if (_result.size() > 0) {
		if ((_result.at(0).compare("o") == 0 || _result.at(0).compare("0") == 0) && (LangUtil::convertUTF16CharToString(_data_value[_counterLetter]).compare("O") == 0)) {
			_result.clear();
			return true;
		}
	}

	for (size_t i = 0; i < _result.size(); i++) {
		if (_result.at(i).compare(letter) == 0) {
			_result.clear();
			return true;
		}
	}
	return false;
}

string BlastLetter::getConvertInUpperCase(string data)
{
	std::ostringstream blockName;
	int i = 0;
	while (data[i])
	{
		blockName << (char)toupper(data[i]);
		i++;
	}
	return blockName.str();
}

void BlastLetter::addEventsOnGrid(cocos2d::Sprite* callerObject)
{
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);

	listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		auto target = event->getCurrentTarget();
		Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
		if (target->getBoundingBox().containsPoint(touch->getLocation())) {
			target->setColor(Color3B::GRAY);
			auto t = target->getTag();
			if (target->getTag() == (_counterLetter+1) && _touch) {
				if (_flagTurnHelp && (_menuContext->getCurrentLevel() == 1)) {
					this->removeChildByName("helpLayer");
					_flagTurnHelp = false;
				}
				return true;
			}
			else {
				target->setColor(Color3B(219, 224, 252));
				CCLOG("The selected grid tagNo is : %d and the counter value is (count + 1 ): %d ", target->getTag(), (_counterLetter + 1));
			}
		}
		return false;
	};

	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		auto target = event->getCurrentTarget();
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);
		target->setColor(Color3B(219, 224, 252));
		_touch = false;
		if (target->getBoundingBox().containsPoint(touch->getLocation())) {
			
			auto fadeOut = FadeOut::create(2.0f);
			std::ostringstream nameLetterBoard;
			nameLetterBoard << (_counterLetter + 1);
			target->getChildByName(nameLetterBoard.str())->runAction(fadeOut);
			
			auto letterBoardSprite = Sprite::create();
			letterBoardSprite->setTextureRect(Rect(0, 0, 350, 380));
			letterBoardSprite->setColor(Color3B(219, 224, 252));
			letterBoardSprite->setPosition(Vec2(target->getPositionX(),target->getPositionY()));
			addChild(letterBoardSprite,5);
			letterBoardSprite->setName("tempBoard");
			
			auto bgLayerGradient = LayerGradient::create(Color4B(49, 42, 53,191.25), Color4B(49, 42, 53, 191.25));
			addChild(bgLayerGradient, 3);
			bgLayerGradient->setName("tempBg");
			std::ostringstream nameLetterBoards;
			nameLetterBoards << _data_value[_counterLetter];

			auto myLabel = LabelTTF::create(nameLetterBoards.str(), "res/fonts/BalooBhai-Regular.ttf", letterBoardSprite->getContentSize().height);
			myLabel->setColor(Color3B::GRAY);
			myLabel->setPosition(Vec2(letterBoardSprite->getContentSize().width * 0.5, letterBoardSprite->getContentSize().height * 0.45));
			myLabel->setScale(1);

			letterBoardSprite->addChild(myLabel);
			
			letterBoardSprite->runAction(MoveTo::create(1,Vec2(Director::getInstance()->getVisibleSize().width/2 , Director::getInstance()->getVisibleSize().height * 0.540072222)));
			letterBoardSprite->runAction(ScaleTo::create(1,3));

			auto letterCharacterBoard = CallFunc::create([=]() {
				std::ostringstream nameLetterBoard;
				nameLetterBoard << (_counterLetter + 1);
				auto fadeOut1 = FadeOut::create(1.0f);
				target->getChildByName(nameLetterBoard.str())->runAction(fadeOut1);
				auto fadeOut2 = FadeOut::create(2.0f);
				myLabel->runAction(fadeOut2);
			});
			auto letterCharacter = CallFunc::create([=]() {
				Node* popGrid = CSLoader::createNode("blastletter/screen_blast.csb");
				auto timelineBlast = CSLoader::createTimeline("blastletter/screen_blast.csb");
				
				addChild(popGrid, 4);
				popGrid->setName("blastScene");
				popGrid->runAction(timelineBlast);
				
				auto dataBoard = popGrid->getChildByName("board");
				auto dataBomb = popGrid->getChildByName("bomb_group");

				auto myGameWidth = 0.0f;
				if (Director::getInstance()->getVisibleSize().width > 2560) {
					myGameWidth = (Director::getInstance()->getVisibleSize().width - 2560) / 2;
					popGrid->setPositionX(myGameWidth);
				}
				auto BlastLetterNodeObj = BlastLetterNode::create(dataBoard->getContentSize().width, dataBoard->getContentSize().height, Vec2(dataBoard->getPositionX() + myGameWidth, dataBoard->getPositionY()));
				addChild(BlastLetterNodeObj ,4);
				std::ostringstream stringStream;
				stringStream << "Node" << target->getTag();
				BlastLetterNodeObj->setName(stringStream.str());
				_checkingAlphabets = true;
				
				timelineBlast->play("blast",false);
				timelineBlast->setAnimationEndCallFunc("blast", CC_CALLBACK_0(BlastLetter::removeAllWritingScene, this));
			
				this->removeChildByName("tempBoard");
			});

			this->runAction(Sequence::create(DelayTime::create(1), letterCharacterBoard, DelayTime::create(2), letterCharacter, NULL));
		}
		else {
			_touch = true;
			target->setColor(Color3B(219, 224, 252));
		}

		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, callerObject);
}

void BlastLetter::checkAlphabets()
{
	std::ostringstream stringStream;
	stringStream << "Node" << (_counterLetter + 1);

	if (checkRecognizeLetter(LangUtil::convertUTF16CharToString(_data_value[_counterLetter]))) {
		_menuContext->addPoints(1);
		((BlastLetterNode *)this->getChildByName(stringStream.str()))->_drawingBoard->removeAllChildren();
		((BlastLetterNode *)this->getChildByName(stringStream.str()))->setScale(1.0f / 3.0f);
		((BlastLetterNode *)this->getChildByName(stringStream.str()))->drawAllowance(false);
		std::ostringstream nameLetterBoard;
		nameLetterBoard << LangUtil::convertUTF16CharToString(_data_value[_counterLetter]) << (_counterLetter + 1);
		auto grid = this->getChildByName(nameLetterBoard.str());
		((BlastLetterNode *)this->getChildByName(stringStream.str()))->setPosition(Vec2(grid->getPositionX(), grid->getPositionY()));
		_checkingAlphabets = false;
		_touch = true;

		this->removeChildByName("blastScene");
		this->removeChildByName("tempBoard");
		this->removeChildByName("tempBg");

		_counterLetter++;
		if (_counterLetter == _data_value.size()) {
			this->runAction(Sequence::create(DelayTime::create(3), CallFunc::create([=]() {_menuContext->showScore(); }), NULL));
		}
		else {
			std::ostringstream nameLetterBoard;
			nameLetterBoard << LangUtil::convertUTF16CharToString(_data_value[_counterLetter]) << (_counterLetter + 1);
			auto label = this->getChildByName(nameLetterBoard.str());
			label->getChildByName(LangUtil::convertUTF16CharToString(nameLetterBoard.str().at(1)))->setRotation(20);
			label->getChildByName(LangUtil::convertUTF16CharToString(nameLetterBoard.str().at(1)))->runAction(RepeatForever::create(shakingCharacter()));
		}
	}
	else {
		_result = ((BlastLetterNode *)this->getChildByName(stringStream.str()))->getPosibileCharacter();
	}
}

BlastLetter::~BlastLetter(void)
{
	this->removeAllChildrenWithCleanup(true);
}
