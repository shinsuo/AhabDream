//
//  StartLayer.h
//  AhabDream
//
//  Created by shin on 5/5/15.
//
//

#ifndef __AhabDream__StartLayer__
#define __AhabDream__StartLayer__

#include "cocos2d.h"

USING_NS_CC;

class StartLayer : public cocos2d::CCLayer
{
public:
    StartLayer();
    ~StartLayer();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(StartLayer);
    
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
//    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
public:
    void readConfig();
    void loadWave();
    
private:
    bool m_bStart;
};

#endif /* defined(__AhabDream__StartLayer__) */
