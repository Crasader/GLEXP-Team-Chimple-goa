#include "HippoScene.h"
#include "HippoGameScene.h"


USING_NS_CC;

Scene* Hippo::createScene() {
	auto layer = Hippo::create();
	auto scene = GameScene::createWithChild(layer, "hippo");
	layer->_menuContext = scene->getMenuContext();
	return scene;
}

Node* Hippo::loadNode() {
//	this->addChild(LayerGradient::create(Color4B(255, 219, 161, 255), Color4B(255, 255, 255, 255)), 0);
//	auto keyBoardLayer =  Layer::create();
//	auto test1 = (Node *)LayerColor::create(Color4B(255, 255, 255, 200.0));
//	test1->setContentSize(Size(Director::getInstance()->getVisibleSize().width, 600));
//	keyBoardLayer->addChild(test1);
//	this->addChild(keyBoardLayer,1);
	auto spritecache1 = SpriteFrameCache::getInstance();
	spritecache1->addSpriteFramesWithFile("hippo/hippo.plist");
	auto node = Node::create();
//	auto node = CSLoader::createNode("hippo/hippo.csb");
	return node;
}


std::string Hippo::getGridBackground() {
	return "hippo/button.png";
}

void Hippo::createChoice()
{
	_choice = Node::create();
//	_choice->setPosition(Vec2(1280, 900));
	addChild(_choice);
	for (int i = 0; i < _numGraphemes; i++) {
		auto choiceNode = Sprite::createWithSpriteFrameName("hippo/button.png");
		//auto dsg = HippoGame::stringPosition.at(i);
		//choiceNode->setAnchorPoint(Vec2(0, 1));
		//choiceNode->setPosition(Vec2(i * 200, 0));//HippoGame::stringPosition.at(i)
		float x = _gapNodes1.at(i)->getPositionX() - 500;
		float y = _gapNodes1.at(i)->getPositionY();
		choiceNode->setPosition(x, y);
	//	choiceNode->setPosition(_stringPositionX1.at(i), _stringPositionY1.at(i));
		addChoice(choiceNode);
	}
}

Hippo* Hippo::create() {
	Hippo* hippo = new (std::nothrow) Hippo();
	if (hippo && hippo->init())
	{
		hippo->autorelease();
		return hippo;
	}
	CC_SAFE_DELETE(hippo);
	return nullptr;
}