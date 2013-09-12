//
//  GameLayer.h
//  ReacheeE
//
//  Created by macbook_016 on 2013/09/05.
//
//

#ifndef __ReacheeE__GameLayer__
#define __ReacheeE__GameLayer__

#include <iostream>
#include "cocos2d.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

class GameLayer : public CCLayer {
private:
    CCSprite *_mario;
    CCSprite *_line;
    CCSprite *_tap;
    CCSprite *_tree;
    
    float _dt;
    
    int _score;
public:
    virtual bool init();
    static CCScene *scene();
    void menuCloseCallback(CCObject * pSender);
    void run();
    void updateBrige(float dt);
    virtual void ccTouchesBegan(CCSet* pTouches, CCEvent* event);
    virtual void ccTouchesMoved(CCSet* pTouches, CCEvent* event);
    virtual void ccTouchesEnded(CCSet* pTouches, CCEvent* event);
    CREATE_FUNC(GameLayer);
};

#endif /* defined(__ReacheeE__GameLayer__) */
