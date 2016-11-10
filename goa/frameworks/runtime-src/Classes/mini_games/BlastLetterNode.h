
#ifndef __BLASTLETTERNODE_NODE_H__
#define __BLASTLETTERNODE_NODE_H__

#include "cocos2d.h"
#include "../menu/MenuContext.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "../LipiTKNode.h"

class BlastLetterNode : public LipiTKNode
{
public:
	BlastLetterNode();
	~BlastLetterNode();
	cocos2d::Sprite* createDrawingBoard();
	static BlastLetterNode *create(int width, int height, cocos2d::Point position);
	virtual void draw(cocos2d::DrawNode* paintingNode, cocos2d::Point fromPoint, cocos2d::Point currentPoint);
	virtual void broadCastRecognizedChars(std::vector<std::string> results) override;
	virtual ui::Button* createButton(const std::string normalImage, const std::string selectedImage, const std::string disableImage, Vec2 position) override;
	virtual void clearDrawing(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType eEventType);
	std::vector<std::string> getPosibileCharacter();
	void drawAllowance(bool permission);

protected:
	MenuContext * menu;
	std::vector<std::string> _result;
	bool _drawAllowance = true;
};

#endif  // __BLASTLETTERNODE_NODE_H__