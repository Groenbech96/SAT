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
#include "Clause.hpp"
#include "Config.hpp"
#include "Graph.hpp"
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
    void addStep(std::string s, util::Graph *g, cnf::Variable *v, int decisionLevel);
    void addStep(std::string s, std::unordered_map<int, cnf::Literal> solution, int decisionLevel, int backtrackLevel);
    void addStep(std::string s, std::set<util::vertex *> rm, int beta);
    
    void addConflictClause(cnf::Clause *);
    void addUIP(int id);
    void addFormulaAtStart(std::unordered_map<int, cnf::Clause*>);
    void addFormulaAtEnd(std::unordered_map<int, cnf::Clause *>);
    void close();
    void failure();
    void addUnsat();
    
    void addIGraph(util::Graph *g);
    
private:
    std::string     _name;
    std::ofstream   _outfile;
    int             _step;
    int             _stepInternal;
    int             _conflictClause;
    int             _UIP;
    
    
    rapidjson::Document _document;
    
    
};
    
}
#endif /* Output_hpp */
