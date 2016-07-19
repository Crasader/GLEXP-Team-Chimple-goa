//
//  AlphamonSprite.cpp
//  safari
//
//  Created by Shyamal  Upadhyaya on 19/07/16.
//
//

#include "AlphamonSprite.h"
#include "SkeletonCharacter.h"
#include "Alphamon.h"

USING_NS_CC;

AlphamonSprite::AlphamonSprite():
shouldSendShowTouchSign(false),
showTouchSignNotificationSent(false),
vicinityToMainCharacter(false),
interAct("")
{    
    this->mainSkeleton = NULL;
}


AlphamonSprite::~AlphamonSprite() {
    
}


AlphamonSprite* AlphamonSprite::create(cocos2d::Node* node, std::unordered_map<std::string, std::string> attributes, char alphabet)
{
    auto alphaMonSprite = new AlphamonSprite();
    if (alphaMonSprite && alphaMonSprite->initialize(node, attributes, alphabet)) {
        alphaMonSprite->autorelease();
        return alphaMonSprite;
    }
    CC_SAFE_DELETE(alphaMonSprite);
    return nullptr;
}


bool AlphamonSprite::initialize(cocos2d::Node* node, std::unordered_map<std::string,std::string> attributes, char alphabet) {
    this->alphabet = alphabet;
    Alphamon* alphamon = Alphamon::createWithAlphabet(alphabet);
    alphamon->setName(node->getName());
    this->setAttributes(attributes);
    this->addChild(alphamon);
    this->setName(node->getName());
    alphamon->setPosition(node->getPosition());
    
    
    this->getEventDispatcher()->addCustomEventListener("alphamon_pressed", CC_CALLBACK_1(AlphamonSprite::onAlphabetSelected, this));

    
    auto checkVicinityWithMainCharacter = [=] (EventCustom * event) {
        this->mainSkeleton = static_cast<SkeletonCharacter*>(event->getUserData());
        this->checkVicinityToMainSkeleton(this->mainSkeleton);
        
        if(this->getVicinityToMainCharacter() && !this->getShowTouchSignNotificationSent()) {
            this->setShowTouchSignNotificationSent(true);
            EVENT_DISPATCHER->dispatchCustomEvent(RPGConfig::SEND_SHOW_TOUCH_POINT_SIGN_NOTIFICATION, static_cast<void*>(this->getAlphaMon()));
            
        }
    };
    
    ADD_VICINITY_NOTIFICATION(this, RPGConfig::MAIN_CHARACTER_VICINITY_CHECK_NOTIFICATION, checkVicinityWithMainCharacter);
    
    this->scheduleUpdate();
    
    return true;
    
}

Alphamon* AlphamonSprite::getAlphaMon() {
    assert(!this->getChildren().empty());
    assert(this->getChildren().size() == 1);
    
    Alphamon* alphaMone = dynamic_cast<Alphamon *>(this->getChildren().at(0));
    return alphaMone;
}

void AlphamonSprite::setAttributes(std::unordered_map<std::string, std::string> attributes) {
    this->attributes = attributes;
    //process it
    
    std::unordered_map<std::string,std::string>::const_iterator it = this->attributes.find("canInteract");
    if ( it != this->attributes.end() ) {
        this->setInterAct(it->second);
    }
}

std::unordered_map<std::string, std::string> AlphamonSprite::getAttributes() {
    return this->attributes;
}

void AlphamonSprite::update(float dt) {
    if(!this->vicinityToMainCharacter && this->mainSkeleton != NULL) {
        
        EVENT_DISPATCHER->dispatchCustomEvent( RPGConfig::MAIN_CHARACTER_VICINITY_CHECK_NOTIFICATION, this->mainSkeleton);
    }
}

bool AlphamonSprite::checkVicinityToMainSkeleton(SkeletonCharacter* skeletonCharacter) {
    bool isNear = false;
    Vec2 mainSkeletonPositionFromBottom = Point(skeletonCharacter->getSkeletonNode()->getPosition().x, skeletonCharacter->getSkeletonNode()->getPosition().y);
    Vec2 mainSkeletonPositionFromTop = Point(skeletonCharacter->getSkeletonNode()->getPosition().x, skeletonCharacter->getSkeletonNode()->getPosition().y + skeletonCharacter->getSkeletonNode()->getBoundingBox().size.height);
    
    float distanceFromTop= mainSkeletonPositionFromTop.getDistance(this->getAlphaMon()->getPosition());
    float distanceFromBottom = mainSkeletonPositionFromBottom.getDistance(this->getAlphaMon()->getPosition());
    
    if((distanceFromTop >= -OBJECT_TAP_BOUNDING_BOX_WIDTH && distanceFromTop <= OBJECT_TAP_BOUNDING_BOX_WIDTH) || (distanceFromBottom >= -OBJECT_TAP_BOUNDING_BOX_WIDTH && distanceFromBottom <= OBJECT_TAP_BOUNDING_BOX_WIDTH)) {
        this->setVicinityToMainCharacter(true);
        isNear = true;
        
    } else {
        this->setVicinityToMainCharacter(false);
        isNear = false;
    }
    
    
    if((distanceFromTop >= -OBJECT_NEAR_BY_BOUNDING_BOX_WIDTH && distanceFromTop <= OBJECT_NEAR_BY_BOUNDING_BOX_WIDTH) || (distanceFromBottom >= -OBJECT_NEAR_BY_BOUNDING_BOX_WIDTH && distanceFromBottom <= OBJECT_NEAR_BY_BOUNDING_BOX_WIDTH)) {
        this->setShouldSendShowTouchSign(true);
        
    } else {
        this->setShouldSendShowTouchSign(false);
        this->setShowTouchSignNotificationSent(false);
    }
    
    
    return isNear;
    
}

SkeletonCharacter* AlphamonSprite::getMainSkeleton() {
    return this->mainSkeleton;
}

void AlphamonSprite::onAlphabetSelected(cocos2d::EventCustom *event) {
    std::string s(this->getAlphaMon()->getName());
    char* buf = static_cast<char*>(event->getUserData());
    if(alphabet == buf[0]) {
        EVENT_DISPATCHER->dispatchCustomEvent(RPGConfig::SPEECH_MESSAGE_ON_TAP_NOTIFICATION, static_cast<void*>(&s));
    }
}