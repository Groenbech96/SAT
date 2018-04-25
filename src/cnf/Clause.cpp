//
//  Clause.cpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 28/02/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include "Clause.hpp"


void cnf::Clause::evaluate() {
    
    bool SAT = false;
    int unitLiteralKey = -1;
    
    int noOfUnassignedLiterals = 0;
    
    for(auto kv : this->literals) {
        VariableAssignment a = kv.second.pVar->getAssignment();
        bool n = kv.second.isNegated;
        
        if (a == cnf::UNASSIGNED) {
            noOfUnassignedLiterals++;
            unitLiteralKey = kv.first;
        }
        
        if((n && a == VariableAssignment::FALSE) || (!n && a == VariableAssignment::TRUE)) {
            // We know that the clause is true (disjunction property)
            SAT = true;
            break;
        }
    }
    
    if (noOfUnassignedLiterals == 1 && !SAT) {
        this->unitLiteralKey = unitLiteralKey;
    } else {
        this->unitLiteralKey = -1;
    }
    
    this->conflict = (noOfUnassignedLiterals == 0 && !SAT);
    this->satisfied = SAT;
}

int cnf::Clause::getId() const {
    return this->id;
}

bool cnf::Clause::isSatisfied() {
    // make sure that clause is up to date
    this->evaluate();
    return this->satisfied;
}

bool cnf::Clause::isUnit() {
    this->evaluate();
    return this->unitLiteralKey != -1;
}


cnf::Clause::~Clause() {
    // std::cout << "Clause pointer ended" << std::endl;
}

std::unordered_map<int, cnf::Literal> &cnf::Clause::getLiterals() {
    return this->literals;
}

boost::optional<cnf::Literal&> cnf::Clause::getLiteral(int id) {
    auto p = this->literals.find(id);
    
    if(p != this->literals.end()) {
        return p->second;
    } else {
        return boost::none;
    }
    
}

bool cnf::Clause::containsConflict() {
    this->evaluate();
    return this->conflict;
}

std::string cnf::Clause::string() {
    std::string s = " (";
    for(auto kv : this->literals) {
        VariableAssignment a = kv.second.pVar->getAssignment();
        int varID = kv.second.pVar->getKey();
        
        if(kv.second.isNegated) {s+="-";}
        if(a == UNASSIGNED) {s+="U";}
        else if (a == FALSE) {s+="F";}
        else {s+="T";}
        
        s+= "(" + std::to_string(varID) + ") ";
    }
    
    s += ") ";
    
    return s;
}

boost::optional<cnf::Literal> cnf::Clause::getUnitLiteral() {
    auto l = this->literals.find(unitLiteralKey);
    if(l!=this->literals.end()) {
        return l->second;
    }
    return boost::none;
}

void cnf::Clause::removeLiteral(int id) {
    this->literals.erase(id);
}


