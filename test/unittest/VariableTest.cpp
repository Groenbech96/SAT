//
//  VariableTest.cpp
//  SatTests
//
// Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 05/03/2018.
// Copyright © 2018 DTU. All rights reserved.
//


#include <gtest/gtest.h>
#include "Variable.hpp"

class VariableFixture : public testing::Test {
    
public:
    int varId = 1;
    
protected:
    
    virtual void SetUp() {
        
        
    }
    
    virtual void TearDown() {
        
    }
    
};

TEST_F(VariableFixture, ConstructorTestWithId) {
    
    cnf::Variable *variable = new cnf::Variable(varId);
    ASSERT_EQ(variable->getAssignment(), cnf::UNASSIGNED);
    
}

TEST_F(VariableFixture, ConstructorTestWithIdAndAssignment) {
    
    auto v1 = new cnf::Variable(varId, cnf::UNASSIGNED);
    auto v2 = new cnf::Variable(varId, cnf::TRUE);
    auto v3 = new cnf::Variable(varId, cnf::FALSE);
    ASSERT_EQ(v1->getAssignment(), cnf::UNASSIGNED);
    ASSERT_EQ(v2->getAssignment(), cnf::TRUE);
    ASSERT_EQ(v3->getAssignment(), cnf::FALSE);
    
    delete v1;
    delete v2;
    delete v3;
}



