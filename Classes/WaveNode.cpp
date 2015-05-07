//
//  WaveNode.cpp
//  AhabDream
//
//  Created by shin on 5/6/15.
//
//

#include "WaveNode.h"
#include "GameUtil.h"
USING_NS_CC;

WaveNode::WaveNode():m_iIndex(-1),m_iCount(0)
{
    m_vSp.clear();
}

WaveNode::~WaveNode()
{
    m_vSp.clear();
}

WaveNode* WaveNode::create(int wave_index)
{
    WaveNode* p = new WaveNode();
    p->setIndex(wave_index);
    
    if (p && p->init())
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

bool WaveNode::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    std::string wave_name = GameUtil::getStrByInt(m_iIndex);
    
    CCSprite* wave_sp = GameUtil::createSprite(wave_name.c_str());
    m_fWidth = wave_sp->getContentSize().width;

    int wave_count = (int)visibleSize.width/(int)wave_sp->getContentSize().width+2;
    for (int i = 0; i < wave_count; i++)
    {
        wave_sp = GameUtil::createSprite(wave_name.c_str());
        addChild(wave_sp);
        m_vSp.push_back(wave_sp);
        wave_sp->setAnchorPoint(ccp(0.0, 0.5));
        
        wave_sp->setPositionX(m_fWidth*i);
        
//        CCLabelTTF* label=  CCLabelTTF::create(GameUtil::getStrByInt(i).c_str(), "", 48);
//        wave_sp->addChild(label);
//        label->setPositionY(wave_sp->getContentSize().height);
    }
    
    m_iCount = wave_count;
    scheduleUpdate();
    
    return true;
}

void WaveNode::update(float dt)
{
    for (int i = 0; i < m_iCount; i++)
    {
        float cur_x = m_vSp[i]->getPositionX()-dt*30*(5-m_iIndex);
        if (cur_x + m_fWidth < 0)
        {
            cur_x += (m_iCount)*m_fWidth;
        }
//        else
        {
            m_vSp[i]->setPosition(ccp(cur_x, 0));
        }
    }
    
//    for (int i = 0; i < m_iCount; i++)
//    {
//        float cur_x = m_vSp[i]->getPositionX();
//        if (cur_x + m_fWidth < 0)
//        {
//            cur_x += (m_iCount-1)*m_fWidth;
//        }
//        else
//        {
//            m_vSp[i]->setPosition(ccp(cur_x, 0));
//        }
//    }
}