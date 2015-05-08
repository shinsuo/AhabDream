//
//  BloodGroove.h
//  AhabDream
//
//  Created by shin on 5/7/15.
//
//

#ifndef __AhabDream__BloodGroove__
#define __AhabDream__BloodGroove__

#include "cocos2d.h"

class BloodGroove : public cocos2d::CCNode
{
public:
    BloodGroove();
    ~BloodGroove();
    
    static BloodGroove* create(const char* blood_png, const char* blood_container_png, int leftorright = 0);
    
    virtual bool init();
    CREATE_FUNC(BloodGroove);
    virtual void update(float dt);
    
    void setProgress(float percent);
    
    CC_SYNTHESIZE(std::string, m_strBloodPng, BloodPng);
    CC_SYNTHESIZE(std::string, m_strBloodContainerPng, BloodContainerPng);
    CC_SYNTHESIZE(int, m_iLeftRight, LeftRight);
    
private:
    cocos2d::CCSprite* m_pBlood;
    cocos2d::CCSprite* m_pBloodContainer;
    
    float m_fContainer_len;
    float m_fBlood_len;
    float m_fScaleFull;
    
    int m_fCurPercent;
    int m_fNextPercent;
};

#endif /* defined(__AhabDream__BloodGroove__) */
