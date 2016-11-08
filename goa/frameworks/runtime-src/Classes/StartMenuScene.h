//
//  StartMenuScene.h
//  safari
//
//  Created by Srikanth Talapadi on 14/07/16.
//
//

#ifndef StartMenuScene_h
#define StartMenuScene_h

#include "cocos2d.h"

static const std::string DUEL_SCENE = "book";
static const std::string ALPHAMON_COMBAT = "book";
static const std::string CAMP = "camp";
static const std::string FARM_HOUSE = "farmhouse";
static const std::string MINING_BG = "miningbg";
static const std::string PATCH_THE_WALL = "Patch The Wall";
static const std::string CROSS_THE_BRIDGE = "Cross The Bridge";
static const std::string SMASH_THE_ROCK = "Smash The Rock";
static const std::string CANNON_BALL = "Cannon Ball";
static const std::string ENDLESS_RUNNER = "EndlessRunner";
static const std::string KUNG_FU_ALPHA = "Kung Fu Alpha";
static const std::string ALPHAMON_FEED = "Alphamon Feed";
static const std::string BAJA = "baja";
static const std::string CHAIN = "chain";
static const std::string WEMBLEY = "wembley";
static const std::string JAZZ = "jazz";
static const std::string JASMINE = "jasmine";
static const std::string CAT = "cat";
static const std::string TRAIN = "train";
static const std::string POP = "pop";
static const std::string ALPHAMOLE = "alphamole";
static const std::string JUMP_ON_WORDS = "JumpOnWords";
static const std::string STORY_TELLING = "book";
static const std::string DECOMON = "decomone";
static const std::string SORT_IT = "sortit";
static const std::string WORD_BOARD = "wordBoard";
static const std::string PEG = "peg";
static const std::string BUBBLE = "bubble";
static const std::string PINATA = "shoot";
static const std::string STACK = "stack";
static const std::string TALK = "talk";
static const std::string BINGO = "bingo";
static const std::string DROP = "drop";
static const std::string OWL = "owl"; 
static const std::string MEMORY = "memory"; 
static const std::string BALLONHERO = "balloon";
static const std::string DASH = "dash";
static const std::string CIRCLE = "circle";
static const std::string ORDER = "order";
static const std::string PILLAR = "pillar";
static const std::string CARDRAW = "cardraw"; 
static const std::string BLASTLETTER = "blastletter";
static const std::string DOOR = "Door";
static const std::string TREASUREHUNT = "TreasureHunt";


class StartMenu {
public:
    static void startScene(std::string gameName, std::string firstParam = "", std::string secondParam = "", std::string thirdParam = "");
    static const std::vector<std::string> getGameNames();
    static const std::vector<std::string> multiPlayerGameNames();
    
CC_CONSTRUCTOR_ACCESS:
    StartMenu();
    virtual ~StartMenu();
    static std::string parseGameConfig(std::string gameConfigStr);
};

#endif /* StartMenuScene_h */
