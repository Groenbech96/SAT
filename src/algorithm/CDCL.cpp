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
}

bool algorithms::CDCL::solve() {
    
    int decisionLevel = 0;
    
    // Lines 1-3
    if(CDCL::unitPropagation(decisionLevel) == CONFLICT) {
        return false;
    }
    
    while(this->formula.hasUnassignedVariables()) {
        pickBranchingVariable(decisionLevel);
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
    
    cnf::Clause* c;
    int nMin = std::numeric_limits<int>::max();
    
    // Pick the clause with the smallest number of unassigned variables
    for(auto clausekv = clauseSet.begin(); clausekv != clauseSet.end(); clausekv++) {
        
       
    }
    
    
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




