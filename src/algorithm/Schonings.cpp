//
//  Schonings.cpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include "Schonings.hpp"

void algorithms::Schonings::setup(cnf::Formula formula) {
    
    this->formula = formula;
    
    
    for(auto kv = this->formula.getVariableSet().begin(); kv != this->formula.getVariableSet().end(); kv++) {
    if(util::Randomizer::GetRandomInt(0,1) == 1) {
     kv->second->setAssignment(cnf::TRUE);
    } else {
     kv->second->setAssignment(cnf::FALSE);
    }

    }
    
}

bool algorithms::Schonings::solve() {
    
    for (int i = 0; i < (3*this->formula.getM()); ++i) {
        
        this->unsatisfied_clauses = formula.updateClauseStates();
        if(this->unsatisfied_clauses.empty())
            return true;
        
        int index = util::Randomizer::GetRandomInt(0, (int)this->unsatisfied_clauses.size()-1);
        auto c = this->unsatisfied_clauses.at(index);
        
        // int literalIndex = util::Randomizer::GetRandomInt(0, (int)c->getLiterals().size()-1);
        
        // pick random literal in clause
        auto item = c->getLiterals().begin();
        std::advance(item, util::Randomizer::GetRandomInt(0, (int)c->getLiterals().size()-1));
        
        // literal id
        //int id = item->second.pVar->getKey();
        
        switch(item->second.pVar->getAssignment()) {
            case cnf::TRUE:
                
                item->second.pVar->setAssignment(cnf::FALSE);
                
        
                break;
            case cnf::FALSE:
                
                item->second.pVar->setAssignment(cnf::TRUE);
                
                
                
                break;
            case cnf::UNASSIGNED:break;
                
        }
    }
    return false;
    
}
