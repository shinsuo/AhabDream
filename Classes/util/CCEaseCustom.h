//
//  CCEaseCustom.h
//  DianDian
//
//  Created by shin on 12/10/14.
//
//

#ifndef __DianDian__CCEaseCustom__
#define __DianDian__CCEaseCustom__

#include "cocos2d.h"
#include "CCTweenFunction.h"

USING_NS_CC;

class  CCEaseCustom : public CCActionEase
{
public:

    virtual void update(float time);
    /**
     *  @js NA
     *  @lua NA
     */
    virtual CCObject* copyWithZone(CCZone* pZone);
    
public:
    
    /** creates the action */
    static CCEaseCustom* create(CCActionInterval* pAction, CCTweenType tweenType);

    CC_SYNTHESIZE(CCTweenType, m_tweenType, TweenType);
};

#endif /* defined(__DianDian__CCEaseCustom__) */
