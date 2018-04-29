//
//  CompleteSolver.cpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include "CDCLSolver.hpp"


// Provide a definition for destructor.
algorithms::CDCLSolver::~CDCLSolver() {}

bool algorithms::CDCLSolver::canBacktrack() {
    return this->beta > 0;
}

bool algorithms::CDCLSolver::hasUnitClause() {
    return this->_formula.hasUnitClause();
}
bool algorithms::CDCLSolver::hasConflict () {
    return this->_formula.hasConflictClause();
}
bool algorithms::CDCLSolver::hasUndecidedVariables() {
    return this->_formula.hasUnassignedVariables();
}


bool algorithms::CDCLSolver::isImpliedLiteralAtDesicionLevel(cnf::Clause *c, cnf::Literal l, int d) {
    
    auto search = this->graph.getVertex(l.pVar);

    if(search == boost::none) {
        exit(10);
        return false;
    } else {
        auto vex = search.get();
       
        boost::optional<cnf::Literal&> found = c->getLiteral(l.pVar->getKey());
        bool dlvl = d == vex->decisionLevel;
        bool dec  = vex->antecedentClauseID != -1;
        
        return found != boost::none && dlvl && dec;
    }
    
    return false;
}

int algorithms::CDCLSolver::getGraphSize() {
    return (int) this->graph.graphMap.size();
}


int algorithms::CDCLSolver::getBeta() {
    return this->beta;
}
void algorithms::CDCLSolver::setBeta(int b) {
    this->beta = b;
}

int algorithms::CDCLSolver::getDecisionLevel() {
    return this->decisionLevel;
}
void algorithms::CDCLSolver::setDecisionLevel(int dl) {
    this->decisionLevel = dl;
}

void algorithms::CDCLSolver::addToImplicationGraph(cnf::Variable *v, int decisionLvl, int antecedentClause) {
    this->graph.addVertex(v, decisionLvl, antecedentClause);
}


void algorithms::CDCLSolver::addConflict(cnf::Clause *c) {
    this->graph.addVertex(nullptr, this->decisionLevel, c->getId());
    
    for(auto literals = c->getLiterals().begin(); literals != c->getLiterals().end(); literals++){
        this->graph.addEdge(literals->second.pVar, nullptr);
    }
    
}

void algorithms::CDCLSolver::findUIP(cnf::Clause c1, cnf::Clause reason, int level) {
    
    this->learnClauseLiterals.clear();
    
    // int conflictLevel = this->graph.getVertex(nullptr).get()->decisionLevel;
    resolution(c1.getLiterals(), reason.getLiterals());
    
    while (!isUIP(this->learnClauseLiterals, level)) {
        
        if(!this->graph.getStack()->empty()) {
            
            auto var = this->graph.getStack()->top();
            this->graph.getStack()->pop();
            int reasonID = this->graph.getVertex(var).get()->antecedentClauseID;
            cnf::Clause *reason = this->_formula.getClause(reasonID);
            
            resolution(this->learnClauseLiterals, reason->getLiterals());
            
        } else {
            
            // No UIP was found
            // Last UIP is decision variable itself + all variables assigned at levels with a value less than that of the conflict level and the actual decision variable whose assignment was responsible for the confict.
            this->learnClauseLiterals.clear();
       
            for(auto kv : this->graph.graphMap) {
                
                auto vex = kv.second;
                if(vex->antecedentClauseID == -1 && vex->decisionLevel <= level) {
                    cnf::Literal l = {kv.first, true};
                    this->learnClauseLiterals.insert({kv.first->getKey(), l});
                }
                
            }
            return;
            
        }
        
    }
    
}




algorithms::ClauseLiterals algorithms::CDCLSolver::getLearnedClause() {
    return this->learnClauseLiterals;
}

bool algorithms::CDCLSolver::isUIP(algorithms::ClauseLiterals m1, int level) {
    
    int count = 0;
    for (auto it : m1) {
        
        auto vex = this->graph.getVertex(it.second.pVar).get();
        if(vex->decisionLevel == level)
            count++;
        
    }
    return count == 1;
    
}

int algorithms::CDCLSolver::getAssertionLevel() {
    int m1 = -1;
    int m2 = -1;
    
    if(this->learnClauseLiterals.size() == 1) {
        auto pvar = learnClauseLiterals.begin()->second.pVar;
        auto search = this->graph.getVertex(pvar);
        auto vex = search.get();
        if(search == boost::none) {
            // Do some error handling here
        }
        
        auto vexDL = vex->decisionLevel;
        return (vexDL == 0) ? -1 : 0;
        
    }
    
    for(auto it = this->learnClauseLiterals.begin(); it != this->learnClauseLiterals.end(); ++it) {
        
        auto pvar = it->second.pVar;
        auto search = this->graph.getVertex(pvar);
        auto vex = search.get();
        if(search == boost::none) {
            // Do some error handling here
        }
        
        
        // get second highest decision lvl
        if(vex->decisionLevel > m2) {
            if(vex->decisionLevel > m1) {
                m2 = m1;
                m1 = vex->decisionLevel;
            } else if (vex->decisionLevel != m1) {
                m2 = vex->decisionLevel;
            }
        }
    }
    
    // No second highest found
    // Learned clause only contains one decision level
    if( m2 == -1) {
        return m1;
    }
    return m2;
}




