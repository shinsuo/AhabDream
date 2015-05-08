//
//  BloodGroove.cpp
//  AhabDream
//
//  Created by shin on 5/7/15.
//
//

#include "BloodGroove.h"
#include "GameUtil.h"

static float container_border_percent = 0.02;

BloodGroove::BloodGroove():m_fBlood_len(0.0)
,m_fContainer_len(0.0)
,m_iLeftRight(0)
,m_fCurPercent(100)
,m_fNextPercent(100)
,m_fScaleFull(1.0)
{

}

BloodGroove::~BloodGroove()
{

}

BloodGroove* BloodGroove::create(const char* blood_png, const char* blood_container_png, int leftorright)
{
    BloodGroove* p = new BloodGroove();
    p->setBloodContainerPng(blood_container_png);
    p->setBloodPng(blood_png);
    p->setLeftRight(leftorright);
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

bool BloodGroove::init()
{
    if (CCNode::init())
    {
     
        m_pBlood = GameUtil::createSprite(m_strBloodPng.c_str());
        m_pBlood->setAnchorPoint(ccp(m_iLeftRight, 0.5));
        m_pBloodContainer = GameUtil::createSprite(m_strBloodContainerPng.c_str());
        m_pBloodContainer->setAnchorPoint(ccp(m_iLeftRight, 0.5));
        
        
        m_pBloodContainer->addChild(m_pBlood);
        m_pBlood->setPositionY(m_pBloodContainer->getContentSize().height/2);
        int temp = 1;
        if (m_iLeftRight == 1)
        {
            temp = -1;
        }
        m_pBlood->setPositionX(m_iLeftRight*m_pBloodContainer->getContentSize().width+temp*m_pBloodContainer->getContentSize().width*container_border_percent);
        
        addChild(m_pBloodContainer);
        
        
        m_fContainer_len = m_pBloodContainer->getContentSize().width*(1- container_border_percent*2);
        
        m_fBlood_len = m_pBlood->getContentSize().width;
        
        m_fScaleFull = m_fContainer_len/m_fBlood_len;
        m_pBlood->setScaleX(m_fScaleFull);
        
        scheduleUpdate();
        
        return true;
    }
    return false;
}


void BloodGroove::update(float dt)
{
    if (m_fNextPercent != m_fCurPercent)
    {
        int temp = 1;
        if (m_fNextPercent < m_fCurPercent)
        {
            temp = -1;
        }
        
        
        m_fCurPercent += temp;
        m_fCurPercent < 0 ? m_fCurPercent = 0:0;
        m_fCurPercent > 100 ? m_fCurPercent = 100:0;
        
        m_pBlood->setScaleX(m_fScaleFull*m_fCurPercent/100);
    }
}

void BloodGroove::setProgress(float percent)
{
    m_fNextPercent = percent;
    
//    float dis = (m_fNextPercent - m_fCurPercent);
}