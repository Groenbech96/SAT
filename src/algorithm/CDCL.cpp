//
//  CDCL.cpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include "CDCL.hpp"

void algorithms::CDCL::setup(cnf::Formula formula) {
    this->formula = formula;
    this->graph = util::Graph();
    
    
    this->graph.addVertex(this->formula.getVariableSet().find(31)->second, 3, -1);
    this->graph.addVertex(this->formula.getVariableSet().find(1)->second, 5, -1);
    this->graph.addVertex(this->formula.getVariableSet().find(21)->second, 2, -1);

}

bool algorithms::CDCL::solve() {
    
    int decisionLevel = 0;
    
    // Lines 1-3
//    if(CDCL::unitPropagation(decisionLevel) == CONFLICT) {
//        return false;
//    }
    
    
    decisionLevel = 4;
    while(this->formula.hasUnassignedVariables()) {
        //pickBranchingVariable(decisionLevel);
        decisionLevel++;
        
        // If conflict
        UnitPropagationResult result = CDCL::unitPropagation(decisionLevel);
        if(result == CONFLICT) {
            int beta = CDCL::conflictAnalysis();
            if(beta < 0) {
                return 0;
            } else {
                CDCL::backtrack(beta);
                decisionLevel=beta;
            }
        } else if(result == SOLVED) {
            return 1;
        }
        
        
    }
    return 0;
    
    
}


// TODO: Implement
void algorithms::CDCL::pickBranchingVariable(int decisionLevel) {
    
    std::unordered_map<int, cnf::Clause *> clauseSet = formula.getClauseSet();
    
    cnf::Clause* c = new cnf::Clause;
    int nMin = std::numeric_limits<int>::max();
    
    // Pick the clause with the smallest number of unassigned variables
    for(auto clausekv = clauseSet.begin(); clausekv != clauseSet.end(); clausekv++) {
        
        int n = 0;
        
        for(auto kv : clausekv->second->getLiterals()) {
            cnf::VariableAssignment a = kv.second.pVar->getAssignment();
            
            if (a == cnf::UNASSIGNED) {
                n++;
            }
            
        }
        if (!clausekv->second->isSatisfied()){
            if (n < nMin && n > 1) {
                nMin = n;
                c = clausekv->second;
            }
        }
    }
    
    std::cout << c->string() << std::endl;
    // Pick the first unassigned variable
    for(auto kv : c->getLiterals()) {
        cnf::VariableAssignment a = kv.second.pVar->getAssignment();
        bool neg = kv.second.isNegated;
        
        cnf::Variable* var = kv.second.pVar;
        
        if (a == cnf::UNASSIGNED) {
            
            // Assign the variable so the literal evaluates to false
            var->setAssignment(neg ? cnf::TRUE : cnf::FALSE);
            
            // Update the implication graph
            this->graph.addVertex(var, decisionLevel, -1);
            
            break;
        }
    }
}


// TODO: Implement
void algorithms::CDCL::backtrack(int beta) {
    
}

void algorithms::CDCL::printGraph() {
    std::cout << graph.stringJsStyle() << std::endl;
}




