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

#endif /* defined(__AhabDream__Actor__) */
