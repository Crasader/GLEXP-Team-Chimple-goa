//
//  MessageReceiver.cpp
//  rpg
//
//  Created by Shyamal  Upadhyaya on 09/07/16.
//
//


#include "MessageReceiver.hpp"
#include "cocos2d.h"
#include "RPGConfig.h"
#include "MessageContent.hpp"


USING_NS_CC;

MessageReceiver::MessageReceiver() {
}


MessageReceiver::~MessageReceiver() {
}

MessageReceiver* MessageReceiver::getInstance() {
    auto messageReceiver = new MessageReceiver();
    if (messageReceiver && messageReceiver->initialize()) {
        messageReceiver->autorelease();
        return messageReceiver;
    }
    CC_SAFE_DELETE(messageReceiver);
    return nullptr;
}


bool MessageReceiver::initialize() {
    
    auto receiveMessageEvent = [=] (EventCustom * event) {
        EVENT_DISPATCHER->dispatchCustomEvent(RPGConfig::PROCESS_CUSTOM_MESSAGE_AND_CREATE_UI_NOTIFICATION, event->getUserData());
    };
    
    RECEIVE_MESSAGE_FOR_TAP_ON_SPEAKABLE(this, RPGConfig::RECEIVE_CUSTOM_MESSAGE_NOTIFICATION, receiveMessageEvent);
    
    return true;
}
