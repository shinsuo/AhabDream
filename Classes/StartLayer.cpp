//
//  StartLayer.cpp
//  AhabDream
//
//  Created by shin on 5/5/15.
//
//

#include "StartLayer.h"

USING_NS_CC;

StartLayer::StartLayer()
{

}

StartLayer::~StartLayer()
{
    
}

bool StartLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCArray* arr = CCArray::create();
    
    CCLabelTTF* title_label = CCLabelTTF::create("Ahab's Dream", "", 48);
    CCMenuItemLabel* title = CCMenuItemLabel::create(title_label);//, this, menu_selector(StartLayer::menuCloseCallback));
    arr->addObject(title);
    title->setPosition(ccp(visibleSize.width/2,visibleSize.height/2+100));
    
    
    CCLabelTTF* start_label = CCLabelTTF::create("Start", "", 48);
    CCMenuItemLabel* start = CCMenuItemLabel::create(start_label, this, menu_selector(StartLayer::menuCloseCallback));
    arr->addObject(start);
    start->setPosition(ccp(visibleSize.width/2,visibleSize.height/2-100));
    
    CCMenu* pMenu = CCMenu::createWithArray(arr);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);
    
    return true;
}

void StartLayer::menuCloseCallback(CCObject* pSender)
{

}