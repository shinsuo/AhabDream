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

USING_NS_CC;

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

class GameUtil : public cocos2d::CCObject
{
public:
    
    static CCSprite* createSprite(const char* png);
    static CCLabelAtlas* createAtlasLabel(const char* str, int num = 0, int count = 10, unsigned int startChar = '0');
    static CCMenuItemSprite* createMenuSp(const char* png);
    static CCMenuItemImage* createMenuImage(const char* normal_png, const char* selected_png = 0, const char* disabled_png = 0);
    static std::string getPngName(const char* name);
    static std::string getPlistName(const char* name);

    static std::string getTimestamp();
    static std::string getStrByInt(int i);
    static unsigned char* hex2byte(unsigned char *input, int inlen, int *outlen);
    static char* bin2hex(unsigned char* bin, int binLength);
    static std::string* byteToHexStr(unsigned char byte_arr[], int arr_len);
    static std::string getDeNickName(std::string nickName);

    static float getRandom();

    static CCScene* getMainScene();
    static float getWinWidth();
    static float getWinHeight();

	inline static const char* trim(std::string& text)  
	{  
		if(!text.empty())  
		{  
			text.erase(0, text.find_first_not_of(" \n"));
			text.erase(text.find_last_not_of(" \n") + 1);  
		}  
		return text.c_str();
	}


};

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#endif /* defined(__PuzzleTouch__GameUtil__) */
