//
//  GameUtil.h
//  PuzzleTouch
//
//  Created by shin on 11/22/14.
//
//

#ifndef __PuzzleTouch__GameUtil__
#define __PuzzleTouch__GameUtil__

#include "cocos2d.h"
#include "AppMacros.h"
#include "MainScene.h"
#include "SoundManger.h"
#include "CCEaseCustom.h"
#include "CCTweenFunction.h"
#include "EventManager.h"
#include <queue>

USING_NS_CC;

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class CC3Node;
class CC9Node;

class GameUtil : public cocos2d::CCObject
{
public:
    enum
    {
        kTag_Left,
        kTag_Middle,
        kTag_Right
    };

    
    static MainScene* getMainState();
    static CCSprite* createSprite(const char* png);
    static CCLabelAtlas* createAtlasLabel(const char* str, int num = 0, int count = 10, unsigned int startChar = '0');
    static CCMenuItemSprite* createMenuSp(const char* png);
    static std::string getPngName(const char* name);
    static std::string getPlistName(const char* name);
    static std::string getLoginFullUrl(const char* url);
    static std::string getLogicFullUrl(std::string url);
    static std::string getVersionUrl(std::string url);
	static std::string getSettingUrl(std::string url);
    static std::string getRedeemUrl(std::string code);
    static long sign(const char*s);
    static std::string getTimestamp();
    static std::string getStrByInt(int i);
    static std::string getEncryptStrByInt(int i);
    static unsigned char* hex2byte(unsigned char *input, int inlen, int *outlen);
    static char* bin2hex(unsigned char* bin, int binLength);
    static std::string* byteToHexStr(unsigned char byte_arr[], int arr_len);
    static std::string getDeNickName(std::string nickName);
    static CC3Node* create3Node(const char* png, float width, float height = 0);
    static CC3Node* create3Node(const char* left, const char* right, const char* middle, float width, float height = 0);
//    static CCNode* create9Node(const char* lefttop, const char* top, const char* righttop,
//                               const char* left, const char* middle, const char* right,
//                               const char* leftbottom, const char* bottom, const char* rightbottom,
//                               float width, float height);
    
    static CC9Node* create9Node(const char* png, float width, float height);
    static float getRandom();

	static CCNode* createVipHeader();
	static CCNode* createShopCellDescription(int buyNum,int sendNum,int type);//0:heart 1:diamond
	static CCNode* createSoundSettingNode();

	static const char* getPayStr(int payId);

	//从商城的static数据获取价格
	static int getPriceFromShop(int kdataType);


	inline static const char* trim(std::string& text)  
	{  
		if(!text.empty())  
		{  
			text.erase(0, text.find_first_not_of(" \n"));  
			text.erase(text.find_last_not_of(" \n") + 1);  
		}  
		return text.c_str();
	}

	static std::string _blockName;
	static void readBlockName();
	static bool checkName(std::string pName);


};

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=




class CC3Node : public cocos2d::CCNode
{
public:
    enum
    {
        kTag_Left,
        kTag_Middle,
        kTag_Right
    };
    static CC3Node* create(const char* png, float width, float height = 0);
    static CC3Node* create(const char* left, const char* right, const char* middle, float width, float height = 0);
    
    CCSize getContentSize(){return m_cSize;}
    void setContentSize(float width, float height = 0);
    
    bool init(const char *left, const char *right, const char *middle, float width, float height);
    void reorderSprite();
    
    CC_SYNTHESIZE(CCSprite*, m_pLeft,   LeftSprite);
    CC_SYNTHESIZE(CCSprite*, m_pMiddle, MiddleSprite);
    CC_SYNTHESIZE(CCSprite*, m_pRight,  RightSprite);
    
private:
    CCSize m_cSize;
};

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class CC9Node : public cocos2d::CCNode
{
public:
    enum
    {
        kTag_LeftBottom,
        kTag_Bottom,
        kTag_RightBottom,
        
        kTag_Left,
        kTag_Middle,
        kTag_Right,
        
        kTag_LeftTop,
        kTag_Top,
        kTag_RightTop
    };
    static CC9Node* create(const char* png, float width, float height);
    
    CCSize getContentSize(){return m_cSize;}
    void setContentSize(float width, float height);
    
    bool init(const char* png, float width, float height);
    void reorderSprite();
    
private:
    CCSize m_cSize;
    CCSize m_cCornerSize;
};

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class CCProgressNode : public cocos2d::CCNode
{
public:
    enum
    {
        kTag_Bottom,
        kTag_Blood,
        kTag_Border
    };
    static CCProgressNode* create(const char* bottom, const char* blood, const char* border,
                                  float width, float shift_height = 0.0, float border_width = 0.0);
    virtual bool init(const char* bottom, const char* blood, const char* border,
                      float width,float shift_height, float border_width);
    void setPercent(float percent, int duration = 0);
    void setType(int type = 0);
    void addPercent(int percent);
    int getFrameLength(int src, int dest);
    
    float getPercent();
    
    virtual void update2(float dt);
    virtual void update1(float dt);
    virtual void update(float dt);
    
    void setWidth(float width);
    float getWidth();
    
private:
    CC3Node* m_pBorder;
    CCSprite* m_pBlood;
    CCSprite* m_pBottom;
    
    float m_fWidth;
    float m_fPercent;
    float m_fLastPercent;
    float m_fPercentFrame;
    float m_fShiftHeight;
    float m_fBorderWidth;
    
    int m_iBeforePercent;
    int m_iCurPercent;
    int m_iCurFrameLen;
    
    void setPercent2();
    void setPercent3();
    
    void reorderChildren();
    
    std::queue<int> m_qPercent;
    int m_iType;
};

class VipHeaderNode : public CCNode
{
public:
	virtual bool init();
	static VipHeaderNode* create();
	CCSprite* getHead(){return _head;}
	CCSprite* getBoard(){return _headBoard;}
	void setVipVisiable(bool bVisiable);



	void onEnter();
	void onExit();
	void handler(CCObject* obj);
	void setVipHeader(CCObject* obj);
	void setMenuEnable(bool b){_menu->setEnabled(b);}

	CCMenu* getMenu(){return _menu;}

private:
	CCMenu* _menu;
	void menuCallBack(CCObject* obj);
	CCSprite* _head;
	CCSprite* _headBoard;
	CCSprite* _vip;
};

class VipHeaderWithLvNode : public  CCNode
{
public:
    VipHeaderWithLvNode();
	enum TargetBar
	{
		kTargetBar3Node,
		kTargetBarProcess
	};
	struct ProgressBar
	{
		CCNode* board;
		CCProgressNode* progress;
	};

	static VipHeaderWithLvNode* create(CCNode* vipHeaderNode);
	virtual bool init(CCNode* vipHeaderNode);

	CCSprite* getHead(){return _head;}

	float getWidth(){return _width;}
	float getHeight(){return _height;}

	void setExpCurNum(int num);
	void setExpTotalNum(int num);
	void setLvNum(int num);
	void setTargetNum(int num);

	void setHeadImg(const char* fileName);
	void setModelImg(const char* fileName);


	void setExpCurNumNoPercent(int num);
	void setPercent(float percent);
	
	std::vector<CCNode*> setTargetBarType(TargetBar type);
	void setTargetBarPercent(float percent);
    
    CCProgressNode* getProgressLv();

	CCNode* getCurExpLabel(){return _lblExpCur;}

	void setVipVisiable(bool bVisiable);
    void playUpgradeText(CCObject* obj);
    void playLevelUp(CCObject* obj);
    void onEnter();
    void onExit();
    void updateData(CCObject* obj);
    void updatePlayerLevel(CCObject* obj);
	void setMenuEnable(bool b){_vipHeadNode->setMenuEnable(b);};
	CCMenu* getMenu(){return _vipHeadNode->getMenu();}
protected:
	CCProgressNode* _progressLv;
	CCLabelAtlas* _lblLv;
	CCLabelAtlas* _lblExpCur;
	CCLabelAtlas* _lblTarget;
	CCSprite* _spTarget;
	CCSprite* _head;
	float _expCur;
	float _expTotal;

	float _height;
	float _width;

	float lvNBgPanelWidth;
	float lvNumPanelWidth;

	CCNode* _lvNumPanel;
	CCNode* _lvBgPanel;
	CCNode* _lvNode;
	CCSprite* _lvSp;
	void createlvNumPanel();
	TargetBar _targetBarType;

	VipHeaderNode* _vipHeadNode;
};
class NewVipHeaderWithLvNode : public VipHeaderWithLvNode
{
public:

	NewVipHeaderWithLvNode();
	~NewVipHeaderWithLvNode();
	virtual bool init(CCNode* vipHeaderNode);
	static NewVipHeaderWithLvNode* create(CCNode* vipHeaderNode);


private:
	void initUI();
};
class StageNumNode : public CCNode
{
public:

	StageNumNode();
	~StageNumNode();
	virtual bool init(int num);
	static StageNumNode* create(int num);

	void setNum(int num);
	int getNum(){return _num;}
    
    CCSize getContentSize();

private:
	CCLabelAtlas* _lblNum;
	int _num;
	
    float m_fWidth;
    float m_fHeight;
};

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class Follow : public CCNode
{
public:
    Follow();
    ~Follow();
    
    static Follow* create(CCNode *node1, CCNode* node2);
    void update(float dt);
    void onEnter();
    void onExit();
    bool init(CCNode* node1, CCNode* node2);
private:
    CCNode* m_pNode1;
    CCNode* m_pNode2;
};

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
class CLevelUpEvent : public IEvent
{
public:
    CLevelUpEvent();
    ~CLevelUpEvent();
    
    void init(CCPoint pt);
    void start();
    
private:
    CCPoint m_cPoint;
    
};

#endif /* defined(__PuzzleTouch__GameUtil__) */
