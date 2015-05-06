//
//  GameUtil.cpp
//  PuzzleTouch
//
//  Created by shin on 11/22/14.
//
//

#include "GameUtil.h"
#include "AppMacros.h"
#include "DataManager.h"
#include "CCTweenFunction.h"
#include "SoundSettingLayer.h"
#include "GlobalVar.h"
#include "CCCrypto.h"
#include "AppRes.h"
#include "ShopLayer.h"

#include <time.h>

#define NODE_9_MATRIX_LEN 3

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

float GameUtil::getRandom()
{
	return CCRANDOM_0_1();
}

MainScene* GameUtil::getMainState()
{
	return MainScene::getInstance();
}

CCSprite* GameUtil::createSprite(const char* png)
{
	return CCSprite::createWithSpriteFrameName(getPngName(png).c_str());
}

CCLabelAtlas* GameUtil::createAtlasLabel(const char* str, int num,int count, unsigned int startChar)
{
	CCTexture2D* texture2d = CCTextureCache::sharedTextureCache()->textureForKey(getPngName(str).c_str());
	CCLabelAtlas* atlas = new CCLabelAtlas;
	CCString* numStr = CCString::createWithFormat("%d", num);
	atlas->initWithString(numStr->getCString(), texture2d, texture2d->getContentSize().width/count, texture2d->getContentSize().height, startChar);
	atlas->setAnchorPoint(ccp(0.5, 0.5));
	return atlas;
}

CCMenuItemSprite* GameUtil::createMenuSp(const char* png)
{
	CCSprite* sp = CCSprite::createWithSpriteFrameName(getPngName(png).c_str());
	CCSize spSize = sp->getContentSize();
	CCMenuItemSprite* menuSp = CCMenuItemSprite::create(sp, 0);
	return menuSp;
}

std::string GameUtil::getPngName(const char* name)
{
	std::string pngName(name);
	pngName.append(".png");
	return pngName;
}

std::string GameUtil::getPlistName(const char* name)
{
	std::string plistName(name);
	plistName.append(".plist");
	return plistName;
}

std::string GameUtil::getLoginFullUrl(const char* url)
{
    const char* server = LOGIN_SERVER;
#ifdef TESTSERVER
    server = TEST_LOGIN_SERVER;
#endif
    std::string fullUrl(server);
    fullUrl.append(LOGIN_PORT);
    fullUrl.append(url);
    return fullUrl;
}

std::string GameUtil::getLogicFullUrl(std::string url)
{
    const char* server = LOGIC_SERVER;
#ifdef TESTSERVER
    server = TEST_LOGIN_SERVER;
#endif
    std::string fullUrl(server);
    fullUrl.append(LOGIC_PORT);
    fullUrl.append(url);
    return fullUrl;
}

std::string GameUtil::getStrByInt(int i)
{
    char integer[256];
    memset(integer, 0, sizeof(integer));
    sprintf(integer, "%d", i);
    return integer;
}

std::string GameUtil::getVersionUrl(std::string url)
{
    static const char* server = LOGIC_SERVER;
    static const char* version = VERSION_PORT;
#ifdef TESTSERVER
    server = TEST_VERSION;
    version = TEST_PORT;
#endif
    std::string fullUrl(server);
    fullUrl.append(version);
    fullUrl.append(url);
    return fullUrl;
}
std::string GameUtil::getSettingUrl(std::string url)
{
    static const char* server = LOGIC_SERVER;
    static const char* version = VERSION_PORT;
#ifdef TESTSERVER
	server = TEST_VERSION;
    version = TEST_PORT;
#endif
	std::string fullUrl(server);
	fullUrl.append(version);
	fullUrl.append(url);
	return fullUrl;
}

std::string GameUtil::getRedeemUrl(std::string code)
{
    std::string redeemUrl(URL_VERIFI_EXCHANGED);
    std::string status = "unused";
    std::string timestamp = getTimestamp();
    std::string strSign = code + ',' + timestamp + ',' + gChannelId + ',' + gCocosId + ',' + gUid + ',' + status;
    long sign = GameUtil::sign(strSign.c_str());
	char pstrSign[256];
    memset(pstrSign, 0, sizeof(pstrSign));
	sprintf(pstrSign,"%ld",sign);
    
    std::string param = "code=" + code + "&timestamp=" + timestamp +
    "&canal=" + gChannelId + "&appid=" + gCocosId + "&uid=" + gUid + "&status=" + status + "&sign=" + pstrSign;
    

    redeemUrl += param;
    return redeemUrl;
}

long GameUtil::sign(const char*s)
{
	if (s == NULL || strlen(s) == 0) {
		return 1;
	}
	long code = 0;
	int length = strlen(s);
	for (int idx = length - 1; idx >= 0; idx--) {
		unsigned char ch = s[idx];
		long v = (long)ch;
		code = (code << 6 & 268435455) + v + (v << 14);
        
		long k = code & 266338304;
		code = (k==0 ? code : (code ^ k >> 21));
	}
    
	return code;
}

std::string GameUtil::getTimestamp()
{
	char str[64];
	int len = sprintf(str, "%ld", time(0));
	str[len] = '\0';
	std::string str1 = str;
	return str1;
}

std::string GameUtil::getEncryptStrByInt(int i)
{
    std::string iStr = getStrByInt(i);
    int len = iStr.size();
    unchar* p = (unchar*)iStr.c_str();
    
    int resultLen = 0;
    unchar* result = CCCrypto::encryptXXTEA(p,len, (unchar*)encryptKey2, strlen(encryptKey2),&resultLen);
    std::string* p_resultStr = GameUtil::byteToHexStr((unchar*)result, resultLen);
    std::string resultStr = *p_resultStr;
    delete p_resultStr;
    free(result);
    return resultStr;
}

#define char2num(in) ((in > '9') ? ((in < 'a')?(in - 'A' + 10):(in - 'a' + 10)) : (in - '0'))
static const char *num = "0123456789ABCDEF";

unsigned char * GameUtil::hex2byte(unsigned char *input, int inlen, int *outlen)
{
    unsigned long i = 0,q = 0;
    //    LTC_ARGCHK(outlen != NULL);
    
    if (inlen % 2 != 0)
        return 0;

    *outlen = inlen  / 2;
    unsigned char* output = (unsigned char*)malloc(*outlen);
    for (q=0; q<inlen; q+=2)
    {
        output[i] = char2num(input[q]) << 4;
        output[i++] |= char2num(input[q+1]);
    }
    *outlen = i;
    return output;
}

char* GameUtil::bin2hex(unsigned char* bin, int binLength)
{
    static const char* hextable = "0123456789abcdef";
    
    int hexLength = binLength * 2 + 1;
    char* hex = new char[hexLength];
    memset(hex, 0, sizeof(char) * hexLength);
    
    int ci = 0;
    for (int i = 0; i < 16; ++i)
    {
        unsigned char c = bin[i];
        hex[ci++] = hextable[(c >> 4) & 0x0f];
        hex[ci++] = hextable[c & 0x0f];
    }
    
    return hex;
}

/*鏋勯€犱袱涓弬鏁帮紝涓€涓槸BYTE鏁扮粍锛屼竴涓槸BYTE鏁扮粍瀵瑰簲鐨勯暱搴︼紝鐩殑鏄柟渚垮悗缁殑for寰幆杩涜閬嶅巻鑰屼笉鐢ㄥ啀姝ゅ垽鏂€?
 
 */
std::string* GameUtil::byteToHexStr(unsigned char byte_arr[], int arr_len)
{
    std::string* hexstr=new std::string();
    
    for (int i=0;i < arr_len; i++)
    {
        char hex1;
        char hex2;
        /*鍊熷姪C++鏀寔鐨剈nsigned鍜宨nt鐨勫己鍒惰浆鎹紝鎶妘nsigned char璧嬪€肩粰int鐨勫€硷紝閭ｄ箞绯荤粺灏变細鑷姩瀹屾垚寮哄埗杞崲*/
        int value=byte_arr[i];
        int S=value/16;
        int Y=value % 16;
        //灏咰++涓璾nsigned char鍜宨nt鐨勫己鍒惰浆鎹㈠緱鍒扮殑鍟嗚浆鎴愬瓧姣?
        if (S>=0&&S<=9)
            
            hex1=(char)(48+S);
        else
            hex1=(char)(55+S);
        //灏咰++涓璾nsigned char鍜宨nt鐨勫己鍒惰浆鎹㈠緱鍒扮殑浣欐暟杞垚瀛楁瘝
        if (Y>=0&&Y<=9)
            hex2=(char)(48+Y);
        else
            hex2=(char)(55+Y);
        //鏈€鍚庝竴姝ョ殑浠ｇ爜瀹炵幇锛屽皢鎵€寰楀埌鐨勪袱涓瓧姣嶈繛鎺ユ垚瀛楃涓茶揪鍒扮洰鐨?
        *hexstr=*hexstr+hex1+hex2;
    }
    return hexstr;
}

std::string GameUtil::getDeNickName(std::string nickname)
{
    //avoid Chinese
    int outlen = 0;
    unchar* nickHex = GameUtil::hex2byte((unchar*)nickname.c_str(), nickname.size(), &outlen);
    int len = 0;
    unchar* decryptNick = 0;
    if (nickHex && outlen != 0)
    {
        decryptNick = CCCrypto::decryptXXTEA((unchar*)nickHex, outlen,
                                             (unchar*)encryptKey, strlen(encryptKey), &len);
    }
    
    std::string nickDec = nickname;
    if (decryptNick)
    {
        
        std::string tempNickDec((const char*)decryptNick);
        nickDec = tempNickDec;
        free(decryptNick);
    }
    
    if (nickHex)
    {
        free(nickHex);
    }
    return nickDec;
}

CC3Node* GameUtil::create3Node(const char* png, float width, float height)
{
	std::string left(png);
	left += "left";
	std::string middle(png);
	middle += "middle";
	std::string right(png);
	right += "right";
	return create3Node(left.c_str(), right.c_str(), middle.c_str(), width, height);
}

CC3Node* GameUtil::create3Node(const char* left, const char* right, const char* middle, float width, float height)
{
	CC3Node* node = CC3Node::create(left, right, middle, width,height);

	return node;
}

//CCNode* GameUtil::create9Node(const char* lefttop, const char* top, const char* righttop,
//                           const char* left, const char* middle, const char* right,
//                           const char* leftbottom, const char* bottom, const char* rightbottom,
//                           float width, float height)
CC9Node* GameUtil::create9Node(const char* png, float width, float height)
{
	CC9Node* node = CC9Node::create(png, width, height);
	return node;
}
CCNode* GameUtil::createVipHeader()
{
	VipHeaderNode* head = VipHeaderNode::create();
	return head;
}
CCNode* GameUtil::createShopCellDescription(int buyNum,int sendNum,int type)//0:heart 1:diamon 2:gold
{
	CCNode* node = CCNode::create();
	node->setAnchorPoint(ccp(0,0.5f));
	const char typeText[][32] = 
	{
		"font_shopHeart.png","font_diamond.png","font_gold.png"
	};

	float fontHeight = 28.0f;
	float fontWidth = 19.0f;

	char buyNumStr[16] = {0};
	sprintf(buyNumStr,"%d",buyNum);
	char sendNumStr[16] = {0};
	sprintf(sendNumStr,"%d",sendNum);

	CCLabelAtlas* lblBuyNum = CCLabelAtlas::create(buyNumStr,"number_shop.png",fontWidth,fontHeight,'0');
	CCSprite* typeSp = CCSprite::createWithSpriteFrameName(typeText[type]);

	unsigned long buyLenth = strlen(buyNumStr) ;
	unsigned long sendLenth = strlen(sendNumStr) ;
	if( 0 == sendNum )
	{
		CCPoint posLblNum = ccp(0,0);
		lblBuyNum->setPosition(ccp(-fontWidth,0));
		node->addChild(lblBuyNum);

		typeSp->setAnchorPoint(ccp(0,0.5));
		typeSp->setPosition(ccp(buyLenth*19.0f - fontWidth ,posLblNum.y +fontHeight/2 ));
		node->addChild(typeSp);
	}
	else
	{
// 		if( 2 != type )
// 		{
// 			lblBuyNum->setPosition(ccp(16.0f,0));
// 			typeSp->setPosition(ccp(16.0f + sendLenth*fontWidth + 32,-17.0f));
// 			node->addChild(lblBuyNum);
// 			node->addChild(typeSp);
// 		}
// 		else
// 		{
// 
// 			CCPoint posLblNum = ccp(0,0);
// 			lblBuyNum->setPosition(ccp(-fontWidth+10,0));
// 			typeSp->setAnchorPoint(ccp(0,0.5));
// 			typeSp->setPosition(ccp(buyLenth*19.0f - fontWidth +12,posLblNum.y +fontHeight/2 ));
// 			node->addChild(lblBuyNum);
// 			node->addChild(typeSp);
// 
// 		}
	}

	return node;
}
CCNode* GameUtil::createSoundSettingNode()
{
	return SoundSettingNode::create();
}
const char* GameUtil::getPayStr(int payId)
{
	return CCString::createWithFormat("PAYID%d",payId)->getCString();
}
//从商城的static数据获取价格
int GameUtil::getPriceFromShop(int kdataType)
{

	int lenth = sizeof(item_idx_set)/sizeof(int);
	int priceItem = -1;
	int idx = -1;
	for(int i = 0; i < lenth; i++)
	{
		if( item_idx_set[i] == kdataType )
		{
			idx = i;
			break;
		}
	}
	if( idx != -1 )
	{
		priceItem = price[idx][0];
	}
	return priceItem;

}
std::string GameUtil::_blockName = "";
void GameUtil::readBlockName()
{
	if( _blockName.length() > 0 )
	{
		return;
	}

	unsigned long size = 0;
	char filePath[256] = {0};
	sprintf(filePath,"blockName");
	char* pBuffer = (char*)CCFileUtils::sharedFileUtils()->getFileData(filePath,"r",&size);
	if( pBuffer )
	{

		char* newBuffer = new char[size+1];
		memcpy(newBuffer,pBuffer,size);

		delete [] pBuffer;

		char* pstr = newBuffer;
		pstr += size;
		*pstr = '\0';


		_blockName = newBuffer;

		delete[] newBuffer;
	}


}
bool GameUtil::checkName(std::string pName)
{
	if( _blockName.length() < 1 )
	{
		readBlockName();
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	char *s = new char[_blockName.length()];
#else
	char s[_blockName.length()];
#endif
    memset(s, 0, _blockName.length());
	sprintf(s,"%s",_blockName.c_str());
	const char *d = "\n";
	char *p;
	p = strtok(s,d);
	while(p)
	{
		std::string stringP = p;
		if( pName == p 
			||  std::string::npos != pName.find(p)
			//||  std::string::npos != stringP.find(pName)
		)
		{
			return false;
		}
		p = strtok(NULL,d);
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	delete [] s;
#endif

	return true;

}


//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

CC3Node* CC3Node::create(const char *png, float width, float height)
{
	std::string left(png);
	left += "left";
	std::string middle(png);
	middle += "middle";
	std::string right(png);
	right += "right";
	return create(left.c_str(), right.c_str(), middle.c_str(), width, height);
}

CC3Node* CC3Node::create(const char *left, const char *right, const char *middle, float width, float height)
{
	CC3Node* node = new CC3Node;
	if (node && node->init(left,right,middle, width, height))
	{
		node->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(node);
	}
	return node;
}

void CC3Node::setContentSize(float width, float height)
{
	m_cSize = CCSizeMake(width, m_pLeft->getContentSize().height);

	reorderSprite();
}

bool CC3Node::init(const char *left, const char *right, const char *middle, float width, float height)
{
	if (CCNode::init())
	{
		m_pLeft     = CCSprite::createWithSpriteFrameName(GameUtil::getPngName(left).c_str());
		m_pRight   = CCSprite::createWithSpriteFrameName(GameUtil::getPngName(right).c_str());
		m_pMiddle  = CCSprite::createWithSpriteFrameName(GameUtil::getPngName(middle).c_str());
		addChild(m_pLeft);
		m_pLeft->setTag(kTag_Left);
		addChild(m_pRight);
		m_pRight->setTag(kTag_Right);
		addChild(m_pMiddle);
		m_pMiddle->setTag(kTag_Middle);


		setContentSize(width, height);

		return true;
	}

	return false;
}

void CC3Node::reorderSprite()
{
	float width = m_cSize.width;
	//    float height = m_cSize.height;
	float middleWidth = width - m_pLeft->getContentSize().width - m_pRight->getContentSize().width;
	m_pMiddle->setScaleX(middleWidth/m_pMiddle->getContentSize().width);

	m_pLeft->setPosition(ccp(-(middleWidth/2+m_pLeft->getContentSize().width/2), 0));
	m_pRight->setPosition(ccp(middleWidth/2+m_pRight->getContentSize().width/2 - 1, 0));

}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

CC9Node* CC9Node::create(const char *png, float width, float height)
{
	CC9Node* node = new CC9Node;
	if (node && node->init(png, width, height))
	{
		node->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(node);
	}
	return node;
}

bool CC9Node::init(const char *png, float width, float height)
{
	if (CCNode::init())
	{
		static std::string name[NODE_9_MATRIX_LEN][NODE_9_MATRIX_LEN] = {
			{"leftbottom","bottom","rightbottom"},
			{"left","middle","right"},
			{"lefttop","top","righttop"}
		};

		for (int row = 0; row < NODE_9_MATRIX_LEN; row++)
		{
			for (int col = 0; col < NODE_9_MATRIX_LEN; col++)
			{

				char spName[64];
				memset(spName, 0, sizeof(spName));
				sprintf(spName, "%s%s.png",png,name[row][col].c_str());
				if( NULL == CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(spName) )
					continue;
				CCSprite* sp = CCSprite::createWithSpriteFrameName(spName);
				addChild(sp);
				sp->setTag(row*NODE_9_MATRIX_LEN+col);
			}
		}

		setContentSize(width, height);

		return true;
	}
	return false;
}

void CC9Node::setContentSize(float width, float height)
{
	m_cSize = CCSizeMake(width, height);

	reorderSprite();
}

void CC9Node::reorderSprite()
{
	float width = m_cSize.width;
	float height = m_cSize.height;
	int middleIdx = 1;

	for (int row = 0; row < NODE_9_MATRIX_LEN; row++)
	{
		for (int col = 0; col < NODE_9_MATRIX_LEN; col++)
		{
			CCSprite* sp = (CCSprite*)getChildByTag(row*NODE_9_MATRIX_LEN+col);
			if( NULL == sp )
				continue;

			if (row == 0 && col == 0)
			{
				m_cCornerSize = sp->getContentSize();
			}

			int colShift = col - middleIdx;
			float x = width/2*colShift - m_cCornerSize.width/2*colShift;

			int rowShift = row - middleIdx;
            float y = height/2*rowShift - m_cCornerSize.height/2*rowShift;// - (row*row*row);

			sp->setPosition(ccp(x, y));

			float spScaleY = 1.0f;
			if (row == middleIdx)
			{
				spScaleY = (height - 2*m_cCornerSize.height)/sp->getContentSize().height;
			}

			float spScaleX = 1.0f;
			if (col == middleIdx)
			{
				spScaleX = (width - 2*m_cCornerSize.width)/sp->getContentSize().width;
			}
			sp->setScaleX(spScaleX);
			sp->setScaleY(spScaleY);
		}
	}
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

CCProgressNode* CCProgressNode::create(const char* bottom, const char* blood, const char* border, float width,float shift_height, float border_width)
{
	CCProgressNode* pRet = new CCProgressNode();
	if (pRet && pRet->init(bottom, blood, border, width, shift_height, border_width))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;
}

bool CCProgressNode::init(const char* bottom, const char* blood, const char* border, float width, float shift_height, float border_width)
{
	if (CCNode::init())
	{
		m_fBorderWidth = border_width;
		m_fShiftHeight = shift_height;


		m_pBottom = CCSprite::createWithSpriteFrameName(GameUtil::getPngName(bottom).c_str());
		addChild(m_pBottom, kTag_Bottom);


		m_pBlood = CCSprite::createWithSpriteFrameName(GameUtil::getPngName(blood).c_str());
		addChild(m_pBlood, kTag_Blood);


		std::string border_left(border);
		border_left += "left";
		std::string border_middle(border);
		border_middle += "middle";
		std::string border_right(border);
		border_right += "right";

		m_pBorder = GameUtil::create3Node(border_left.c_str(), border_right.c_str(), border_middle.c_str(), width);
		addChild(m_pBorder, kTag_Border);



		m_fLastPercent = 0.0;
		m_fPercent = 0.0;
		m_fPercentFrame = 0.0;
        
        m_iCurPercent = 0;
        m_iBeforePercent = 0;
        m_iType = 0;
        m_qPercent.empty();

		setWidth(width);

		scheduleUpdate();

		return true;
	}
	return false;
}

void CCProgressNode::setWidth(float width)
{
	m_fWidth = width - m_fBorderWidth*2;

	reorderChildren();
}

float CCProgressNode::getWidth()
{
	return m_fWidth+m_fBorderWidth*2;
}

void CCProgressNode::reorderChildren()
{
	m_pBottom->setScaleX(m_fWidth/m_pBottom->getContentSize().width);
	m_pBottom->setPositionY(m_fShiftHeight);

	m_pBlood->setAnchorPoint(ccp(0.0, 0.0));
	m_pBlood->setPosition(ccp(-m_fWidth/2,-m_pBottom->getContentSize().height/2+m_fShiftHeight));

	m_pBorder->setContentSize(getWidth());
}

void CCProgressNode::setPercent(float percent, int duration)
{
	if (duration == 0)
	{
		m_fLastPercent = m_fPercent = percent;
	}
	else
	{
        float base = 0.0f;
        if (percent < m_fLastPercent)
        {
            base = 1.0f;
        }
		m_fLastPercent = percent;
		m_fPercentFrame = (base+m_fLastPercent-m_fPercent)/duration;
	}
    
    int _percent = percent;
    if (_percent != m_iBeforePercent)
    {
        addPercent(_percent);
    }
}

float CCProgressNode::getPercent()
{
	return m_fLastPercent;
}

void CCProgressNode::addPercent(int percent)
{
    m_qPercent.push(percent);
}

void CCProgressNode::setPercent2()
{
	if (m_fPercent > 100)
	{
//		m_fPercent = 100;
        m_fPercent = 0;
	}

	if (m_fPercent < 0)
	{
		m_fPercent = 0;
	}

	float blood_show_width = m_fWidth*(m_fPercent/100.0);
	float scaleX = blood_show_width/m_pBlood->getContentSize().width;
//    GAMELOG("%f,%f,%f,%f,%f,%f", blood_show_width, scaleX, m_fPercent, m_fWidth, m_pBlood->getPosition().x, m_pBlood->getPosition().y);
	m_pBlood->setScaleX(scaleX);
}

int CCProgressNode::getFrameLength(int src, int dest)
{
    return 2;//(float(dest - src))/EXP_PROGRESS_FRAME;
}

void CCProgressNode::update2(float dt)
{
    if (m_qPercent.size() > 0)
    {
        int destPercent = m_qPercent.front();
        if (m_iBeforePercent != 100 && m_iBeforePercent > destPercent)
        {
            if (m_iBeforePercent != 100)
            {
                destPercent = 100;
            }
        }
        if (m_iBeforePercent == m_iCurPercent)
        {
            if (m_iBeforePercent == 100)
            {
                m_iBeforePercent = 0;
                m_iCurPercent = 0;
            }
            m_iCurFrameLen = getFrameLength(m_iBeforePercent, destPercent);
        }
        
        
        if (m_iCurPercent < destPercent)
        {
            m_iCurPercent += m_iCurFrameLen;
        }
        else
        {
            m_iCurFrameLen = 0;
            m_iBeforePercent = m_iCurPercent = destPercent;
         
            if (destPercent == m_qPercent.front())
            {
                m_qPercent.pop();
            }
            
//            GAMELOG("to percent:%d", m_iBeforePercent);
        }
//        GAMELOG("%d,%d,%d, %d",destPercent, m_qPercent.front(), m_iCurPercent, m_iBeforePercent);
        setPercent3();
    }
}

void CCProgressNode::setPercent3()
{
    float blood_show_width = m_fWidth*(m_iCurPercent/100.0);
    float scaleX = blood_show_width/m_pBlood->getContentSize().width;
    m_pBlood->setScaleX(scaleX);
    
//        GAMELOG("cur:%d,before:%d,%f,%f", m_iCurPercent, m_iBeforePercent, blood_show_width, scaleX);
//    GAMELOG("%f,%f,%f,%f,%f,%f", blood_show_width, scaleX, m_fPercent, m_fWidth, m_pBlood->getPosition().x, m_pBlood->getPosition().y);
}

void CCProgressNode::setType(int type)
{
    m_iType = type;
}

void CCProgressNode::update1(float dt)
{
	m_fPercent += m_fPercentFrame*dt*FRAME_PER_SECOND;
	if (m_fPercent < m_fLastPercent)
	{

	}
	else
	{
		m_fPercent = m_fLastPercent;
	}

	setPercent2();
}

void CCProgressNode::update(float dt)
{
    if (m_iType == 0)
    {
        update2(dt);
    }
    else if (m_iType == 1)
    {
        update1(dt);
    }
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
VipHeaderNode* VipHeaderNode::create()
{
	VipHeaderNode* vip = new VipHeaderNode;
	if(vip->init())
	{
		vip->autorelease();
		return vip;
	}
	CC_SAFE_DELETE(vip);
	return NULL;
}
bool VipHeaderNode::init()
{
	int headIdx = GetDataManager()->getValueByType(kDataHeadImg);
	if(headIdx > HEAD_COUNT-1 )
	{
		headIdx = 0;
	}

	char headImgFile[32] = {0};
	sprintf(headImgFile,"head_%d.png",headIdx+1);

	_head = CCSprite::createWithSpriteFrameName(headImgFile);
	CCMenuItemSprite* item = CCMenuItemSprite::create(_head,0);
	item->setTarget(this,menu_selector(VipHeaderNode::menuCallBack));

	_menu = CCMenu::create(item,NULL);
	_menu->setPosition(CCPointZero);
	addChild(_menu);

	CCSize size = _head->getContentSize();
	_headBoard = CCSprite::createWithSpriteFrameName("head_1_board.png");
	_headBoard->setPosition(ccp(size.width/2 ,size.height/2-2 ));
	_head->addChild(_headBoard);

	_vip = CCSprite::createWithSpriteFrameName("vip.png");
	_vip->setAnchorPoint(ccp(0,0));
	_vip->setPosition(ccp(-25,45));
	_head->addChild(_vip,1);

	return true;
}

void VipHeaderNode::setVipVisiable(bool bVisiable)
{
	_vip->setVisible(bVisiable);
}
void VipHeaderNode::onEnter()
{
	CCNode::onEnter();

	NOTIFY_ADD(this,callfuncO_selector(VipHeaderNode::handler), NOTIFY_UPDATE_VIP, 0);
	NOTIFY_ADD(this,callfuncO_selector(VipHeaderNode::setVipHeader), NOTIFY_UPDATE_HEADCHANGE, 0);
}
void VipHeaderNode::onExit()
{
	NOTIFY_REMOVE_SELF;
	CCNode::onExit();
}
void VipHeaderNode::setVipHeader(CCObject* obj)
{
	int headIdx = GetDataManager()->getValueByType(kDataHeadImg);//((CCInteger*)obj)->getValue();
	char headImgFile[32] = {0};
	sprintf(headImgFile,"head_%d.png",headIdx+1);
	CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(headImgFile);
	_head->setDisplayFrame(frame);
}
void VipHeaderNode::handler(CCObject* obj)
{
    bool bVip = (0 !=  GetDataManager()->getInstance()->getValueByType(kDataType_Vip));
    if(bVip > 0)
    {
        setVipVisiable(true);
    }
}
void VipHeaderNode::menuCallBack(CCObject* obj)
{
    SoundManager::getInstance()->playEffect(MUSIC_BUTTON);
	NOTIFY_POST(NOTIFY_HEADIMG_CLICKED,NULL);
}
//////////////////////////////////////////////////////////////////////////
VipHeaderWithLvNode::VipHeaderWithLvNode():_expCur(0.0f),_expTotal(0.0f)
{
    NOTIFY_ADD(this, callfuncO_selector(VipHeaderWithLvNode::playLevelUp), NOTIFY_UPDATE_LEVELUP, 0);
    NOTIFY_ADD(this, callfuncO_selector(VipHeaderWithLvNode::playUpgradeText), NOTIFY_UPDATE_TEXTUPGRADE, 0);
}

VipHeaderWithLvNode* VipHeaderWithLvNode::create(CCNode* vipHeaderNode)
{
	VipHeaderWithLvNode* vip = new VipHeaderWithLvNode;
	if(vip->init(vipHeaderNode))
	{
		vip->autorelease();
		return vip;
	}
	CC_SAFE_DELETE(vip);
	return NULL;
}
bool VipHeaderWithLvNode::init(CCNode* vipHeaderNode)
{
	_vipHeadNode = (VipHeaderNode*)vipHeaderNode;
	_head = _vipHeadNode->getHead();

	_targetBarType = kTargetBar3Node;


	CCSize size = ((VipHeaderNode*)vipHeaderNode)->getHead()->getContentSize();
	_progressLv = CCProgressNode::create("exp_bottom", "exp_show", "exp_border_", 150, 2,6);
	_progressLv->setAnchorPoint(ccp(0,0.5));
	_progressLv->setPosition(ccp(size.width*2+28,8));
	addChild(_progressLv);

	_lvNode = CCNode::create();
	_lvNode->setPosition(ccp(size.width*2 - 10,-35));
	addChild(_lvNode);


	lvNBgPanelWidth = 220;
	_lvBgPanel =GameUtil::create3Node("goal1_",lvNBgPanelWidth);
	_lvBgPanel->setPosition(CCPointZero);
	_lvNode->addChild(_lvBgPanel);

	float fontHeight = 20.0f;
	float fontWidth = 12.0f;
	const char* fontFile = "numitem.png";
	char firstAlphabet = '.';


	_lvSp = CCSprite::createWithSpriteFrameName("font_lv.png");
	_lvSp->setPosition(ccp(size.width-15,10));
	addChild(_lvSp);

	int data = DataManager::getInstance()->getValueByType(kDataType_PlayerLevel);
	_lblLv = CCLabelAtlas::create("0","num_lv.png",19,24,'0');
	_lblLv->setAnchorPoint(ccp(0.0,0.5f));
	_lblLv->setPosition(ccp(_lvSp->getPositionX()+20,10));
	addChild(_lblLv, kGameSceneDebug);
	setLvNum(data);

	float lblLvCurX = size.width*2-10;

	int data1 = DataManager::getInstance()->getTotalExp();
	int data2 = DataManager::getInstance()->getValueByType(kDataType_Exp);


	_lblExpCur = CCLabelAtlas::create("0/0",fontFile,fontWidth,fontHeight,firstAlphabet);
	_lblExpCur->setAnchorPoint(ccp(0.5f,0.5f));
	_lblExpCur->setPosition(ccp(_progressLv->getPositionX(),_progressLv->getPositionY()));
	addChild(_lblExpCur,1);



	setExpTotalNum(data1);
	setExpCurNum(data2);

	_lblTarget = CCLabelAtlas::create("100",fontFile,fontWidth,fontHeight,firstAlphabet);
	_lvBgPanel->addChild(_lblTarget);


	_spTarget = CCSprite::createWithSpriteFrameName("font_target.png");
	_spTarget->setAnchorPoint(ccp(0,0.5f));
	_spTarget->setPosition(ccp(size.width-10,-35));
	addChild(_spTarget);

	addChild(vipHeaderNode);

	createlvNumPanel();

	_height = ((VipHeaderNode*)vipHeaderNode)->getBoard()->getContentSize().height;
	_width = _lvNode->getPositionX() + lvNBgPanelWidth/2 - ((VipHeaderNode*)vipHeaderNode)->getBoard()->getContentSize().width/2;

	if( 0 == GetDataManager()->getValueByType(kDataType_Vip) )
		setVipVisiable(false);

	return true;
}
void VipHeaderWithLvNode::createlvNumPanel()
{
	lvNumPanelWidth = lvNBgPanelWidth - _spTarget->getContentSize().width - 40;
	_lvNumPanel = GameUtil::create3Node("goal2_",lvNumPanelWidth);
	_lvNumPanel->setPosition(ccp(_spTarget->getContentSize().width/2,1));
	_lvBgPanel->addChild(_lvNumPanel);

	_lblTarget->setAnchorPoint(ccp(0.5f,0.5f));
	_lblTarget->setPosition(_lvNumPanel->getPosition());
	_lblTarget->setZOrder(1);
}
void VipHeaderWithLvNode::setExpCurNum(int num)
{

	_expCur = num;
	if( 0 == _expTotal )
		return;
	setExpCurNumNoPercent(num);
	float percent = _expCur / _expTotal * 100;
	setPercent(percent);
}
void VipHeaderWithLvNode::setExpTotalNum(int num)
{
	

	_expTotal = num;
	if( 0 == _expTotal )
		return;
	
	setExpCurNumNoPercent(_expCur);

	float percent = _expCur / _expTotal * 100;
//	setPercent(percent);
}
void VipHeaderWithLvNode::setLvNum(int num)
{
	char text[16] = {0};
	sprintf(text,"%d",num);
	_lblLv->setString(text);
}
void VipHeaderWithLvNode::setTargetNum(int num)
{
	char text[16] = {0};
	if( _targetBarType == kTargetBarProcess )
	{
		sprintf(text,"%d",num);
	}
	else
	{
		sprintf(text,"%d;",num);
	}
	_lblTarget->setString(text);
}
void VipHeaderWithLvNode::setHeadImg(const char* fileName)
{
	CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName);
	getHead()->setDisplayFrame(frame);
}
void VipHeaderWithLvNode::setModelImg(const char* fileName)
{
	CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(fileName);
	_spTarget->setDisplayFrame(frame);

	_lvNumPanel->removeFromParentAndCleanup(true);
	createlvNumPanel();

	_lblTarget->setString("0;");
}
void VipHeaderWithLvNode::setPercent(float percent)
{
	_progressLv->setPercent(percent, EXP_PROGRESS_FRAME);
}
void VipHeaderWithLvNode::setExpCurNumNoPercent(int num)
{
	_expCur = num;
	char txt[16] = {0};
	sprintf(txt,"%d/%d",(int)_expCur,(int)_expTotal);
	_lblExpCur->setString(txt);
}
std::vector<CCNode*> VipHeaderWithLvNode::setTargetBarType(TargetBar type)
{
	_targetBarType = type;
	CCPoint pos = _lvNumPanel->getPosition();
	_lvNumPanel->removeFromParent();

	//progressNode
	_lvNumPanel = CCProgressNode::create("exp_bottom", "exp_show", "exp_border_", lvNumPanelWidth, 2,6);
	_lvNumPanel->setPosition(pos);
    _lvNumPanel->setVisible(false);
	_lvBgPanel->addChild(_lvNumPanel);

	//back board
	std::vector<CCNode*> arr;
	arr.push_back(_lvNumPanel);
	arr.push_back(_lvBgPanel);;

	return arr;

}
void VipHeaderWithLvNode::setTargetBarPercent(float percent)
{
	if( kTargetBarProcess == _targetBarType  )
		((CCProgressNode*)_lvNumPanel)->setPercent(percent);
}

CCProgressNode* VipHeaderWithLvNode::getProgressLv()
{
	return _progressLv;
}
void VipHeaderWithLvNode::setVipVisiable(bool bVisiable)
{
	_vipHeadNode->setVipVisiable(bVisiable);
}

void VipHeaderWithLvNode::playUpgradeText(cocos2d::CCObject *obj)
{
    CCNode* parent = GameUtil::getMainState();
    CCSprite* doneSp = GameUtil::createSprite("level_up");
    parent->addChild(doneSp, kGameSceneDebug-10);
    doneSp->setPosition(ccp(g_ScreenWidth/2, g_ScreenHeight/2));
    doneSp->setScale(3);
    
    CCSize doneSize = doneSp->getContentSize();
    CCPoint destPt;
    
    CCRotateBy* rb1 = CCRotateBy::create(0.03, 20);
    CCRotateBy* rb2 = CCRotateBy::create(0.03, -20);
    CCSequence* seq1 = CCSequence::create(
                                          CCEaseBounceOut::create(CCScaleTo::create(0.6, 1)),
                                          rb1,
                                          rb1->reverse(),
                                          rb2,
                                          rb2->reverse(),
                                          rb1,
                                          rb1->reverse(),
                                          rb2,
                                          rb2->reverse(),
                                          CCDelayTime::create(0.3),
                                          CCCallFuncN::create(parent, callfuncN_selector(MainScene::garbage)),
                                          0);
    doneSp->runAction(seq1);
}

void VipHeaderWithLvNode::playLevelUp(CCObject* obj)
{
    CCPoint pt = _lblLv->getPosition();
    float duration = 0.2;
    CCSpawn* spawn1 = CCSpawn::create(CCMoveTo::create(duration, ccp(pt.x,pt.y+50)),CCScaleTo::create(duration, 3),  0);
    CCSpawn* spawn2 = CCSpawn::create(CCMoveTo::create(duration, ccp(pt.x,pt.y)),CCScaleTo::create(duration, 1),  0);
    CCSequence* seq = CCSequence::create(
//                                         CCScaleTo::create(0.3, 3),
//                                         CCScaleTo::create(0.3, 1),
                                         spawn1,
                                         spawn2,
                                         0);
    _lblLv->runAction(seq);
    
    //random play lihua particle
    static int lihuaCount = 15;
    static int lihuaRow = 3;
    static float width = g_ScreenWidth/lihuaRow;
    static float height = g_ScreenHeight/lihuaRow;
    CCNode* parent = GameUtil::getMainState();
    CSortEvent* pse = new CSortEvent;
    
//    SoundManager::getInstance()->playEffect(MUSIC_CELEBRATE);
//    SoundManager::getInstance()->playBackGroundMusic(MUSIC_CELEBRATE, false);
    SoundManager::getInstance()->playBackGroundMusic(MUSIC_CELEBRATE,false);
    
    //
    CCParticleSystemQuad* particle = CCParticleSystemQuad::create("lihua.plist");
    addChild(particle);
    particle->setAutoRemoveOnFinish(true);
    particle->setPosition(pt);
    
    for (int i = 0; i < lihuaCount; i++)
    {
        int temp = i;
        bool isTop = false;
        bool isBottom = false;
        if (temp >= 9)
        {
            isTop = true;
        }
        else if (temp < 3)
        {
            isBottom = true;
        }
        
        int col = temp%lihuaRow;
        int row = temp/lihuaRow;
        if (isTop)
        {
            row = 2;
        }
        else if(isBottom)
        {
            row = 1;
        }
        
        
        float x = col*width+width*GameUtil::getRandom();
        float y = row*height+height*GameUtil::getRandom();
        
        CCPoint pt = ccp(x,y);
        CLevelUpEvent* levelEvent = new CLevelUpEvent();
        levelEvent->init(pt);
        int frame = GameUtil::getRandom()*FRAME_PER_SECOND*2+30+i*8;
        if (i == 0)
        {
            frame = 0;
        }
        pse->addEvent(levelEvent, frame);
    }
    EventManager::getInstance()->addEvent(pse);
    pse->start();
}

void VipHeaderWithLvNode::onEnter()
{
    CCNode::onEnter();
    
    NOTIFY_ADD(this, callfuncO_selector(VipHeaderWithLvNode::updateData), NOTIFY_UPDATE_EXP, 0);
    NOTIFY_ADD(this, callfuncO_selector(VipHeaderWithLvNode::updateData), NOTIFY_UPDATE_TOTALEXP, 0);
    NOTIFY_ADD(this, callfuncO_selector(VipHeaderWithLvNode::updatePlayerLevel), NOTIFY_UPDATE_PLAYERLEVEL, 0);
    
}

void VipHeaderWithLvNode::onExit()
{
    NOTIFY_REMOVE_SELF;
    
    CCNode::onExit();
}

void VipHeaderWithLvNode::updateData(CCObject* obj)
{
    setExpTotalNum(GetDataManager()->getTotalExp());
    setExpCurNum(GetDataManager()->getValueByType(kDataType_Exp));
    
    
}

void VipHeaderWithLvNode::updatePlayerLevel(CCObject* obj)
{
    setLvNum(GetDataManager()->getValueByType(kDataType_PlayerLevel));
}

//////////////////////////////////////////////////////////////////////////
NewVipHeaderWithLvNode::NewVipHeaderWithLvNode(){}
NewVipHeaderWithLvNode::~NewVipHeaderWithLvNode(){}
NewVipHeaderWithLvNode* NewVipHeaderWithLvNode::create(CCNode* vipHeaderNode)
{
	NewVipHeaderWithLvNode* vip = new NewVipHeaderWithLvNode;
	if(vip->init(vipHeaderNode))
	{
		vip->autorelease();
		return vip;
	}
	CC_SAFE_DELETE(vip);
	return NULL;
}
bool NewVipHeaderWithLvNode::init(CCNode* vipHeaderNode)
{
	if( !VipHeaderWithLvNode::init(vipHeaderNode) )
	{
		return false;
	}

	_spTarget->setVisible(false);
	_lvBgPanel->setVisible(false);


	float widthArg = 10.0f;

	CCSize size = ((VipHeaderNode*)vipHeaderNode)->getHead()->getContentSize();
	_progressLv->removeFromParent();
	_progressLv = CCProgressNode::create("exp_bottom", "exp_show", "exp_border_", 180, 2,6);
	_progressLv->setAnchorPoint(ccp(0,0.5));
	_progressLv->setPosition(ccp(size.width*2+28+widthArg,8));
	addChild(_progressLv);

	
	_progressLv->setPosition(ccp(_lvNode->getPositionX()-30+widthArg,_lvNode->getPositionY()));
	_lblExpCur->setPosition(ccp(_progressLv->getPositionX(),_progressLv->getPositionY()));


	_lvSp->setPosition(ccp(75.0f+widthArg,_lvSp->getPositionY()-10));
	_lblLv->setPosition(ccp(_lvSp->getPositionX()+10+widthArg,_lblLv->getPositionY()-10));

	initUI();

	setMenuEnable(false);

	return true;
}
void NewVipHeaderWithLvNode::initUI()
{
	const char* fontName = "num_lv.png";
	float fontWidth = 19.0f;
	float fontHieght = 24.0f;

	float width = 130.0f;
	float height = 35.0f;

	int num = DataManager::getInstance()->getValueByType(kDataType_Level);
	char text[8] = {0};
	sprintf(text,"%d",num);
	CCLabelAtlas* lblNum = CCLabelAtlas::create(text,fontName,fontWidth,fontHieght,'0');
	lblNum->setAnchorPoint(ccp(0.5,0.5));
	lblNum->setPosition(ccp(width,height));
	addChild(lblNum);


	CCSprite* di = CCSprite::createWithSpriteFrameName("font_di.png");
	di->setAnchorPoint(ccp(1,0.5));
	di->setPosition(ccp(width-fontWidth*2,height));
	addChild(di);


	CCSprite* guan = CCSprite::createWithSpriteFrameName("font_guan.png");
	guan->setAnchorPoint(ccp(0,0.5));
	guan->setPosition(ccp(width+fontWidth*2,height));
	addChild(guan);
    
    if (g_GameMode == kMainSceneButtonTime)
    {
        lblNum->setVisible(false);
        di->setVisible(false);
        guan->setVisible(false);
        
    }

}
//////////////////////////////////////////////////////////////////////////
StageNumNode::StageNumNode()
{

}
StageNumNode::~StageNumNode()
{

}
StageNumNode* StageNumNode::create(int num)
{
	StageNumNode* stage = new StageNumNode;
	if( stage->init(num) )
	{
		stage->autorelease();
		return stage;
	}
	CC_SAFE_DELETE(stage);
	return NULL;
}
bool StageNumNode::init(int num)
{
	_num = num;


	const char* fontName = "num_lv.png";
	float fontWidth = 19.0f;
	float fontHieght = 24.0f;

	char text[8] = {0};
	sprintf(text,"%d",num);
	_lblNum = CCLabelAtlas::create(text,fontName,fontWidth,fontHieght,'0');
	_lblNum->setAnchorPoint(ccp(0.5,0.5));
	addChild(_lblNum);


	CCSprite* di = CCSprite::createWithSpriteFrameName("font_di.png");
	di->setAnchorPoint(ccp(1,0.5));
	di->setPosition(ccp(-fontWidth*2,0));
	addChild(di);


	CCSprite* guan = CCSprite::createWithSpriteFrameName("font_guan.png");
	guan->setAnchorPoint(ccp(0,0.5));
	guan->setPosition(ccp(fontWidth*2,0));
	addChild(guan);

	m_fHeight = guan->getContentSize().height;
	m_fWidth = guan->getPositionX()+guan->getContentSize().width;

	return true;
}

CCSize StageNumNode::getContentSize()
{
	return CCSizeMake(m_fWidth, m_fHeight);
}

void StageNumNode::setNum(int num)
{
	char text[8] = {0};
	sprintf(text,"%d",num);
	_num = num;
	_lblNum->setString(text);
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
Follow::Follow():m_pNode1(0)
,m_pNode2(0)
{

}

Follow::~Follow()
{

}

Follow* Follow::create(CCNode *node1, CCNode* node2)
{
    
    Follow * pRet = new Follow();
    if (pRet && pRet->init(node1, node2))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool Follow::init(CCNode* node1, CCNode* node2)
{
    if (CCNode::init())
    {
        
        m_pNode1 = node1;
        m_pNode2 = node2;
        
        return true;
    }
    return false;
    
}

void Follow::onEnter()
{
    CCNode::onEnter();
    
    scheduleUpdate();
}

void Follow::onExit()
{
    m_pNode2->removeFromParent();
    unscheduleUpdate();
    CCNode::onExit();
}

void Follow::update(float dt)
{
    if (m_pNode1 && m_pNode2)
    {
        m_pNode2->setPosition(m_pNode1->getPosition());
    }
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
CLevelUpEvent::CLevelUpEvent():m_cPoint(CCPointZero)
{
    GameUtil::getMainState()->pushLevelup();
}

CLevelUpEvent::~CLevelUpEvent()
{
    GameUtil::getMainState()->popLevelup();
}

void CLevelUpEvent::init(CCPoint pt)
{
    m_cPoint = pt;
}

void CLevelUpEvent::start()
{
    IEvent::start();
    
    CCNode* parent = GameUtil::getMainState();
    CCParticleSystemQuad* particle = CCParticleSystemQuad::create("lihua.plist");
    parent->addChild(particle);
    particle->setAutoRemoveOnFinish(true);
    //    float x = col*width+width*GameUtil::getRandom();
    //    float y = row*height+height*GameUtil::getRandom();
    particle->setPosition(ccp(m_cPoint.x,m_cPoint.y));
    
    int sound_random = GameUtil::getRandom()*3;
    char sound[20];
    memset(sound, 0, sizeof(sound));
    sprintf(sound, "fw%d.mp3", sound_random);
    GAMELOG("play %s", sound);
    SoundManager::getInstance()->playEffect(sound);
    
    end();
}
