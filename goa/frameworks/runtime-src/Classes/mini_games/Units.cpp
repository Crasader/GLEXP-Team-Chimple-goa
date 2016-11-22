#include "Units.h"


USING_NS_CC;

Scene* Units::createScene()
{
	auto scene = Scene::create();
	auto layer = Units::create();
	scene->addChild(layer);
	layer->_menuContext = MenuContext::create(layer, Units::gameName());
	scene->addChild(layer->_menuContext);
	return scene;
}

Units *Units::create() {
	Units *units = new (std::nothrow) Units();
	if (units && units->init()) {
		units->autorelease();
		return units;
	}
	CC_SAFE_DELETE(units);
	return nullptr;

}

bool Units::init()
{
	if (!Layer::init()) { return false; }

	return true;
}

void Units::onEnterTransitionDidFinish() {

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	switch (_menuContext->getCurrentLevel()) {

	case 1:break;
	case 2:break;
	case 3:break;
	case 4:break;
	case 5:break;
	case 6:break;
	case 7:break;
	case 8:break;
	case 9:break;
	case 10:break;

	}
	

	_menuContext->setMaxPoints(1);

	_bg = CSLoader::createNode("unit/unit.csb");
	_bg->setName("bg");
	_bg->setAnchorPoint(Vec2(0.5, 0.5));
	_bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//_bg->setScale(0.5, 0.5);
	this->addChild(_bg);

	//_bgCopy = CSLoader::createNode("unit/unit.csb");

	Vector <Node*> children = _bg->getChildren();
	int size = children.size();
	for (auto item = children.rbegin(); item != children.rend(); ++item) {
		Node * monsterItem = *item;
		std::string str = monsterItem->getName().c_str();
		CCLOG("name : %s", str.c_str());
	}


	float delay = 0.5;
	outlet_1 = _bg->getChildByName("outlet_1")->getPosition();
	outlet_2 = _bg->getChildByName("outlet_2")->getPosition();

	_pizza = CSLoader::createNode("unit/pizza.csb");

	_pizza->setAnchorPoint(Vec2(0.5, 0.5));
	_pizza->setPosition(Vec2(visibleSize.width / 2 + origin.x, outlet_2.y - 550 + origin.y));
	//bg->setScale(0.5, 0.5);
	this->addChild(_pizza);


	addCalculator();


	//addCookiesToPizza(1, 10, 1, 10);

	
	auto handle = _bg->getChildByName("FileNode_3");
	handle->setContentSize(Size(200, 200));
	handle->setName("handle");
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(Units::onTouchBegan, this);
	listener->setSwallowTouches(false);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), handle);


	Sprite* calculatorButton = Sprite::createWithSpriteFrameName("unit/cal.png");
	calculatorButton->setName("calbutton");
	calculatorButton->setAnchorPoint(Vec2(0.5, 0.5));
	calculatorButton->setPosition(Vec2(500, 750));
	this->addChild(calculatorButton);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), calculatorButton);

	
	this->scheduleUpdate();

}

void Units::update(float delta) {
	
		if (_calculateFlag == 0 && _calculator->checkAnswer(13)) {
		
		CCLOG("correct answer");
		_calculateFlag = 1;

		auto ShowScore = CallFunc::create([=] {
			
			_menuContext->addPoints(1);
			_menuContext->showScore();

		});

	
		auto scoreSequenceOne = Sequence::create(DelayTime::create(0.5), ShowScore, NULL);
		this->runAction(scoreSequenceOne);
		
		}
	
		
}

Units::~Units(void)
{
	this->removeAllChildrenWithCleanup(true);
}


void Units::gameHelpLayer()
{


	Size visibleSize = Director::getInstance()->getVisibleSize();
	_help = HelpLayer::create(Rect(visibleSize.width / 2, visibleSize.height / 2, visibleSize.width / 2.8, visibleSize.height * 0.4), Rect(0, 0, 0, 0));
	std::vector <Point> points;
	float boxWidth = (visibleSize.width / 2.8) / 2;
	float boxHeight = (visibleSize.height * 0.4) / 2;
	points.push_back(Vec2(visibleSize.width / 2 - boxWidth / 1.25, visibleSize.height / 2 - boxHeight*0.6));
	points.push_back(Vec2(visibleSize.width / 2, visibleSize.height / 2 + boxHeight*0.7));
	points.push_back(Vec2(visibleSize.width / 2 + boxWidth / 1.25, visibleSize.height / 2 - boxHeight*0.6));
	points.push_back(Vec2(visibleSize.width / 2 - boxWidth / 2, visibleSize.height / 2 - boxHeight*0.1));
	points.push_back(Vec2(visibleSize.width / 2 + boxWidth / 2, visibleSize.height / 2 - boxHeight*0.1));
	_help->writing(points);
	this->addChild(_help);
	_help->setName("gameHelpLayer");
}


void Units::createOrder(int id) {
	
	static int delay = 0.5;
	float time = 0.5;

	std::ostringstream sstreamb;
	sstreamb << "pizzatoppings_" << id;
	std::string queryb = sstreamb.str();

	auto moveObjectToOutletOne = MoveTo::create(time, outlet_1);
	auto moveObjectToOutletTwo = MoveTo::create(time, outlet_2);
	
	auto moveObjectToOrderContainer = MoveTo::create(time, Vec2(_pizza->getPosition()) + _pizza->getChildByName(queryb)->getPosition());
	

	Sprite * newObject = (Sprite*)_bg->getChildByName(queryb);

	auto switchParentSequence = CallFunc::create([=] {
		
		//_bg->getChildByName(queryb)->removeFromParent();
		//removeChild(_bg->getChildByName(queryb));
		//_bg->reorderChild(_bg->getChildByName(queryb), 4);
		_bg->getChildByName(queryb)->setGlobalZOrder(1);
		//object->removeFromParent();

	});


	auto addCookieToPizzaSequence = CallFunc::create([=] {

		//_bg->getChildByName(queryb)->removeFromParent();
		//removeChild(_bg->getChildByName(queryb));
		//_bg->reorderChild(_bg->getChildByName(queryb), 4);
		//_bg->getChildByName(queryb)->setGlobalZOrder(4);
		//object->removeFromParent();
		//_pizza->getChildByName(queryb)->addChild(_bg->getChildByName(queryb));

	});


	auto orderSequence = CallFunc::create([=] {
		if (id == 10) {

			//addCookiesToPizza(1, 10, 1, 10);
		}

	});

	delay += 0.5;
	auto moveSequenceOne = Sequence::create(moveObjectToOutletOne, switchParentSequence,moveObjectToOutletTwo, moveObjectToOrderContainer,DelayTime::create(2), orderSequence,NULL);
	_bg->getChildByName(queryb)->runAction(moveSequenceOne);
	
	//std::chrono::seconds duration(3);
	//std::this_thread::sleep_for(duration); // Sleep for 1 seconds.
	
	//auto moveSequenceTwo = Sequence::create(moveObjectToOrderContainer, NULL);
	//newObject->runAction(moveSequenceTwo);

	//auto mainSequence = Sequence::create(sequenceOne, sequenceTwo,  NULL);
	//_bg->runAction(mainSequence);


}


void Units::addCookiesToPizza(int pizzaToppingStartId, int pizzaToppingEndId, int cookiesStartId, int cookiesEndId) {


	//std::ostringstream sstreamb;
	//sstreamb << "pizzatoppings_" << id;
	//std::string queryb = sstreamb.str();


	for (int i = cookiesStartId, j = pizzaToppingStartId; i <= cookiesEndId; i++, j++) {

		std::ostringstream cookie;
		cookie << "pizzatoppings_" << i;
		std::string cookieStr = cookie.str();

		std::ostringstream pizza;
		pizza << "pizzatoppings_" << j;
		std::string pizzaStr = pizza.str();

		Sprite * newObject = new Sprite();
		newObject = (Sprite*)_bg->getChildByName(cookieStr);
		removeChild(_bg->getChildByName(cookieStr));
		_bg->getChildByName(cookieStr)->removeFromParent();
		newObject->setPosition(_pizza->getChildByName(pizzaStr)->getPosition());
		_pizza->addChild(newObject);

	}

	//auto movePizza = MoveTo::create(1, _bg->getChildByName("roll_29")->getPosition() + Vec2(100, 0));
	//_bg->getChildByName("roll_29")->runAction(moveTrack);

	

	auto movePizza = MoveTo::create(1, _pizza->getPosition() - Vec2(800, 0));

	auto moveSequenceOne = Sequence::create(DelayTime::create(1), movePizza, NULL);
	
	_pizza->runAction(moveSequenceOne);

}




bool Units::onTouchBegan(Touch* touch, Event* event) {


	auto target = event->getCurrentTarget();
	Point locationInNode = Vec2(0,0);

	if (target->getName() == "handle") {
		locationInNode = target->getParent()->convertToNodeSpace(touch->getLocation());
	}

	if (target->getName() == "calbutton") {
		locationInNode = target->getParent()->convertToNodeSpace(touch->getLocation());
	}


	auto bb = target->getBoundingBox();

	if (bb.containsPoint(locationInNode)) {

		CCLOG("touched");
		if (target->getName() == "handle" && orderIteration<=1) {
			if (handleTriggered == 0) {

				createNthOrder();
				handleTriggered = 1;

			}
		}

		if (target->getName() == "calbutton") {

			_calculator->resetCalculator();

			if (_calculatorTouched == false) {
				_calculator->setVisible(true);
				_calculatorTouched = true;

			}
			else {

				_calculator->setVisible(false);
				_calculatorTouched = false;
			}
			
		}


		return true; // to indicate that we have consumed it.
	}
	return false; // to indicate that we have not consumed it.
}


void Units::addCalculator() {

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_calculator = new Calculator();
	_calculator->createCalculator(Vec2(500, 1150), Vec2(0.5, 0.5), 0.5, 0.5);
	this->addChild(_calculator,10);
	//_calculator->setGlobalZOrder(2);
	_calculator->setVisible(false);

}

void Units::hideUnwated(int level) {


	for (int i = 11 + level; i <= 20; i++) {

		std::ostringstream cookie;
		cookie << "pizzatoppings_" << i;
		std::string cookieStr = cookie.str();

		_bg->getChildByName(cookieStr)->setVisible(false);

	}

}


void Units::createNthOrder() {

	for (int i = _startCookieId; i <= _endCookieId; i++) {

		createOrder(i);

	}

	_startCookieId = 11;
	_endCookieId = _startCookieId + _menuContext->getCurrentLevel()-1;
}