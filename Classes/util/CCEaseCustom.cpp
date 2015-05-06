//
//  CCEaseCustom.cpp
//  DianDian
//
//  Created by shin on 12/10/14.
//
//

#include "CCEaseCustom.h"
#include "CCTweenFunction.h"


CCEaseCustom* CCEaseCustom::create(CCActionInterval *pAction, CCTweenType tweenType)
{
    CCEaseCustom *pRet = new CCEaseCustom();
    if (pRet)
    {
        if (pRet->initWithAction(pAction))
        {
            pRet->setTweenType(tweenType);
            pRet->autorelease();
        }
        else
        {
            CC_SAFE_RELEASE_NULL(pRet);
        }
    }
    
    return pRet;
}

CCObject* CCEaseCustom::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCEaseCustom* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCEaseCustom*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCEaseCustom();
        pNewZone = new CCZone(pCopy);
    }
    
    pCopy->initWithAction((CCActionInterval *)(m_pInner->copy()->autorelease()));
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCEaseCustom::update(float time)
{
    float newT = CCTweenFunction::tweenTo(time, m_tweenType, 0);
    m_pInner->update(newT);
}