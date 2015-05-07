//
//  CompassLayer.h
//  AhabDream
//
//  Created by shin on 5/7/15.
//
//

#ifndef __AhabDream__CompassLayer__
#define __AhabDream__CompassLayer__

#include "cocos2d.h"

USING_NS_CC;

class CompassLayer : public cocos2d::CCLayer
{
public:
    CompassLayer();
    ~CompassLayer();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // implement the "static node()" method manually
    CREATE_FUNC(CompassLayer);
    
    
    virtual void onEnter();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
};

#endif /* defined(__AhabDream__CompassLayer__) */
