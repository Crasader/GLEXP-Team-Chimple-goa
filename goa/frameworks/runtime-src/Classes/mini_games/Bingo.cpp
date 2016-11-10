#include "Bingo.h"
#include "SimpleAudioEngine.h"
#include "math.h"
#include "editor-support/cocostudio/CocoStudio.h"

USING_NS_CC;

Scene* Bingo::createScene()
{
	// 'layer' is an autorelease object
	auto layer = Bingo::create();
	auto scene = Scene::create();

	scene->addChild(layer);
	layer->_menuContext = MenuContext::create(layer, Bingo::gameName());
	scene->addChild(layer->_menuContext);
	return scene;
}
// on 'init' you need to initialize your instance
bool Bingo::init()
{
	if (!Layer::init())
	{
		return false;
	}
	return true;
}

void Bingo::onEnterTransitionDidFinish()
{

	std::map<std::string, std::map<std::string, std::string>> sceneMap = {
		{
			{ "bingojungle",
							{
								{ "bg", "jungle/bingojungle.csb" },
								{ "box", "jungle/jungleb/letterbox.png" },
								{ "boxshade", "jungle/jungleb/letterboxshade.png" },
								{ "_resourcePath", "jungle/" },
								{ "griddimension", _bingoGridDimension }
							}
			},
			{ "bingocity",
							{
								{ "bg", "bingo/bingocity/bingocity.csb" },
								{ "box", "bingocity/letterbox.png" },
								{ "boxshade", "bingocity/letterboxshade.png" },
								{ "_resourcePath", "bingo/bingocity/" },
								{ "griddimension", _bingoGridDimension }
							}
			},
			{ "bingofarm",
							{
								{ "bg", "bingo/bingofarm/bingofarm.csb" },
								{ "box", "bingofarm/letterbox.png" },
								{ "boxshade", "bingofarm/letterboxshade.png" },
								{ "_resourcePath", "bingo/bingofarm/" },
								{ "griddimension", _bingoGridDimension }
							}
			}
		}
	};
	std::map<std::string, std::map<std::string, std::map<std::string, float>>> sceneGridValueMap = {

		 { "bingojungle",
						{
							{ "threeByThree",
												{
													{ "pairRequired", 9.0f },
													{ "addXFactor", 0.17f },
													{ "addYFactor", 0.18f },
													{ "bincapacity", 3.0f },
													{ "scale",1.0f },
													{ "bingoAnimScale",0.5f },
													{ "animationLoop", 1.0f },
													{ "helpLetterYFactor", 0.87 }
												}
							},
						    { "fourByFour",
											{
												{ "pairRequired", 16.0f },
												{ "addXFactor", 0.13f },
												{ "addYFactor", 0.15f },
												{ "bincapacity", 4.0f },
												{ "scale",0.75f },
												{ "bingoAnimScale",0.35f },
												{ "animationLoop", 1.0f },
												{ "helpLetterYFactor",0.87 }
											}
							},
							{ "fiveByFive",
											{
												{ "pairRequired", 25.0f },
												{ "addXFactor", 0.10f },
												{ "addYFactor", 0.125f },
												{ "bincapacity", 5.0f },
												{ "scale",0.6f },
												{ "bingoAnimScale",0.2f },
												{ "animationLoop", 1.0f },
												{ "helpLetterYFactor", 0.87 }
											}
							}
		} },
		{ "bingocity",
						{
						 { "threeByThree",
											{
												{ "pairRequired", 9.0f },
												{ "addXFactor", 0.193f },
												{ "addYFactor", 0.215f },
												{ "bincapacity", 3.0f },
												{ "scale",1.0f },
												{ "bingoAnimScale",0.5f },
												{ "animationLoop", 1.0f },
												{ "helpLetterYFactor", 0.91 }
											}
					     },
					    { "fourByFour",
											{
												{ "pairRequired", 16.0f },
												{ "addXFactor", 0.150f },
												{ "addYFactor", 0.184f },
												{ "bincapacity", 4.0f },
												{ "scale",0.75f },
												{ "bingoAnimScale",0.35f },
												{ "animationLoop", 1.0f },
												{ "helpLetterYFactor", 0.91 }
											}
					  },
					  { "fiveByFive",
											{
												{ "pairRequired", 25.0f },
												{ "addXFactor", 0.124f },
												{ "addYFactor", 0.149f },
												{ "bincapacity", 5.0f },
												{ "scale",0.6f },
												{ "bingoAnimScale",0.25f },
												{ "animationLoop", 1.0f },
												{ "helpLetterYFactor", 0.91 }
											}
				    }
			}
		},
		{ "bingofarm",
		              {
			             { "threeByThree",
											{
												{ "pairRequired", 9.0f },
												{ "addXFactor", 0.193f },
												{ "addYFactor", 0.229f },
												{ "bincapacity", 3.0f },
												{ "scale",1.0f },
												{ "bingoAnimScale",0.55f },
												{ "animationLoop", 0.0f },
												{ "helpLetterYFactor", 0.91 }
											}
						},
						{ "fourByFour",
											{
												{ "pairRequired", 16.0f },
												{ "addXFactor", 0.150f },
												{ "addYFactor", 0.192f },
												{ "bincapacity", 4.0f },
												{ "scale",0.75f },
												{ "bingoAnimScale",0.40f },
												{ "animationLoop", 0.0f },
												{ "helpLetterYFactor", 0.91 }
											}
						},
						{ "fiveByFive",
											{
												{ "pairRequired", 25.0f },
												{ "addXFactor", 0.124f },
												{ "addYFactor", 0.165f },
												{ "bincapacity", 5.0f },
												{ "scale",0.6f },
												{ "bingoAnimScale",0.25f },
												{ "animationLoop", 0.0f },
												{ "helpLetterYFactor", 0.91 }
											}
						}
				}
		},

	};
	std::map<int, std::string> bingoGridMapping = {

		{ 0,	"fiveByFive" },
		{ 1,	"threeByThree" },
		{ 2,    "fourByFour" }
	};

	std::map<int, std::string> bingoSceneMapping = {

		{ 0,	"bingofarm" },
		{ 1,	"bingojungle" },
		{ 2,    "bingocity" }
	};

	
	int gameCurrentLevel = _menuContext->getCurrentLevel();
	std::pair<int, int> levelKeyNumber = levelAllInfo(gameCurrentLevel, 12, 3, 4, 3);
	_bingoGridDimension = bingoGridMapping.at(levelKeyNumber.first);
	_bingoCurrentTheme = bingoSceneMapping.at(levelKeyNumber.second);

	_scenePath = sceneMap.at(_bingoCurrentTheme);
	std::map<std::string, std::map<std::string, float>> sample_A = sceneGridValueMap.at(_bingoCurrentTheme);
	_gridBasedValue = sample_A.at(_bingoGridDimension);

	if (levelKeyNumber.second == 0)
	{
		int pairNo = static_cast<int>(_gridBasedValue.at("pairRequired"));
		_data = TextGenerator::getInstance()->getHomonyms(pairNo);
		_menuContext->setMaxPoints(pairNo*5);
	}
	else if (levelKeyNumber.second == 1)
	{
		_bingoCurrentTheme = "bingojungle";
		int pairNo = static_cast<int>(_gridBasedValue.at("pairRequired"));
		_data = TextGenerator::getInstance()->getSynonyms(pairNo);
		_menuContext->setMaxPoints(pairNo*5);
	}
	else
	{
		_bingoCurrentTheme = "bingocity";
		int pairNo = static_cast<int>(_gridBasedValue.at("pairRequired"));
		_data = TextGenerator::getInstance()->getAntonyms(pairNo);
		_menuContext->setMaxPoints(pairNo*5);
	}

	//BackGround
	auto bingoBackground = CSLoader::createNode(_scenePath.at("bg"));
	this->addChild(bingoBackground, 0);

	Vector <Node*> children = bingoBackground->getChildren();
	int size = children.size();
	for (auto item = children.rbegin(); item != children.rend(); ++item) {
		Node * monsterItem = *item;
		std::string str = monsterItem->getName().c_str();
		CCLOG("name : %s", str.c_str());
	}

	std::string charFaceName[6];
	if (!_bingoCurrentTheme.compare("bingocity"))
	{
		CCSpriteFrameCache* framecache1 = CCSpriteFrameCache::sharedSpriteFrameCache();
		framecache1->addSpriteFramesWithFile("bingocity/bingocity.plist");
		charFaceName[0] = "bear"; charFaceName[1] = "cat"; charFaceName[2] = "elephant"; charFaceName[3] = "giraffe"; charFaceName[4] = "lion"; charFaceName[5] = "pig";

		_boxBoard = (Sprite *)bingoBackground->getChildByName("board");
		_helpBoard = (Sprite *)bingoBackground->getChildByName("boardhelp");
	}
	else if (!_bingoCurrentTheme.compare("bingojungle"))
	{
		CCSpriteFrameCache* framecache1 = CCSpriteFrameCache::sharedSpriteFrameCache();
		framecache1->addSpriteFramesWithFile(_scenePath.at("_resourcePath") + "junglea/junglea.plist");
		CCSpriteFrameCache* framecache2 = CCSpriteFrameCache::sharedSpriteFrameCache();
		framecache1->addSpriteFramesWithFile(_scenePath.at("_resourcePath") + "jungleb/jungleb.plist");
		CCSpriteFrameCache* framecache3 = CCSpriteFrameCache::sharedSpriteFrameCache();
		framecache1->addSpriteFramesWithFile(_scenePath.at("_resourcePath") + "junglec/junglec.plist");

		_boxBoard = (Sprite *)bingoBackground->getChildren().at(0)->getChildByName("board");
		_helpBoard = (Sprite *)bingoBackground->getChildren().at(0)->getChildByName("boardhelp");

		charFaceName[0] = "chimp"; charFaceName[1] = "giraffe"; charFaceName[2] = "leopard"; charFaceName[3] = "lion"; charFaceName[4] = "zebra"; charFaceName[5] = "wildebeest";
	}
	else
	{
		CCSpriteFrameCache* framecache1 = CCSpriteFrameCache::sharedSpriteFrameCache();
		framecache1->addSpriteFramesWithFile("bingofarm/bingofarm.plist");

		_boxBoard = (Sprite *)bingoBackground->getChildByName("board");
		_helpBoard = (Sprite *)bingoBackground->getChildByName("boardhelp");

		charFaceName[0] = "cabbage"; charFaceName[1] = "cauliflower"; charFaceName[2] = "pumplin"; charFaceName[3] = "watermelon"; charFaceName[4] = "muskmelon"; charFaceName[5] = "pineapple";
	}

	/*Vector <Node*> children = bingoBackground->getChildren();
	for (auto item = children.rbegin(); item != children.rend(); ++item) {
	Node * monsterItem = *item;
	std::string str = monsterItem->getName().c_str();
	CCLOG("name : %s", str.c_str());
	}*/

	if (visibleSize.width > 2560) {
		auto myGameWidth = (visibleSize.width - 2560) / 2;
		bingoBackground->setPositionX(myGameWidth);
	}

	for (std::map<std::string, std::string>::iterator it = _data.begin(); it != _data.end(); ++it) {
		_data_key.push_back(it->first);
	}

	for (std::map<std::string, std::string>::iterator it = _data.begin(); it != _data.end(); ++it) {
		_data_value.push_back(it->second);
	}

	std::vector<int> randomIndex;
	int a = _data.size();

	while (randomIndex.size() != _data.size()) {
		bool duplicateCheck = true;
		int numberPicker = RandomHelper::random_int(0, a - 1);
		for (int i = 0; i < randomIndex.size(); i++) {
			if (numberPicker == randomIndex[i]) {
				duplicateCheck = false;
			}
		}
		if (duplicateCheck) {
			randomIndex.push_back(numberPicker);
		}
	}

	float addX = 0;
	float addY = 0;
	_boxContainer.clear();
	_charFace.clear();
	_charAnimContainer.clear();
	_bingoAnimBin.clear();
	_bingoAnimTimelineBin.clear();

	addX = _boxBoard->getBoundingBox().size.width * _gridBasedValue.at("addXFactor");
	addY = _boxBoard->getBoundingBox().size.height * _gridBasedValue.at("addYFactor");

	int binCapacity = static_cast<int>(_gridBasedValue.at("bincapacity"));
	_boxContainer = Bingo::createGrid(binCapacity, binCapacity);
	_charFace = Bingo::createGrid(binCapacity, binCapacity);
	_charAnimContainer = Bingo::createGridOfCharcater(binCapacity, binCapacity);
	_bingoAnimBin = Bingo::createGrid(binCapacity, binCapacity);
	_bingoAnimTimelineBin = Bingo::createGridOfCharcater(binCapacity, binCapacity);

	setWordInHelpBoard();

	auto boxId = 0;
	Sprite* box;
	Sprite*	boxShade;
	Sprite* bingoFace;
	Sprite* wrong;
	int Boxcounter =0;
	cocos2d::LabelTTF * label;

	for (int i = 0; i<_boxContainer.size(); i++)
	{
		for (int j = 0; j<_boxContainer.size(); j++)
		{
			box = Sprite::createWithSpriteFrameName(_scenePath.at("box"));
			float c = box->getBoundingBox().size.width / 2;
			float d = box->getBoundingBox().size.height / 2;
			setAllSpriteProperties(box, 3, addX, addY, true, 0.5, 0.5, 0, _gridBasedValue.at("scale"), _gridBasedValue.at("scale"), _boxBoard);
			box->setTag(0);

			boxShade = Sprite::createWithSpriteFrameName(_scenePath.at("boxshade"));
			setAllSpriteProperties(boxShade, 0, addX, addY, true, 0.5, 0.5, 0, _gridBasedValue.at("scale"), _gridBasedValue.at("scale"), _boxBoard);

			//Bingo Last Animation

			auto bingoTimeline = CSLoader::createTimeline("jungle/bingostar.csb");
			auto bingoAnim = (Sprite *)CSLoader::createNode("jungle/bingostar.csb");
			setAllSpriteProperties(bingoAnim, 1, addX, addY, false, 0.5, 0.5, 0, _gridBasedValue.at("bingoAnimScale"), _gridBasedValue.at("bingoAnimScale"), _boxBoard);

			_bingoAnimBin[i][j] = bingoAnim;
			 bingoAnim->runAction(bingoTimeline);
			_bingoAnimTimelineBin[i][j] = bingoTimeline;

			//Label

			label = LabelTTF::create(_data_key[randomIndex[boxId]], "Helvetica", 100);
			label->setPosition(c, d);
			label->setAnchorPoint(Vec2(0.5, 0.5));
			box->addChild(label, 3);

			label->setName(_data_value[randomIndex[boxId]]);
			boxId++;

			std::ostringstream str_i;
			str_i << i;
			std::string string_i = str_i.str();

			std::ostringstream str_j;
			str_j << j;
			std::string string_j = str_j.str();

			_boxContainer[i][j] = box;
			_boxContainer[i][j]->setName("box" + string_i + string_j);
			addEvents(box);

			//ANIMATION PART
			std::string index = charFaceName[RandomHelper::random_int(0, 5)];
			auto charTimeline = CSLoader::createTimeline(_scenePath.at("_resourcePath") + index + ".csb");
			auto charFace = (Sprite *)CSLoader::createNode(_scenePath.at("_resourcePath") + index + ".csb");
			setAllSpriteProperties(charFace, 2, addX, addY, false, 0.5, 0.5, 0, _gridBasedValue.at("scale"), _gridBasedValue.at("scale"), _boxBoard);
			charFace->setGlobalZOrder(4);

			charFace->runAction(charTimeline);
			_charAnimContainer[i][j] = charTimeline;
			_charFace[i][j] = charFace;

			addX += box->getBoundingBox().size.width + _boxBoard->getBoundingBox().size.width * 0.011;
			Boxcounter++;
			if (_menuContext->getCurrentLevel() == 1 && Boxcounter ==1)
			{
				creatHelp(box, _helpBoard);
			}
		}

		addY = addY + box->getBoundingBox().size.height + _boxBoard->getBoundingBox().size.width *0.013;
		addX = _boxBoard->getBoundingBox().size.width * _gridBasedValue.at("addXFactor");
	}
	/*Vector <Node*> children = bingoBackground->getChildren().at(0)->getChildren();
	for (auto item = children.rbegin(); item != children.rend(); ++item) {
	Node * monsterItem = *item;
	std::string str = monsterItem->getName().c_str();
	CCLOG("name : %s", str.c_str());
	}*/

}
Bingo::~Bingo(void)
{

}
Bingo::Bingo(void)
{

}
void Bingo::creatHelp(Sprite* letterBox, Sprite* helpBox)
{
	auto box1 = letterBox->getPosition() +Vec2(visibleSize.width * 0.058, visibleSize.height * 0.07);
	auto box2 = helpBox->getPosition() +Vec2(visibleSize.width * 0.024, -visibleSize.height * 0.01);

	_help = HelpLayer::create(Rect(box1.x, box1.y, letterBox->getContentSize().width*1.3, letterBox->getContentSize().height*1.3), Rect(box2.x, box2.y, helpBox->getContentSize().width*1.4, helpBox->getContentSize().height*1.3));
	_help->click(Vec2(box1.x, box1.y));
	_isHelpDone = 0;
 	 this->addChild(_help);
}
std::pair<int, int> Bingo::levelAllInfo(int currentLevel, int sceneRepetitionNo, int totalScene, int catagoryRepetitionNo, int totalcatagory)
{
	float currentLevelInFloat = static_cast<float>(currentLevel);
	int sceneBaseValue = static_cast<int>(std::ceil(currentLevelInFloat / sceneRepetitionNo));
	int sceneNo = sceneBaseValue % totalScene;

	int catagoryBaseValue = static_cast<int>(std::ceil(currentLevelInFloat / catagoryRepetitionNo));
	int catagoryNo = catagoryBaseValue % totalcatagory;

	return std::make_pair(sceneNo, catagoryNo);
}
void Bingo::setAllSpriteProperties(Sprite* sprite, int zOrder, float posX, float posY, bool visibility, float anchorPointX, float anchorPointY, float rotation, float scaleX, float scaleY, Sprite* parent)
{
	sprite->setPosition(Vec2(posX + origin.x, posY + origin.y));
	sprite->setAnchorPoint(Vec2(anchorPointX, anchorPointY));
	sprite->setScaleX(scaleX);
	sprite->setScaleY(scaleY);
	sprite->setVisible(visibility);
	sprite->setRotation(rotation);
	parent->addChild(sprite, zOrder);
}

void::Bingo::setWordInHelpBoard()
{
	if (_label != NULL)
	{
		for (int i = 0; i < _data_value.size(); i++)
		{
			if (_label->getString().compare(_data_value[i]) == 0)
			{
				this->removeChild(_label, true);
				_data_value.erase(_data_value.begin() + i);
				break;
			}
		}
	}
	int size = _data_value.size() - 1;
	if (size != -1)
	{
		_label = LabelTTF::create(_data_value[RandomHelper::random_int(0, size)], "Helvetica", 200);
		_label->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height*_gridBasedValue.at("helpLetterYFactor"));
		_label->setAnchorPoint(Vec2(0.5, 0.5));
		this->addChild(_label, 3);
	}
}
void Bingo::addEvents(Sprite* clickedObject)
{
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);

	listener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		auto target = event->getCurrentTarget();
		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode) && _flagForSingleTouch)
		{
			if (!_isBingoDone)
			{
				_flagForSingleTouch = false;
				bool bingo = false;
				std::string helpLabelPair = target->getChildren().at(0)->getName();
				if (helpLabelPair.compare(_label->getString()) == 0)
				{
					target->setVisible(false);
					target->setTag(1);
					setWordInHelpBoard();
					_menuContext->addPoints(5);

					auto targetName = target->getName();
					for (int i = 0; i < _boxContainer.size(); i++)
					{
						for (int j = 0; j < _boxContainer.size(); j++)
						{
							if (targetName == _boxContainer[i][j]->getName())
							{

								bool animationLoop = true;
								if (_gridBasedValue.at("animationLoop"))
									animationLoop = true;
								else
									animationLoop = false;

								_boxContainer[i][j]->getEventDispatcher()->removeEventListener(listener);
								_charAnimContainer[i][j]->gotoFrameAndPlay(0, animationLoop);

								charAnimation(i, j);
							}
						}
					}
				}
				else
				{
					FShake* shake = FShake::actionWithDuration(0.5f, 5.0f);
					target->runAction(shake);
					_menuContext->addPoints(-2);
				}
				if (_menuContext->getCurrentLevel() == 1 && _isHelpDone == 0)
				{
					this->removeChild(_help, true);
					_isHelpDone = 1;
				}
				bingo = bingoChecker(bingo);

				if (bingo)
				{
					_isBingoDone = true;
					auto callShowScore = CCCallFunc::create([=] {
						_menuContext->showScore();
					});
					this->runAction(Sequence::create(DelayTime::create(5), callShowScore, NULL));
				}
				/* this->runAction(Sequence::create(DelayTime::create(4), CallFunc::create([=]() {_flagForSingleTouch = true; }), NULL));*/
			}
			this->runAction(Sequence::create(DelayTime::create(0.5), CallFunc::create([=]() {_flagForSingleTouch = true; }), NULL));
		}
		return false;
	};
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, clickedObject);
}

std::vector<std::vector<Sprite*>> Bingo::createGrid(int row, int column)
{
	std::vector<std::vector<Sprite*>> tempContainer;

	tempContainer.resize(row);
	for (int i = 0; i < row; ++i)
		tempContainer[i].resize(column);

	return tempContainer;
}
std::vector<std::vector<cocostudio::timeline::ActionTimeline *>> Bingo::createGridOfCharcater(int row, int column)
{
	std::vector<std::vector<cocostudio::timeline::ActionTimeline *>> tempContainer;

	tempContainer.resize(row);
	for (int i = 0; i < row; ++i)
		tempContainer[i].resize(column);
	return tempContainer;
}
void Bingo::charAnimation(int i_index, int j_index)
{
	auto sequence_E = ScaleTo::create(1, (_gridBasedValue.at("scale") - 0.1));
	auto sequence_F = ScaleTo::create(1, _gridBasedValue.at("scale"));

	auto sequence_scale = Sequence::create(sequence_E, DelayTime::create(1), sequence_F, NULL);

	auto sequence_A = MoveBy::create(0.5, Vec2(10, 0));
	auto sequence_B = MoveBy::create(0.5, Vec2(0, -10));
	auto sequence_C = MoveBy::create(0.5, Vec2(0, 10));
	auto sequence_D = MoveBy::create(0.5, Vec2(-10, 0));
	auto sequence_rotate = Sequence::create(sequence_A, sequence_B, sequence_C, sequence_D, NULL);

	auto mySpawn = Spawn::createWithTwoActions(sequence_scale, sequence_rotate);

	auto action = RepeatForever::create(mySpawn);
	_charFace[i_index][j_index]->setVisible(true);
	_charFace[i_index][j_index]->runAction(action);
}

bool Bingo::bingoChecker(bool bingo)
{
	if (-1 != bingoHorizotally()) {
		bingo = true;
		int row = bingoHorizotally();
		auto delay = 0.1;
		for (int j = 0; j < _boxContainer.size(); j++)
		{
			auto sequenceDot = Sequence::create(DelayTime::create(delay), CCCallFunc::create([=] {
				_bingoAnimBin[row][j]->setVisible(true);
				_bingoAnimTimelineBin[row][j]->gotoFrameAndPlay(0, true);
			}), NULL);
			this->runAction(sequenceDot);
			delay = delay + 0.2;
		}
	}
	if (-1 != bingoVertically()) {
		bingo = true;
		auto delay = 0.1;
		int column = bingoVertically();
		for (int i = 0; i < _boxContainer.size(); i++)
		{
			auto sequenceDot = Sequence::create(DelayTime::create(delay), CCCallFunc::create([=] {
				_bingoAnimBin[i][column]->setVisible(true);
				_bingoAnimTimelineBin[i][column]->gotoFrameAndPlay(0, true);
			}), NULL);
			this->runAction(sequenceDot);
			delay = delay + 0.2;
		}
	}
	if (-1 != bingoRightDiagonally()) {
		bingo = true;
		auto delay = 0.1;
		for (int i = 0; i<_boxContainer.size(); i++)
		{
			auto sequenceDot = Sequence::create(DelayTime::create(delay), CCCallFunc::create([=] {
				_bingoAnimBin[i][i]->setVisible(true);
				_bingoAnimTimelineBin[i][i]->gotoFrameAndPlay(0, true);
			}), NULL);
			this->runAction(sequenceDot);
			delay = delay + 0.2;
		}
	}
	if (-1 != bingoLeftDiagonally()) {
		bingo = true;
		auto delay = 0.1;
		for (int i = 0; i < _boxContainer.size(); i++)
		{
			auto sequenceDot = Sequence::create(DelayTime::create(delay), CCCallFunc::create([=] {
				_bingoAnimBin[i][_boxContainer.size() - 1 - i]->setVisible(true);
				_bingoAnimTimelineBin[i][_boxContainer.size() - 1 - i]->gotoFrameAndPlay(0, true);
			}), NULL);
			this->runAction(sequenceDot);
			delay = delay + 0.2;
		}
	}
	return bingo;
}

int Bingo::bingoHorizotally()
{
	int counter = 0;
	for (int i = 0; i < _boxContainer.size(); i++)
	{
		for (int j = 0; j < _boxContainer.size(); j++)
		{
			if (_boxContainer[i][j]->getTag() == 1)
			{
				counter++;
				if (counter == _boxContainer.size())
				{
					return i;
				}
			}
			else
			{
				break;
			}
		}
		counter = 0;
	}
	return -1;
}

int Bingo::bingoVertically()
{
	int counter = 0;
	for (int j = 0; j<_boxContainer.size(); j++)
	{
		for (int i = 0; i<_boxContainer.size(); i++)
		{
			if (_boxContainer[i][j]->getTag() == 1)
			{
				counter++;
				if (counter == _boxContainer.size())
				{
					return j;
				}
			}
			else
			{
				break;
			}
		}
		counter = 0;
	}
	return -1;
}
int Bingo::bingoRightDiagonally()
{

	int counter = 0;
	for (int i = 0; i<_boxContainer.size(); i++)
	{
		if (_boxContainer[i][i]->getTag() == 1)
		{
			counter++;
			if (counter == _boxContainer.size())
			{
				return i + 1;
			}
		}
		else
		{
			break;
		}
	}
	return -1;
}
int Bingo::bingoLeftDiagonally()
{
	int counter = 0;
	for (int i = 0; i<_boxContainer.size(); i++)
	{
		if (_boxContainer[i][_boxContainer.size() - 1 - i]->getTag() == 1)
		{
			counter++;
			if (counter == _boxContainer.size())
			{
				return i + 1;
			}
		}
		else
		{
			break;
		}
	}
	return -1;
}
