//
//  GameLayer.cpp
//  ReacheeE
//
//  Created by macbook_016 on 2013/09/05.
//
//

#include "GameLayer.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

CCScene * GameLayer::scene(){
    CCScene * scene = CCScene::create();
    GameLayer *layer = GameLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameLayer::init(){
    if ( !CCLayer::init() ) {
        return false;
    }
    _score = 0;
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    _mario = CCSprite::create("1.png");
    _mario->setAnchorPoint(ccp(0.5, 0));
    _mario->setPosition(ccp(300, 200));
    this->addChild(_mario);
    
    _tree = CCSprite::create("line.png");
    _tree->setAnchorPoint(ccp(0, 1));
    _tree->setPosition(ccp(500, 200));
    this->addChild(_tree);
    CCLOG("%f", _tree->getPositionX());
    
    _tap = CCSprite::create("Icon-72.png");
    _tap->setAnchorPoint(ccp(0.5 , 0));
    _tap->setPosition(ccp(size.width / 2, 0));
    this->addChild(_tap);
    
    _line = CCSprite::create("line03.png");
    _line->setScaleY(0);
    _line->setAnchorPoint(CCPointZero);
    _line->setPosition(ccp(304, 200));
    this->addChild(_line, 1000);
    this->setTouchEnabled(true);
    return true;
}

void GameLayer::menuCloseCallback(CCObject * pSender) {
    CCScene *pScene = HelloWorld::scene();
    
    // run
    CCDirector::sharedDirector()->runWithScene(pScene);
}

void GameLayer::run() {
    CCAnimation * animation = CCAnimation::create();
    for (int i = 2; i < 9; i++) {
        char szImageFileName[10] = {0};
        sprintf(szImageFileName, "%d.png", i);
        animation->addSpriteFrameWithFileName(szImageFileName);
    }
    animation->setDelayPerUnit(0.1);
    animation->setRestoreOriginalFrame(true);
    animation->setLoops(5);
    CCAnimate *animate = CCAnimate::create(animation);
    _mario->runAction(animate);
}

void GameLayer::updateBrige(float dt) {
    _dt++;
    _line->setScaleY(_dt);

}

void GameLayer::ccTouchesBegan(CCSet *pTouches, CCEvent * event) {
    CCPoint location =
    this->getParent()->convertTouchToNodeSpace((CCTouch*)( pTouches->anyObject()));
    if (_tap->boundingBox().containsPoint(location)) {
        _dt = 1;
        this->schedule( schedule_selector(GameLayer::updateBrige), 0.1 );
    }
}

void GameLayer::ccTouchesMoved(CCSet *pTouches, CCEvent * event) {
}

void GameLayer::ccTouchesEnded(CCSet *pTouches, CCEvent * event) {
    CCPoint marioBackPoint = _mario->getPosition();
    CCPoint treeBackPoint = ccp(_mario->getPositionX() - _tree->getContentSize().width, 200);
    CCPoint lineBackPoint = ccp(_mario->getPositionX() - _line->getContentSize().width, 200);
    
    CCPoint location =
    this->getParent()->convertTouchToNodeSpace((CCTouch*)( pTouches->anyObject()));
    if (_tap->boundingBox().containsPoint(location)) {
        this->unschedule( schedule_selector(GameLayer::updateBrige));
        CCRotateBy * rotate = CCRotateBy::create(0.1f, 90);
        _line->runAction(rotate);
        this->run();
        float withLine = _line->getContentSize().height * _dt;
        CCPoint taget = ccp(_mario->getPositionX() + withLine + 10, 200);
        CCPoint finalTaget = ccp(_tree->getPositionX() + _tree->getContentSize().width, 200);
        CCMoveTo *move = CCMoveTo::create(3, taget);
        CCRect  rect = _tree->boundingBox();
        if (rect.containsPoint(taget)) {
            CCMoveTo *finalMove = CCMoveTo::create(4, finalTaget);
            CCDelayTime * delay = CCDelayTime::create(4);
            CCMoveTo *marioBack = CCMoveTo::create(1, marioBackPoint);
            CCSequence *sq = CCSequence::create(finalMove, marioBack, NULL);
            _mario->runAction(sq);
            
            CCMoveTo *treeBack = CCMoveTo::create(1, treeBackPoint);
            CCSequence *sq2 = CCSequence::create(delay, treeBack, NULL);
            _tree->runAction(sq2);
            
            CCMoveTo *lineBack = CCMoveTo::create(1, lineBackPoint);
            CCSequence *sq3 = CCSequence::create(delay, lineBack, NULL);
            _line->runAction(sq3);

            _score++;
        } else {
            CCPoint tagetdow = ccp(_mario->getPositionX() + withLine + 10, 0);
            CCMoveTo *movedown = CCMoveTo::create(3, tagetdow);
            CCSequence *sq = CCSequence::create(move, movedown, NULL);
            _mario->runAction(sq);
            CCDelayTime * delay = CCDelayTime::create(3);
            CCSequence * sq2 = CCSequence::create(delay,rotate, NULL);
            _line->runAction(sq2);
        }
    }
}