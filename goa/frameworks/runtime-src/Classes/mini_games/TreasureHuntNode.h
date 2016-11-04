
#ifndef __TREASUREHUNT_NODE_H__
#define __TREASUREHUNT_NODE_H__

#include "cocos2d.h"
#include "../menu/MenuContext.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "../LipiTKNode.h"

class TreasureHuntNode : public LipiTKNode
{
public:
	TreasureHuntNode();
	~TreasureHuntNode();
	cocos2d::Sprite* createDrawingBoard();
	static TreasureHuntNode *create(int width, int height, cocos2d::Point position);

	void draw(cocos2d::DrawNode* paintingNode, cocos2d::Point fromPoint, cocos2d::Point currentPoint);
	virtual void broadCastRecognizedChars(std::vector<std::string> results) override;
	std::vector<std::string> getPosibileCharacter();

protected:
	MenuContext * menu;
	std::vector<std::string> _result;

};

#endif  // __TREASUREHUNT_NODE_H__