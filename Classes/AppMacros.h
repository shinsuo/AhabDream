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
    
    kWave5,
    kWave4,
    kWave3,
    
    kWhale,
    kShip,
    kBattle,
    
    kWave2,
    kWave1,
    
    kUI,
    kMenu,
    
    kDebug,
};

#endif /* defined(__AhabDream__AppConfig__) */
