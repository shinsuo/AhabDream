//
//  AppConfig.h
//  AhabDream
//
//  Created by shin on 5/6/15.
//
//

#ifndef __AhabDream__AppConfig__
#define __AhabDream__AppConfig__

#include <map>


extern std::map<std::string, double> config_map;
extern std::string config_keys[];


enum{
    kWave1,
    kWave2,
    
    kShip,
    kWhale,
    
    kWave3,
    kWave4,
    
    kUI,
    kMenu,
};

#endif /* defined(__AhabDream__AppConfig__) */
