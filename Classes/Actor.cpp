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

//----------------------------------------------------------------

Ship::Ship()
{

}

Ship::~Ship()
{

}

Ship* Ship::create(const char* png)
{
    Ship* p = new Ship();
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

bool Ship::init()
{
    if (!Actor::init())
    {
        return false;
    }
    
    
    return true;
}

//----------------------------------------------------------------

Whale::Whale():m_pAim1(0)
,m_pAim2(0)
{
    
}

Whale::~Whale()
{
    
}

Whale* Whale::create(const char* png)
{
    Whale* p = new Whale();
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

bool Whale::init()
{
    if (!Actor::init())
    {
        return false;
    }
    
    
    m_pAim1 = GameUtil::createSprite("aim1");
    m_pAim2 = GameUtil::createSprite("aim2");
    addChild(m_pAim1);
    addChild(m_pAim2);
    
    scheduleUpdate();
    
    return true;
}

void Whale::moveAimY(float y)
{
    m_pAim2->setPositionY(m_pAim2->getPositionY()+y);
}

void Whale::update(float dt)
{
    
}

