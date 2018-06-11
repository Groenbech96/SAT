//
//  Formula.cpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 28/02/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include "Formula.hpp"


void cnf::Formula::clean() {
    
    for(auto it : this->getVariables()) {
        delete it.second;
    }
    
    for(auto it : this->getClauses()) {
        delete it.second;
    }
    
}

int cnf::Formula::getM() {
    return this->m;
}

int cnf::Formula::getK() {
    return this->k;
}

int cnf::Formula::getN() {
    return this->n;
}

std::unordered_map<int, cnf::Variable *> &cnf::Formula::getVariables() {
    return this->variableSet;
}

std::unordered_map<int, cnf::Clause *> &cnf::Formula::getClauses() {
    return this->clauseSet;
}

cnf::Formula::Formula(int k,
                      int m,
                      int n,
                      std::unordered_map<int, cnf::Variable *> variableSet,
                      std::unordered_map<int, cnf::Clause *> clauses)
{
    
    this->variableSet = variableSet;
    this->clauseSet = clauses;
    this->k = k;
    this->m = m;
    this->n = n;
 
}

cnf::Formula::Formula(int k, int m, int n) : k(k), m(m), n(n) {
    
    std::unordered_set<int> unusedVariablesInFormula;
    
    // Create n new variables
    for (int i = 0; i < this->n; i++) {
        unusedVariablesInFormula.insert(i);
        Variable *var = new Variable(i);
        this->variableSet.insert({i, var});
    }
    
    // Plan is as follows:
    // Insert all used variables into the set, and then filter out the ones not used when formula is made!
    // Set has O(log(set.size())) on insert
    
    this->clauseSet = std::unordered_map<int, Clause *>();
    
    // Create m new clauses
    for (int i = 0; i < this->m; i++) {
        
        std::list<Literal> clauseLiterals;
        std::unordered_map<int, cnf::Literal> clauseLiteralsMap;
        std::vector<int> usedVariablesInClause;
        
        // Create k new literals in this clause
        for (int j = 0; j < this->k; ++j) {
            
            int id       = util::Randomizer::GetRandomInt(0 , n-1);
            bool negated = util::Randomizer::GetRandomInt(0 , 1) == 0;
            
            // Make sure that id only occurs once in clause
            while (std::find(usedVariablesInClause.begin(), usedVariablesInClause.end(), id) != usedVariablesInClause.end()) {
                id = util::Randomizer::GetRandomInt(0, n - 1);
            }
            
            // Add new id
            usedVariablesInClause.push_back(id);
            // Remove it because it is now used
            unusedVariablesInFormula.erase(id);
            
            // Literal created of pointer to var
            cnf::Literal l = {(this->variableSet.at(id)), negated};
            
            // Make sure that list is in incremental order
            clauseLiteralsMap.insert({id, l});
            
        }
        
        this->clauseSet.insert({i, new cnf::Clause(i, clauseLiteralsMap)});
    }
    
    // The variable set ends up only containing variables that are used in formula
    for(int id : unusedVariablesInFormula) {
        this->variableSet.erase(id);
    }
    
}



std::vector<cnf::Clause *> cnf::Formula::updateClauseStates() {
    
    std::vector<cnf::Clause *> unsatisfied;
    
    for(auto kv = this->getClauses().begin(); kv != this->getClauses().end(); kv++) {
        
        kv->second->evaluate();
        if(!kv->second->isSatisfied()) {
            unsatisfied.push_back(kv->second);
        }
        
    }
    
    return unsatisfied;
    
}

boost::optional<cnf::Variable *> cnf::Formula::getVariable(int id) {
    
    auto p = this->variableSet.find(id);
    if(p != this->variableSet.end()) {
        return p->second;
    } else {
        return boost::none;
    }
    
}

bool cnf::Formula::hasUnassignedVariables() {
    
    // KV = key, value
    // First = key
    // Second = Clause
    for(auto kv : this->getVariables()) {
        if(kv.second->getAssignment() == cnf::UNASSIGNED)
            return true;
    }
    
    return false;
}



/**
boost::optional<cnf::Clause *> cnf::Formula::getUnitClause() {
    cnf::Clause* c = nullptr;
    for(auto kv = this->getClauses().begin(); kv != this->getClauses().end(); kv++) {
        
        if (kv->second->isUnit()) {
            c = kv->second;
            
        }
    }
    if(c != nullptr)
        return c;
    return boost::none;
}
**/


bool cnf::Formula::hasUnitClause() {
    for(auto kv = this->getClauses().begin(); kv != this->getClauses().end(); kv++) {
        
        if (kv->second->isUnit()) {
            this->unitClause = kv->second;
            return true;
        }
    }
    return false;
}


bool cnf::Formula::hasUnsatisfiedClauses() {
    
    // KV = key, value
    // First = key
    // Second = Clause
    for(auto kv = this->getClauses().begin(); kv != this->getClauses().end(); kv++) {
        auto c = kv->second;
        if (!c->isSatisfied()) {
            return true;
        }
    }
    
    return false;
}


cnf::Clause* cnf::Formula::getConflictClause() {
    return this->conflictClause;
}

cnf::Clause* cnf::Formula::getUnitClause() {
    return this->unitClause;
}

bool cnf::Formula::hasConflictClause() {
    for(auto kv = this->getClauses().begin(); kv != this->getClauses().end(); kv++) {
        if (kv->second->containsConflict()) {
            this->conflictClause = kv->second;
            return true;
        }
    }
    return false;
}

boost::optional<cnf::Clause *> cnf::Formula::containsConflict() {
    
    for(auto kv = this->getClauses().begin(); kv != this->getClauses().end(); kv++) {
        
        if (kv->second->containsConflict()) {
            return kv->second;
        }
    }
    
    return boost::none;
}

void cnf::Formula::addClause(std::unordered_map<int, cnf::Literal> l) {
    
    cnf::Clause *c = new Clause(this->m, l);
    
    //std::cout << c->string() << std::endl;
    
    this->lastAddedClause = *c;
    // std::cout << c->string() << std::endl;
    // Important is to update m after insert! Do to zero index in map!!!
    this->clauseSet.insert({this->m, c});
    this->m++;
}

cnf::Clause* cnf::Formula::addClause() {
    
    cnf::Clause *c = new Clause(this->m);
    this->lastAddedClause = *c;
    // std::cout << c->string() << std::endl;
    // Important is to update m after insert! Do to zero index in map!!!
    this->clauseSet.insert({this->m, c});
    this->m++;
    return c;
}


cnf::Clause & cnf::Formula::getLastAddedClause() {
    return lastAddedClause;
}


std::string cnf::Formula::string() {
    
    std::string s = "[ ";
    
    for(auto kv = this->getClauses().begin(); kv != this->getClauses().end(); kv++) {
        std::string cs = kv->second->string();
        s+=cs + " ";
    }
    
    s += "]";
    
    return s;
}

// TODO: handle no found
cnf::Clause *cnf::Formula::getClause(int id) {
    return this->clauseSet.find(id)->second;
}

