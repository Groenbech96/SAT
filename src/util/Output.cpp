//
//  Output.cpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 30/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include "Output.hpp"


util::Output::Output() {
    this->enable = false;
}

util::Output::Output(util::Config config) {
    
    this->outfile = std::ofstream(config.getFilename());
    this->enable = true;
    this->document.SetObject();

    
    
    this->document.AddMember(rapidjson::Value("sat solver" , document.GetAllocator()).Move(), rapidjson::Value(config.getSolverType().c_str(), document.GetAllocator()).Move(), this->document.GetAllocator());
    this->document.AddMember(rapidjson::Value("timestamp"  , document.GetAllocator()).Move(), rapidjson::Value(std::to_string(config.getTimestamp()).c_str(), document.GetAllocator()).Move(), this->document.GetAllocator());
    
}

void util::Output::add(std::string s) {
    if(enable)
        outfile << s << std::endl;
}
void util::Output::close() {
    if(enable)
        this->outfile.close();
}

void util::Output::addSolution(std::unordered_map<int, cnf::Variable*> solution) {

    if(enable) {
        rapidjson::Value smap(rapidjson::kObjectType);
        for(auto it : solution) {
            std::string res = it.second->getAssignment() == cnf::V_TRUE ? "T" : "F";
            smap.AddMember(rapidjson::Value(std::to_string(it.first + 1).c_str(), document.GetAllocator()), rapidjson::Value(res.c_str(), document.GetAllocator()), document.GetAllocator());
        }        
        document.AddMember("solution", smap, document.GetAllocator());
    
        rapidjson::StringBuffer sb;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
        document.Accept(writer);
        
        outfile << sb.GetString() << std::endl;
  
    }
    
    
    
    
}
