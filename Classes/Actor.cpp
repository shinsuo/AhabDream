//
//  Actor.cpp
//  AhabDream
//
//  Created by shin on 5/7/15.
//
//

#include "Actor.h"
#include "GameUtil.h"
#include "BloodGroove.h"
#include "AppMacros.h"

Actor::Actor():m_pSp(0)
,m_strPng("")
,m_pWeapon(0)
,m_strWeapon("")
,m_pBlood(0)
,m_pPower(0)
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
    
    m_pWeapon = GameUtil::createSprite(m_strWeapon.c_str());
    addChild(m_pWeapon);
//    m_pWeapon->setVisible(false);

    
    return true;
}

const CCSize& Actor::getContentSize() const
{
    return m_pSp->getContentSize();
}

void Actor::fire()
{
    
}

void Actor::showUI()
{
    
}

void Actor::addBlood(int blood)
{
    m_pBlood->setProgress(20);
}

void Actor::addPower(int power)
{
    m_pPower->setProgress(50);
}

//----------------------------------------------------------------

Ship::Ship()
{
    m_strWeapon = "weapon1"; 
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
    
    
    m_pBlood = BloodGroove::create("blood", "blood_container");
    GameUtil::getMainScene()->addChild(m_pBlood, kUI);
    
    m_pPower = BloodGroove::create("power", "power_container");
    GameUtil::getMainScene()->addChild(m_pPower, kUI);
    
    m_pBlood->setPosition(ccp(60, GameUtil::getWinHeight()*0.95));
    m_pPower->setPosition(ccp(60, GameUtil::getWinHeight()*0.85));
    
    
    return true;
}

//----------------------------------------------------------------

Whale::Whale():m_pAim1(0)
,m_pAim2(0)
{
    m_strWeapon = "weapon2";
    m_fRotate = 20;
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
    
    m_pSp->setRotation(m_fRotate);
    
    
    m_pAim1 = GameUtil::createSprite("aim1");
    m_pAim2 = GameUtil::createSprite("aim2");
    addChild(m_pAim1);
    addChild(m_pAim2);
    
    
    
    m_pBlood = BloodGroove::create("blood", "blood_container", 1);
    GameUtil::getMainScene()->addChild(m_pBlood, kUI);
    
    m_pPower = BloodGroove::create("power", "power_container", 1);
    GameUtil::getMainScene()->addChild(m_pPower, kUI);
    
    m_pBlood->setPosition(ccp(GameUtil::getWinWidth()-60, GameUtil::getWinHeight()*0.95));
    m_pPower->setPosition(ccp(GameUtil::getWinWidth()-60, GameUtil::getWinHeight()*0.85));
    
    scheduleUpdate();
    
    return true;
}

void Whale::moveAimY(float y)
{
    float new_y = m_pAim2->getPositionY()+y;
    m_pAim2->setPositionY(new_y);
    
    moveXByY(new_y);
}

float Whale::moveXByY(float y)
{
    
    float new_x = -y/tan(m_fRotate);
    
    m_pAim2->setPositionX(new_x);
    
    return new_x;
}

void Whale::update(float dt)
{
    
}

