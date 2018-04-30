//
//  Output.hpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 30/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef Output_hpp
#define Output_hpp

#include <iostream>
#include <fstream>
#include <string>
#include "Variable.hpp"
#include "Config.hpp"
#include <unordered_map>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

namespace util {
    
class Output {

public:
    
    Output();
    
    /// Create a new output file
    /// \param config is the contex of the solver
    Output(Config config);
    
    void add(std::string);
    void addSolution(std::unordered_map<int, cnf::Variable*> solution);
    void close();
    
private:
    std::string name;
    std::ofstream outfile;
    bool enable;
    
    rapidjson::Document document;
    
    
};
    
}
#endif /* Output_hpp */
