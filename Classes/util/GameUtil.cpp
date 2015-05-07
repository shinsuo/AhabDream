//
//  GameUtil.cpp
//  PuzzleTouch
//
//  Created by shin on 11/22/14.
//
//

#include "GameUtil.h"

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

float GameUtil::getRandom()
{
	return CCRANDOM_0_1();
}


CCSprite* GameUtil::createSprite(const char* png)
{
    return CCSprite::create(getPngName(png).c_str());
//	return CCSprite::createWithSpriteFrameName(getPngName(png).c_str());
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
    CCSprite* sp = GameUtil::createSprite(png);//CCSprite::createWithSpriteFrameName(getPngName(png).c_str());
	CCSize spSize = sp->getContentSize();
	CCMenuItemSprite* menuSp = CCMenuItemSprite::create(sp, 0);
	return menuSp;
}

CCMenuItemImage* GameUtil::createMenuImage(const char* normal_png, const char* selected_png, const char* disabled_png)
{
    CCMenuItemImage* menuSp = CCMenuItemImage::create(getPngName(normal_png).c_str(), getPngName(selected_png).c_str(), getPngName(disabled_png).c_str());
    return menuSp;
}

std::string GameUtil::getPngName(const char* name)
{
    if (name != NULL)
    {
        std::string pngName(name);
        pngName.append(".png");
        return pngName;
    }
	return "";
}

std::string GameUtil::getPlistName(const char* name)
{
	std::string plistName(name);
	plistName.append(".plist");
	return plistName;
}

std::string GameUtil::getStrByInt(int i)
{
    char integer[256];
    memset(integer, 0, sizeof(integer));
    sprintf(integer, "%d", i);
    return integer;
}

std::string GameUtil::getTimestamp()
{
	char str[64];
	int len = sprintf(str, "%ld", time(0));
	str[len] = '\0';
	std::string str1 = str;
	return str1;
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