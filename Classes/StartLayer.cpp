//
//  StartLayer.cpp
//  AhabDream
//
//  Created by shin on 5/5/15.
//
//

#include "StartLayer.h"
#include "WaveNode.h"

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
    
    readConfig();
    loadWave();
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCArray* arr = CCArray::create();
    
    CCLabelTTF* title_label = CCLabelTTF::create("Ahab's Dream", "", 48);
    CCMenuItemLabel* title = CCMenuItemLabel::create(title_label);//, this, menu_selector(StartLayer::menuCloseCallback));
    arr->addObject(title);
    title->setPosition(ccp(visibleSize.width/2,visibleSize.height/2+100));
    
    
    CCLabelTTF* start_label = CCLabelTTF::create("Start", "", 48);
    CCMenuItemLabel* start = CCMenuItemLabel::create(start_label, this, menu_selector(StartLayer::menuCloseCallback));
//    arr->addObject(start);
    start->setPosition(ccp(visibleSize.width/2,visibleSize.height/2-100));
    
    
    CCMenuItemImage* start1 = GameUtil::createMenuImage("start", "start2");
    start1->setTarget(this, menu_selector(StartLayer::menuCloseCallback));
    arr->addObject(start1);
    start1->setPosition(ccp(visibleSize.width/2,visibleSize.height/2-100));
    start1->setAnchorPoint(ccp(0.5,0.5));
    
    CCMenu* pMenu = CCMenu::createWithArray(arr);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, kMenu);

    
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    return true;
}

void StartLayer::menuCloseCallback(CCObject* pSender)
{

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
    
    for (int i = 0; i < 4; i++)
    {
//        std::string wave_name = GameUtil::getStrByInt(i+1);
//        CCSprite* wave_sp = GameUtil::createSprite(wave_name.c_str());
//        int wave_count = (int)visibleSize.width/(int)wave_sp->getContentSize().width+2;
//        addChild(wave_sp, i);
        
        WaveNode* wave = WaveNode::create(i+1);
        addChild(wave, 4-i);
        wave->setPosition(ccp(0, i*100));
    }
}

bool StartLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (m_bStart)
    {
        CCPoint pt = pTouch->getLocationInView();
        CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
        if (pt.x < visibleSize.width/2)
        {
            //left
            CCLog("left screen");
        }
        else
        {
            //right
            CCLog("right screen");
        }
    }
    return  true;
}


