//
//  WaveNode.h
//  AhabDream
//
//  Created by shin on 5/6/15.
//
//

#ifndef __AhabDream__WaveNode__
#define __AhabDream__WaveNode__

#include "cocos2d.h"
#include <vector>

class WaveNode : public cocos2d::CCNode
{
public:
    WaveNode();
    ~WaveNode();
    
    static WaveNode* create(int wave_index);
    
    virtual bool init();
    
    CREATE_FUNC(WaveNode);
    
    virtual void update(float dt);
    
    CC_SYNTHESIZE(int, m_iIndex, Index);
    
private:
    std::vector<cocos2d::CCSprite*> m_vSp;
    int m_iCount;
    float m_fWidth;
};

#endif /* defined(__AhabDream__WaveNode__) */
