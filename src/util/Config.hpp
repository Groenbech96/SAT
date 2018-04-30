//
//  Config.hpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date 30/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef Config_hpp
#define Config_hpp

#include <string>
#include <ctime>

namespace util {
    
    class Config {
        
    public:
        
        Config(std::string solverType, std::string filename) : _solverType(solverType), _filename(filename) { _timestamp = std::time(0); }
        
        void setSolverType(std::string type);
        std::string getSolverType();
        
        void setFilename(std::string filename);
        std::string getFilename();
        
        time_t getTimestamp();
        
    private:
        std::string _solverType;
        std::string _filename;
        time_t _timestamp;
        
        //bool decisionTracking;
        //bool decisionScoreTracking;
        //bool implicationGraphTracking;
        //bool graphTracking
        
        
    };
}



#endif /* Config_hpp */
