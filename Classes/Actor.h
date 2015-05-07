//
//  Actor.h
//  AhabDream
//
//  Created by shin on 5/7/15.
//
//

#ifndef __AhabDream__Actor__
#define __AhabDream__Actor__

#include "cocos2d.h"
#include <vector>
#include <string>

class Actor : public cocos2d::CCNode
{
public:
    Actor();
    ~Actor();
    
    static Actor* create(const char* png);
    
    virtual bool init();
    
    CREATE_FUNC(Actor);
    
    CC_SYNTHESIZE(std::string, m_strPng, StrPng);
    
    virtual const cocos2d::CCSize& getContentSize() const;
    
private:
    
    cocos2d::CCSprite* m_pSp;
};

//----------------------------------------------------------------

class Ship : public Actor
{
public:
    Ship();
    ~Ship();
    
    static Ship* create(const char* png);
    virtual bool init();
};

//----------------------------------------------------------------

class Whale : public Actor
{
public:
    Whale();
    ~Whale();
    
    static Whale* create(const char* png);
    virtual bool init();
    
    void moveAimY(float y);
    
    CC_SYNTHESIZE(cocos2d::CCSprite*, m_pAim1, Aim1);
    CC_SYNTHESIZE(cocos2d::CCSprite*, m_pAim2, Aim2);
    
    virtual void update(float dt);
};
#endif /* defined(__AhabDream__Actor__) */
