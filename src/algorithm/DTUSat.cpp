//
//  CDCL.cpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//
#include "DTUSat.hpp"


void algorithms::DTUSat::setup(cnf::Formula formula) {
    
    this->_formula = formula;
    
    for(auto it : this->_formula.getVariables()) {
        this->activity.insert(std::make_pair(it.second, 0));
    }
    
    if(this->verbose) {
        outputter.addFormulaAtStart(formula.getClauses());
    }
    
    this->graph = util::Graph();
}

bool algorithms::DTUSat::solve() {
    
    // We start with decision level 0
    this->decisionLevel = 0;
    cnf::Variable *next = nullptr;
    
    // Begin solve
    while(true) {
        
        exhaustivePropagate();
    
        if(hasConflict()) {
            
            conflictAnalysis();
            
            backtrack();
            
            if(getBeta() < 0) {
                if(this->output) {
                    this->outputter.addUnsat();
                }
                return false;
            }
            
            this->setDecisionLevel(this->getBeta());
            
        } else {
            if(!this->_formula.hasUnsatisfiedClauses()) {
                
                if(this->verbose) {
                    this->outputter.addFormulaAtEnd(this->_formula.getClauses());
                }
                if(this->output) {
                    this->outputter.addSolution(this->_formula.getVariables());
                    this->outputter.close();
                }
                return true;
            
            } else {
                next = pickBranchingVariable();
                next->setAssignment(cnf::V_TRUE);
                this->decisionLevel++;
                addToImplicationGraph(next, this->decisionLevel, -1);
                
                if(this->verbose) {
                    this->outputter.addStep("branch", &this->graph, next, this->decisionLevel);
                }
                
                
            }
        }

    }
    
}

void algorithms::DTUSat::failed() {
    this->outputter.failure();
    this->outputter.close();
}


cnf::Variable* algorithms::DTUSat::pickBranchingVariable() {
    
    float max = 0;
    cnf::Variable *maxVar = nullptr;
    for(auto it = this->activity.begin(); it != this->activity.end(); it++) {
        if(it->second >= max && it->first->getAssignment() == cnf::UNASSIGNED) {
            max = it->second;
            maxVar = it->first;
        }
    }
    //std::cout << maxVar->getKey() << " " << maxVar->getAssignment() << " score: " << max << std::endl;
    return maxVar;

}


void algorithms::DTUSat::backtrack() {
    
    this->graph.undo(this->beta);
    
    if(this->verbose) {
        this->outputter.addStep("backtrack", this->graph.rm, this->beta);
    }
    
    for(auto v : this->graph.rm) {
        delete v;
    }
    this->graph.rm.clear();
    
}

void algorithms::DTUSat::backtrackToStart() {
    
}

void algorithms::DTUSat::propagate() {
    
    auto unitClause = this->_formula.getUnitClause();
    
    auto l = unitClause->getUnitLiteral().get();
    
    //Assigns the variable to the value making the literal evaluate to true
    l.pVar->setAssignment((!l.isNegated) ? cnf::V_TRUE : cnf::V_FALSE);
    
    this->graph.addVertex(l.pVar, this->decisionLevel, unitClause->getId());
    
    for(auto literal = unitClause->getLiterals().begin(); literal != unitClause->getLiterals().end(); literal++) {
        if(literal->second.pVar != l.pVar) {
            this->graph.addEdge(literal->second.pVar, l.pVar);
        }
    }
    
    if(this->verbose) {
        this->outputter.addStep("unit_resolution", &this->graph, l.pVar, this->decisionLevel);
    }
    
}

void algorithms::DTUSat::exhaustivePropagate() {
    
    while(hasUnitClause()) {
        propagate();
    }
   
}


void algorithms::DTUSat::updateActivity() {
    // Additive bump
    for(auto it : this->getLearnedClause()) {
        this->activity.find(it.second.pVar)->second += 1;
    }
    
    // Decay
    for(auto it = this->activity.begin(); it != this->activity.end(); it++) {
        it->second = it->second * 0.95;
      
    }
    
}


void algorithms::DTUSat::conflictAnalysis() {
    
    auto var = this->graph.getStack()->top();
    this->graph.getStack()->pop();
    
    int conflictLevel = this->graph.getVertex(var).get()->decisionLevel;
    if(conflictLevel == 0) {
        setBeta(-1);
        return;
    }
    
    int backtrack = 0;
    
    cnf::Clause *conflict = this->_formula.getConflictClause();
    
    if(this->verbose) {
        this->outputter.addConflictClause(conflict);
    }
    
    int reasonID = this->graph.getVertex(var).get()->antecedentClauseID;
    cnf::Clause *reason = this->_formula.getClause(reasonID);
    
    findUIP(*conflict, *reason, conflictLevel);
    
    backtrack = this->getAssertionLevel();
    
    if(this->verbose) {
        this->outputter.addStep("conflict", this->learnClauseLiterals, conflictLevel, backtrack);
    }
    
    updateActivity();
    
    this->_formula.addClause(this->learnClauseLiterals);
    this->setBeta(backtrack);
    
}





void algorithms::DTUSat::resolution(ClauseLiterals cl1, ClauseLiterals cl2) {
    
    ClauseLiterals newMap;
    
    for(auto kv : cl1) {
        
        auto l1 = kv.second;
        
        int id = kv.first;
        
        if(cl2.find(id) != cl2.end()) { // elm is in cl2
            
            auto l2 = cl2.find(id)->second;
            if(!((l2.isNegated && !l1.isNegated) || (!l2.isNegated && l1.isNegated))) {
                newMap.insert(std::make_pair(id, l1));
            } else {
                cl2.erase(id);
            }
        } else {
            newMap.insert(std::make_pair(id, l1));
        }
    }
    for(auto kv : cl2) {
        newMap.insert(std::make_pair(kv.first, kv.second));
    }
    
    this->learnClauseLiterals = newMap;
}



/*void algorithms::DTUSat::printGraph() {
    std::cout << graph.stringJsStyle() << std::endl;
}*/

cnf::Formula & algorithms::DTUSat::getFormulaState() {
    return this->_formula;
}









