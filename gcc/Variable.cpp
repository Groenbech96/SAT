//
//  Variable.cpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 28/02/2018.
//  Copyright © 2018 DTU. All rights reserved.
//


#include "Variable.hpp"
#include <iostream>
#include <string>

cnf::VariableAssignment cnf::Variable::getAssignment() const {
    return this->assignment;
}

int cnf::Variable::getKey() const {
    return this->key;
}

void cnf::Variable::setAssignment(cnf::VariableAssignment a) {
    this->assignment = a;
}

cnf::Variable::~Variable() {
    // std::cout << "Variable pointer ended" << std::endl;
}
