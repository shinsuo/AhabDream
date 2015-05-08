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

class BloodGroove;
class Actor : public cocos2d::CCNode
{
public:
    Actor();
    ~Actor();
    
    static Actor* create(const char* png);
    
    virtual bool init();
    
    CREATE_FUNC(Actor);
    
    CC_SYNTHESIZE(std::string, m_strPng, StrPng);
    CC_SYNTHESIZE(std::string, m_strWeapon, StrWeapon);
    
    virtual const cocos2d::CCSize& getContentSize() const;
    
    
    virtual void fire();
    virtual void showUI();
    
    virtual void addBlood(int blood);
    virtual void addPower(int power);
    
protected:
    
    cocos2d::CCSprite* m_pSp;
    cocos2d::CCSprite* m_pWeapon;
    
    BloodGroove* m_pBlood;
    BloodGroove* m_pPower;

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
    float moveXByY(float y);
    
    CC_SYNTHESIZE(cocos2d::CCSprite*, m_pAim1, Aim1);
    CC_SYNTHESIZE(cocos2d::CCSprite*, m_pAim2, Aim2);
    
    virtual void update(float dt);
    
private:
    float m_fRotate;
};
#endif /* defined(__AhabDream__Actor__) */
