//
//  CompassLayer.cpp
//  AhabDream
//
//  Created by shin on 5/7/15.
//
//

#include "CompassLayer.h"

CompassLayer::CompassLayer()
{

}

CompassLayer::~CompassLayer()
{
    
}

bool CompassLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    return true;
}

void CompassLayer::onEnter()
{
    CCLayer::onEnter();
    
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,kCCMenuHandlerPriority*2,true);
}

bool CompassLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCLog("compasslayer:touchbegan");
    return true;
}
