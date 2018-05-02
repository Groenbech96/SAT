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



/**
int algorithms::CDCLSolver::getAssertionLevel(std::unordered_map<int, cnf::Literal> *map) {
    int m1 = -1;
    int m2 = -1;
    
    if(map->size() == 1) {
        
        auto pvar = map->begin()->second.pVar;
        auto search = this->graph.getVertex(pvar);
        auto vex = search.get();
        if(search == boost::none) {
            // Do some error handling here
            // TODO: ERROR HANDLE
            //std::cout << "error 5" << std::endl;
        }
        auto vexDL = vex->decisionLevel;
        return (vexDL == 0) ? -1 : 0;
 
    }
    
    
    for(auto it = map->begin(); it != map->end(); ++it) {
        
        auto pvar = it->second.pVar;
        auto search = this->graph.getVertex(pvar);
        auto vex = search.get();
        if(search == boost::none) {
            // Do some error handling here
            // TODO: ERROR HANDLE
            //std::cout << "error 6" << std::endl;
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

**/










bool algorithms::CDCLSolver::canBacktrack() {
    return this->beta > 0;
}

bool algorithms::CDCLSolver::hasUnitClause() {
    return this->_formula.hasUnitClause();
}

bool algorithms::CDCLSolver::isImpliedLiteralAtDesicionLevel(cnf::Clause *c, cnf::Literal l, int d) {
    
    auto search = this->graph.getVertex(l.pVar);

    if(search == boost::none) {
        std::cout << "impliedLiteralNotInVertex Error" << std::endl;
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

bool algorithms::CDCLSolver::hasUndecidedVariables() { 
    return this->_formula.hasUnassignedVariables();
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




