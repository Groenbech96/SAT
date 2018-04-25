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
    
    // We start with decision level 0
    int decisionLevel = 0;
    // int debugCount = 0;
    
    
    // If CNF has unit clause without any assignments
    // and it cannot be solved, then it is unsatisfiable
    if(CDCL::unitPropagation(decisionLevel) == CONFLICT) {
        return false;
    }
    
    // Run as long as variables needs to be assigned
    while(this->formula.hasUnsatisfiedClauses()) {
        
        // Pick variable and add it to Implication Graph
        auto var = pickBranchingVariable();
        decisionLevel++;
        
        addToImplicationGraph(var, decisionLevel, -1);
        
        
        // We want to unit propagate and backtrack until no conflicts are found
        while(true) {
        
            auto res = unitPropagation(decisionLevel);
            if(res == CONFLICT) {
                
                int beta = conflictAnalysis();
                if(beta < 0)
                    return false;
                else {
                    
                    backtrack(beta);
                    decisionLevel = beta;
                }
                
                
            } else {// no more conflict, we can now select next variable
                break;
            }
        
        }
        
    }
    
    return true;
        
}


// TODO: Implement
cnf::Variable* algorithms::CDCL::pickBranchingVariable() {
    
    // Set always to true
    for(auto kv : this->formula.getVariableSet()) {
        if(kv.second->getAssignment() == cnf::UNASSIGNED) {
            kv.second->setAssignment(cnf::TRUE);
            return kv.second;
        }
    }
    
    return nullptr;
    
    /**
    
    std::unordered_map<int, cnf::Clause *> clauseSet = formula.getClauseSet();
    
    cnf::Clause* c = nullptr;
    cnf::Variable* var = nullptr;
    
    
    // Pick the clause with the smallest number of unassigned variables
    for(auto clausekv = clauseSet.begin(); clausekv != clauseSet.end(); clausekv++) {
        
        int n = 0;
        
        for(auto kv : clausekv->second->getLiterals()) {
            cnf::VariableAssignment a = kv.second.pVar->getAssignment();
            
            if (a == cnf::UNASSIGNED) {
                kv.second.pVar->setAssignment(kv.second.isNegated ? cnf::TRUE : cnf::FALSE);
                return kv.second.pVar;
            }
            
        }
        
        if (n > 1) {
            c = clausekv->second;
        }
        
    }
    
    
    
    
    // Pick the first unassigned variable
    for(auto kv : c->getLiterals()) {
        cnf::VariableAssignment a = kv.second.pVar->getAssignment();
        bool neg = kv.second.isNegated;
        
        var = kv.second.pVar;
        
        if (a == cnf::UNASSIGNED) {
            
            // Assign the variable so the literal evaluates to false
            var->setAssignment(neg ? cnf::TRUE : cnf::FALSE);
            
            break;
        }
    }
    
    
    
    return var;
     
     **/

}


void algorithms::CDCL::addToImplicationGraph(cnf::Variable *v, int decisionLvl, int antecedentClause) {
    this->graph.addVertex(v, decisionLvl, antecedentClause);
}


// TODO: Implement
void algorithms::CDCL::backtrack(int backtrackLevel) {
    
    auto search = this->graph.getVertex(nullptr);

    if(search != boost::none) {
        auto vex = search.get();
        
        this->graph.backtrack(vex, backtrackLevel);
        
        for(auto v : this->graph.rm) {
            delete v;
        }
        this->graph.rm.clear();
        
    } else {
    }
    

}

void algorithms::CDCL::printGraph() {
    std::cout << graph.stringJsStyle() << std::endl;
}

cnf::Formula & algorithms::CDCL::getFormulaState() {
    return this->formula;
}




