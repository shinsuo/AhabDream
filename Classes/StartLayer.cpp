//
//  StartLayer.cpp
//  AhabDream
//
//  Created by shin on 5/5/15.
//
//

#include "StartLayer.h"
#include "WaveNode.h"
#include "CompassLayer.h"
#include "Actor.h"

#include "GameUtil.h"
#include "document.h"
#include "AppMacros.h"
#include <map>


std::map<std::string, double> config_map;
std::string config_keys[] = {
    "Gaptime",
    "Speed"
};

#define CONFIG_COUNT 2

StartLayer::StartLayer():m_bStart(false)
,m_pMenu(0)
,m_pLogo(0)
,m_pShip(0)
,m_pWhale(0)
,m_bRightMove(false)
{

}

StartLayer::~StartLayer()
{
    
}

bool StartLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    m_winSize = CCDirector::sharedDirector()->getVisibleSize();
    
    CCArray* arr = CCArray::create();
    
//    CCLabelTTF* title_label = CCLabelTTF::create("Ahab's Dream", "", 48);
    m_pLogo = GameUtil::createSprite("logo");
    m_pLogo->setPosition(ccp(m_winSize.width/2,m_winSize.height/2+100));
    addChild(m_pLogo, kUI);
    
    
    CCLabelTTF* start_label = CCLabelTTF::create("Start", "", 48);
    CCMenuItemLabel* start = CCMenuItemLabel::create(start_label, this, menu_selector(StartLayer::menuCloseCallback));
//    arr->addObject(start);
    start->setPosition(ccp(m_winSize.width/2,m_winSize.height/2-100));
    
    
    CCMenuItemImage* start1 = GameUtil::createMenuImage("start", "start2");
    start1->setTarget(this, menu_selector(StartLayer::menuCloseCallback));
    arr->addObject(start1);
    start1->setPosition(ccp(m_winSize.width/2,m_winSize.height/2-100));
    start1->setAnchorPoint(ccp(0.5,0.5));
    
    m_pMenu = CCMenu::createWithArray(arr);
    m_pMenu->setPosition(CCPointZero);
    this->addChild(m_pMenu, kMenu);

    
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);

    
    readConfig();
    loadWave();

    
    return true;
}

void StartLayer::menuCloseCallback(CCObject* pSender)
{
    if (!m_bStart)
    {
        CCPoint pt = ccp(m_pLogo->getPositionX(), m_winSize.height+m_pLogo->getContentSize().width/2);
        CCMoveTo* mt = CCMoveTo::create(0.6, pt);
//        CCEaseBounceOut* peeo = CCEaseBounceOut::create(mt);
        m_pLogo->runAction(mt);
        
        
        m_pMenu->setVisible(false);
        
        m_bStart = true;
        
        
        loadActor();
    }
}

void StartLayer::readConfig()
{
    unsigned long size = 0;
    unsigned char* bytes = CCFileUtils::sharedFileUtils()->getFileData("config.json", "r", &size);
    if (bytes)
    {
        bytes[size] = '\0';
        rapidjson::Document doc;
        doc.Parse<rapidjson::kParseDefaultFlags>((const char*)bytes);
        
        if (doc.HasParseError())
        {
            CCLOG("rapidjosneror:%s", doc.GetParseError());
        }
        if (doc.IsObject())
        {
            for (int i = 0; i < CONFIG_COUNT; i++)
            {
                if (doc.HasMember(config_keys[i].c_str()))
                {
                    const rapidjson::Value& pValue = doc[config_keys[i].c_str()];
                    pValue.GetDouble();
                    
                    config_map[config_keys[i].c_str()] = pValue.GetDouble();
                }
            }
            
            for (std::map<std::string, double>::iterator it = config_map.begin(); it != config_map.end(); it++)
            {
                CCLOG("read config:%s,%f", it->first.c_str(),it->second );
            }
            
        }
        
        delete[] bytes;
    }
}

void StartLayer::loadWave()
{
 
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    
    int zorders[] = {kWave1, kWave2, kWave3, kWave4, kWave5};
    float pos_ys[] = {0.1,0.25,0.5,0.7, 0.9};
    
    for (int i = 0; i < sizeof(zorders)/sizeof(int); i++)
    {
//        std::string wave_name = GameUtil::getStrByInt(i+1);
//        CCSprite* wave_sp = GameUtil::createSprite(wave_name.c_str());
//        int wave_count = (int)visibleSize.width/(int)wave_sp->getContentSize().width+2;
//        addChild(wave_sp, i);
        
        WaveNode* wave = WaveNode::create(i+1);
        addChild(wave, zorders[i]);
        wave->setPosition(ccp(0, m_winSize.height*pos_ys[i]));
    }
}

void StartLayer::loadActor()
{
    std::vector<Actor*> v_Actor;
    m_pShip = Ship::create("ship");
    addChild(m_pShip, kBattle);
    v_Actor.push_back(m_pShip);
   
    m_pWhale = Whale::create("whale");
    addChild(m_pWhale, kBattle);
    v_Actor.push_back(m_pWhale);
    
    
    int directions[] = {-1, 1};
    float y = m_winSize.height/2;
    for (int i = 0; i < v_Actor.size(); i++)
    {
        float width = v_Actor[i]->getContentSize().width/2;
        CCPoint pt = ccp((m_winSize.width/2+width)*directions[i]
                         +m_winSize.width/2,y);
        v_Actor[i]->setPosition(pt);
        
        float target_x = m_winSize.width/2+directions[i]*m_winSize.width/4;

        CCMoveTo* mt = CCMoveTo::create(0.6, ccp(target_x, y));
        v_Actor[i]->runAction(mt);
        
    }
    
}

bool StartLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_bStart)
    {
        CCPoint pt = pTouch->getLocation();

        if (pt.x < m_winSize.width/2)
        {
            //left
            CCLog("left screen");
        }
        else
        {
            //right
            CCLog("right screen");
            m_bRightMove = true;
        }
    }
    return  true;
}

void StartLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bRightMove)
    {
        CCPoint cur_pt = pTouch->getLocation();
        CCPoint pre_pt = pTouch->getPreviousLocation();
        
        float y_dis = cur_pt.y - pre_pt.y;
        m_pWhale->moveAimY(y_dis);
        CCLog("%f,%f---%f,%f", pre_pt.x, pre_pt.y, cur_pt.x, cur_pt.y);
    }
}

void StartLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bRightMove = false;
}


