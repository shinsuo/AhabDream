//
//  Actor.cpp
//  AhabDream
//
//  Created by shin on 5/7/15.
//
//

#include "Actor.h"
#include "GameUtil.h"

Actor::Actor():m_pSp(0)
,m_strPng("")
{

}

Actor::~Actor()
{
    
}

Actor* Actor::create(const char* png)
{
    Actor* p = new Actor();
    p->setStrPng(png);
    if (p&&p->init())
    {
        p->autorelease();
        return p;
    }
    else
    {
        delete p;
        p = NULL;
        return NULL;
    }
    
}

bool Actor::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    
    setAnchorPoint(ccp(0.5, 0.5));
    
    m_pSp = GameUtil::createSprite(m_strPng.c_str());
    addChild(m_pSp);
    
    return true;
}

const CCSize& Actor::getContentSize() const
{
    return m_pSp->getContentSize();
}