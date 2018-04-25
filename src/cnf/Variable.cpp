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
    auto s = std::to_string(this->key);
    std::string se = "";
    se += s;
    se += " ";
    switch (a) {
        case TRUE:
            se += "T";
            break;
        case FALSE:
            se += "F";
            break;
        case UNASSIGNED:
            se += "U";
            break;
    }
    // std::cout << se << std::endl;
    this->assignment = a;
}

cnf::Variable::~Variable() {
    // std::cout << "Variable pointer ended" << std::endl;
}
