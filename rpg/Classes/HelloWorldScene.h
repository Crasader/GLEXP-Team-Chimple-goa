#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#include "cocos2d.h"
#include "editor-support/cocostudio/ActionTimeline/CCSkeletonNode.h"
#include "RPGConfig.h"
#include "SkeletonCharacter.h"
#include "ExternalSkeletonCharacter.h"
#include "StateMachine.h"
#include "Sqlite3Helper.hpp"
#include "MessageSender.hpp"
#include "MessageReceiver.hpp"

class GestureLayer;
class MessageContent;

typedef std::vector<ExternalSkeletonCharacter*> external_skeletons;    // or whatever you


#define DIALOG_FILE "dialogFile"
#define PHYSICS_FILE "physicsFile"
#define MAIN_CHARACTER_FILE "mainCharacterFile"


class HelloWorld : public cocos2d::Layer
{
private:
    //member variables
    
    cocos2d::Point currentTouchPoint;
    
    GestureLayer* gesture_layer_;
    
    StateMachine* stateMachine;
    
    Sqlite3Helper* sqlite3Helper;
    
    MessageSender* messageSender;
    
    MessageReceiver* messageReceiver;
    
    SkeletonCharacter* skeletonCharacter;
    
    bool _isFingerTouchedToScreen;
    
    float _xVelocity = 0;
    
    virtual bool checkTouchWithinBoundsOfCharacter(cocos2d::Point point, cocostudio::timeline::SkeletonNode* characterNode);
    
    virtual bool checkTouchVerticallyUpOnBoundsOfCharacter(cocos2d::Point point, cocostudio::timeline::SkeletonNode* characterNode);
    
    virtual bool checkTouchLeftOfCharacter(cocos2d::Point point, cocostudio::timeline::SkeletonNode* characterNode);
    
    virtual bool checkTouchRightOfCharacter(cocos2d::Point point, cocostudio::timeline::SkeletonNode* characterNode);
    
    virtual bool checkHoldWithinWalkLimitOfCharacter(cocos2d::Point point, cocostudio::timeline::SkeletonNode* characterNode);
    
    virtual bool checkHoldWithinSittingLimitOfCharacter(cocos2d::Point point, cocostudio::timeline::SkeletonNode* characterNode);
    
    virtual void applyImpulseOnSkeletonToJumpOnHoldOrDrag(cocos2d::Point position);
    
    virtual void applyImpulseOnSkeletonToJumpOnTap(cocos2d::Point position);
    
    virtual void applyImpulseOnSkeletonToJump(cocos2d::Point position, float angle, float velocity, float timeToStart);
    
    virtual void walkCharacterOnLeftOrRightDirection(cocos2d::Point position);
    
    virtual void runCharacterOnLeftOrRightDirection(cocos2d::Point position);
    
    virtual void HoldOrDragBehaviour(cocos2d::Point position);
    
    virtual void scheduleContinuousRotationCall(float timeToStart);
    
    virtual void moveBackGroundLayerInParallex();
    
    virtual void parseScene(cocos2d::Node *rootNode);
    
    virtual void addExternalCharacters(cocos2d::Node *rootNode);
    
    virtual void processMessage(std::vector<MessageContent*>*messages);
    
    cocos2d::Size sceneSize;
    
    //references to all external Skeletons
    
    external_skeletons externalSkeletons;
    
    
    //reference to Layers
    cocos2d::Node* mainLayer;
    cocos2d::Node* backgroundLayer;
    cocos2d::Node* foregroundLayer;

    //category bit mask for main skeleton
    int mainCharacterCategoryBitMask;
    
    std::string baseDir;
    
public:
    static cocos2d::Scene* createScene();
    
    HelloWorld();
    ~HelloWorld();
    
    virtual bool init();
    
    void createRPGGame();
    
    void loadGameScene();
    
    void enablePhysicsBoundaries(Node* rootNode);
    
    cocostudio::timeline::SkeletonNode* createMainGameCharacter();
    
    virtual void addMainCharacterToScene(const std::string& filename);
        
    void initGestureLayer();
    
    static void initPhysics(cocos2d::Scene* scene);
    
    void startJumpUpEndingAnimation(float dt);
    
    void startContinuousRoationAnimation(float dt);
    
    void update(float dt);
    
    void initializeStateMachine();
    
    //bind Gesture
    void OnGestureReceived(Ref* sender);
    
    //Gesture Handler
    void HandleTap(cocos2d::Point position);
    void HandleHold(cocos2d::Point position);
    void HandleSwipeUp(cocos2d::Point position);
    void HandleSwipeDown(cocos2d::Point position);
    void HandleSwipeLeft(cocos2d::Point position);
    void HandleSwipeRight(cocos2d::Point position);
    void HandleTouchedEnded(cocos2d::Point position);
    bool isTapOnSpeakableObject(cocos2d::Point position);
    
    void HandleJumpWithAnimation();
    void HandlePostJumpUpAnimation();
    
    
    void HandlePostJumpUpWithRotationAnimation();
    
    void scheduleJumpUpEndCall(float time);
    
    void flipSkeletonDirection(cocos2d::Point point, cocostudio::timeline::SkeletonNode* characterNode);
    
    void HandleJumpWithContinueousRotation();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    //set scene attributes
    virtual void setSceneSize(const cocos2d::Size& size);
    
    virtual cocos2d::Size getSceneSize();
        
    virtual void registerPhysicsEventContactLister();
    
    virtual void loadSqlite3FileForScene();
    
    virtual void registerMessageSenderAndReceiver();
    
    virtual bool handlePhysicsContactEventForMainCharacter(cocos2d::PhysicsContact &contact, cocos2d::Node* nodeA, cocos2d::Node* nodeB);
    
    virtual bool handlePhysicsContactEventForOtherSkeletonCharacter(cocos2d::PhysicsContact &contact, cocos2d::Node* nodeA, cocos2d::Node* nodeB);
    
    
    CC_SYNTHESIZE(std::string, _baseDir, BaseDir);
    
    CC_SYNTHESIZE(std::string, dialogFile, DialogFile);
    
    CC_SYNTHESIZE(std::string, physicsFile, PhysicsFile);
    
    CC_SYNTHESIZE(std::string, mainCharacterFile, MainCharacterFile);
    
    CC_SYNTHESIZE(bool, isSpeechBubbleAlreadyVisible, SpeechBubbleAlreadyVisible);
};

#endif // __HELLOWORLD_SCENE_H__
