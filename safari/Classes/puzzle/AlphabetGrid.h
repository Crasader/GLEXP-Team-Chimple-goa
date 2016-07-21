//
//  AlphabetGrid.h
//  rpg
//
//  Created by Srikanth Talapadi on 24/06/16.
//
//

#ifndef AlphabetGrid_h
#define AlphabetGrid_h

#include "cocos2d.h"
#include "Alphabet.h"

class AlphabetGrid : public cocos2d::Layer
{
public:
    static AlphabetGrid *create(GLfloat width, GLfloat height, int numRows, int numCols);
    void setCharacters(std::vector<std::vector<char>> charArray);
    std::vector<Alphabet *> getAlphabetsWhichMatch(char a);
    int getCountOfAlphabetsWhichMatch(char a);
    void enableTouch(bool value);
    void resize(GLfloat width, GLfloat height, int numRows, int numCols);    

CC_CONSTRUCTOR_ACCESS:
    AlphabetGrid();
    virtual ~AlphabetGrid();
    bool initWithSize(GLfloat width, GLfloat height, int numRows, int numCols);

protected:
    int _numRows;
    int _numCols;
    GLfloat _width;
    GLfloat _height;
    Node *_alphabetLayer;
    Node *_labelLayer;
    std::vector<std::vector<Alphabet *> > _alphabetMatrix;
    cocos2d::DrawNode *_overlay;
};

#endif /* AlphabetGrid_h */
