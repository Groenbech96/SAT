//
//  Schonings.cpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include "Schonings.hpp"


void algorithms::Schonings::setup(cnf::Formula formula) {
    
    this->formula = formula;
    
}

bool algorithms::Schonings::solve() {
    // Calculate number of iterations

    int n = this->formula.getN();
    uint64_t S = (uint64_t)((std::pow(n, 2))*std::pow(4.0/3.0,n));
    //Run the algorithm
    for(uint64_t s = 0; s<S;s++){
        //Give random assignments to all variables
        for(auto kv = this->formula.getVariables().begin(); kv != this->formula.getVariables().end(); kv++) {
            if(util::Randomizer::GetRandomInt(0,1) == 1) {
                kv->second->setAssignment(cnf::V_TRUE);
            } else {
                kv->second->setAssignment(cnf::V_FALSE);
            }
            
        }
        //Flip values of variables in clauses that are not satisfied
        for (int i = 0; i < (3*n); ++i) {
            
            this->unsatisfiedClauses = this->formula.updateClauseStates();
            //If all clauses are satisfied return SAT
            if(this->unsatisfiedClauses.empty())
                return true;
            
            int index = util::Randomizer::GetRandomInt(0, (int)this->unsatisfiedClauses.size()-1);
            auto c = this->unsatisfiedClauses.at(index);
            
            // pick random literal in clause
            auto item = c->getLiterals().begin();
            std::advance(item, util::Randomizer::GetRandomInt(0, (int)c->getLiterals().size()-1));
            
            // literal id
            //int id = item->second.pVar->getKey();
            
            switch(item->second.pVar->getAssignment()) {
                case cnf::V_TRUE:
                    
                    item->second.pVar->setAssignment(cnf::V_FALSE);
                    break;
                    
                case cnf::V_FALSE:
                    
                    item->second.pVar->setAssignment(cnf::V_TRUE);
                    break;
                    
                case cnf::UNASSIGNED:
                    break;
                    
            }
        }
    }
    return false;
}
