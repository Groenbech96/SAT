//
//  CDCL.cpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include "DTUSat.hpp"


void algorithms::DTUSat::setup(cnf::Formula formula) {
    
    this->_formula = formula;
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
                return false;
            }
            
            this->setDecisionLevel(this->getBeta());
            
        } else {
            if(!this->_formula.hasUnsatisfiedClauses()) {
                
                return true;
            
            } else {
                next = pickBranchingVariable();
                next->setAssignment(cnf::TRUE);
                this->decisionLevel++;
                addToImplicationGraph(next, this->decisionLevel, -1);
                
            }
        }
    
    
    }
        
  
}


bool algorithms::DTUSat::hasConflict () {
    return this->_formula.hasConflictClause();
}


// TODO: Implement
cnf::Variable* algorithms::DTUSat::pickBranchingVariable() {
    
    // Set always to true
    for(auto kv : this->_formula.getVariables()) {
        if(kv.second->getAssignment() == cnf::UNASSIGNED) {
            return kv.second;
        }
    }
    
    return nullptr;
}


void algorithms::DTUSat::addToImplicationGraph(cnf::Variable *v, int decisionLvl, int antecedentClause) {
    this->graph.addVertex(v, decisionLvl, antecedentClause);
}


// TODO: Implement
void algorithms::DTUSat::backtrack() {
    
    this->graph.backtrack(this->beta);
    
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
    l.pVar->setAssignment((!l.isNegated) ? cnf::TRUE : cnf::FALSE);
    
    this->graph.addVertex(l.pVar, this->decisionLevel, unitClause->getId());
    
    for(auto literal = unitClause->getLiterals().begin(); literal != unitClause->getLiterals().end(); literal++) {
        if(literal->second.pVar != l.pVar) {
            this->graph.addEdge(literal->second.pVar, l.pVar);
        }
    }
}

void algorithms::DTUSat::exhaustivePropagate() {
    
    while(hasUnitClause()) {
        
        propagate();
        
    }
    
    
    /**
    auto unitClause = this->_formula.getUnitClause();
    
    //While unsatisfied clauses still exist
    while( unitClause != boost::none) {
        
        boost::optional<cnf::Literal> l = unitClause.get()->getUnitLiteral();
        // std::cout << unitClause.get()->string() << std::endl;
        if (l != boost::none) {
            
            cnf::Literal unpackedLiteral = l.get();
            
            //Assigns the variable to the value making the literal evaluate to true
            unpackedLiteral.pVar->setAssignment((!unpackedLiteral.isNegated) ? cnf::TRUE : cnf::FALSE);
            
            // Add the implied variable to the implication graph
            this->graph.addVertex(unpackedLiteral.pVar, decisionLevel, unitClause.get()->getId());
            
            // Add edges from all other variables in the same clause
            for(auto literals = unitClause.get()->getLiterals().begin(); literals != unitClause.get()->getLiterals().end();literals++ ){
                if (literals->second.pVar != unpackedLiteral.pVar) {
                    // DEBUG
                    if(literals->second.pVar->getAssignment() == cnf::UNASSIGNED) {
                        std::cout << "ERROR FAILED" << std::endl;
                    }
                    this->graph.addEdge(literals->second.pVar, unpackedLiteral.pVar);
                }
            }
        }
        
        boost::optional<cnf::Clause *> conflictClause = this->_formula.containsConflict();
        
        if(conflictClause != boost::none) {
            // Add conflict vertex to implication graph
            this->graph.addVertex(nullptr, decisionLevel, conflictClause.get()->getId());
            
            for(auto literals = conflictClause.get()->getLiterals().begin(); literals != conflictClause.get()->getLiterals().end();literals++ ){
                // DEBUG
                if(literals->second.pVar->getAssignment() == cnf::UNASSIGNED) {
                    std::cout << "ERROR FAILED" << std::endl;
                }
                this->graph.addEdge(literals->second.pVar, nullptr);
            }
            //std::cout << "conflict found " + conflictClause.get()->string()  << std::endl;
            
            return CONFLICT;
            
        } //else if(!this->formula.hasUnsatisfiedClauses()) {
        //   return SOLVED;
        // }
        
        unitClause = this->_formula.getUnitClause();
    }
    
     **/

}


void algorithms::DTUSat::learn(int i) {
    
    /**
    if(i == 0) {
        int antecedent = this->graph.getVertex(nullptr).get()->antecedentClauseID;
        
        this->learnClauseLiterals = this->_formula.getClause(antecedent)->getLiterals();
        for(auto i : this->learnClauseLiterals)
            this->queue.push(i.second);
        
        learn(i+1);
    } else {
        
        auto l = this->queue.front();
        this->queue.pop();
        
        // Insert fake new clause to method.
        cnf::Clause c = cnf::Clause(-1, this->learnClauseLiterals);
        if(this->isImpliedLiteralAtDesicionLevel(&c, l, this->decisionLevel)) {
            
            int antecedent = this->graph.getVertex(l.pVar).get()->antecedentClauseID;
            auto literals = this->_formula.getClause(antecedent)->getLiterals();
            for (auto it : literals) {
                if(this->graph.getVertex(it.second.pVar).get()->decisionLevel == this->decisionLevel)
                    queue.push(it.second);
            }
            resolution(this->learnClauseLiterals, literals);
            learn(i+1);
            
        } else if (this->isUIP(this->learnClauseLiterals)) {
            return;
        } else {
            learn(i+1);
        }
        
    }***/

}


bool algorithms::DTUSat::isUIP(algorithms::ClauseLiterals m1, int level) {
    
    int count = 0;
    for (auto it : m1) {
        
        auto vex = this->graph.getVertex(it.second.pVar).get();
        if(vex->decisionLevel == level)
            count++;
   
    }
    return count == 1;
    
}

void algorithms::DTUSat::print(std::stack<cnf::Variable *> s)
{
    if(s.empty())
    {
        std::cout << std::endl;
        return;
    }
    cnf::Variable *x = s.top();
    s.pop();
    print(s);
    s.push(x);
    std::cout << x->getKey() << " ";
}

void algorithms::DTUSat::conflictAnalysis() {
    
    // pop nullptr
    //this->graph.getStack().pop();

    //print(*graph.getStack());
    
    auto var = this->graph.getStack()->top();
    this->graph.getStack()->pop();
    
    int conflictLevel = this->graph.getVertex(var).get()->decisionLevel;
    if(conflictLevel == 0) {
        setBeta(-1);
        return;
    }
    
    int backtrack = 0;
    
    cnf::Clause *conflict = this->_formula.getConflictClause();
    int reasonID = this->graph.getVertex(var).get()->antecedentClauseID;
    cnf::Clause *reason = this->_formula.getClause(reasonID);
    
    findUIP(*conflict, *reason, conflictLevel);
    
    backtrack = this->getAssertionLevel();
    
    this->_formula.addClause(this->learnClauseLiterals);
    this->setBeta(backtrack);
    
}

void algorithms::DTUSat::findUIP(cnf::Clause c1, cnf::Clause reason, int level) {
    
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
    
    //std::cout << "UIP found" << std::endl;
    
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


int algorithms::DTUSat::getAssertionLevel() {
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



void algorithms::DTUSat::addConflict(cnf::Clause *c) {
    this->graph.addVertex(nullptr, this->decisionLevel, c->getId());
    
    for(auto literals = c->getLiterals().begin(); literals != c->getLiterals().end(); literals++){
        this->graph.addEdge(literals->second.pVar, nullptr);
    }
    
}


/*void algorithms::DTUSat::printGraph() {
    std::cout << graph.stringJsStyle() << std::endl;
}*/

cnf::Formula & algorithms::DTUSat::getFormulaState() {
    return this->_formula;
}

algorithms::ClauseLiterals algorithms::DTUSat::getLearnedClause() {
    return this->learnClauseLiterals;
}







