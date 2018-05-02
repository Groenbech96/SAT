//
//  ClauseTest.cpp
//  SatTests
//
// Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 04/03/2018.
// Copyright © 2018 DTU. All rights reserved.
//


#include <gtest/gtest.h>
#include "Clause.hpp"

class ClauseFixture : public testing::Test {
    
public:
    int Clause_ID = 1;
    std::unordered_map<int, cnf::Literal> literals;
    
protected:
    
    virtual void SetUp() {
        for(int i = 0; i < 3; i++) {
            
            auto v = new cnf::Variable(i);
            cnf::Literal literal = {v, false};
            
            literals.insert({i, literal});
        }
    }
    
    virtual void TearDown() {
        
        for(auto i : literals) {
            delete i.second.pVar;
        }
        literals.empty();
        
    }
    
};


///
/// Test constructor
///
TEST_F(ClauseFixture, ConstructorTest)
{
    auto clause = new cnf::Clause(Clause_ID, literals);
    
    ASSERT_EQ(clause->getId(), Clause_ID);
    ASSERT_EQ(clause->getLiterals().size(), literals.size());
}

///
/// Test that a new clause is not satisfied by default and still is if no variables have been set
///
TEST_F(ClauseFixture, UnassignedClauseTest)
{
    auto clause = new cnf::Clause(Clause_ID, literals);
    
    ASSERT_FALSE(clause->isSatisfied());
    // No variables have been set: clause must then still be false
    clause->evaluate();
    ASSERT_FALSE(clause->isSatisfied());
}

///
/// Test that clause evaulates correcly
///
TEST_F(ClauseFixture, AssignedClauseTest)
{
    auto clause = new cnf::Clause(Clause_ID, literals);
    ASSERT_FALSE(clause->isSatisfied());
    // Literals are not negated in this test
    literals.at(0).pVar->setAssignment(cnf::V_TRUE);
    
    // First variables have been set: clause must then still be false
    clause->evaluate();
    ASSERT_TRUE(clause->isSatisfied());
    
    // Make sure that clause state dont change if we dont call evaluate
    literals.at(0).pVar->setAssignment(cnf::V_FALSE);
    ASSERT_FALSE(clause->isSatisfied());
    
    
    literals.at(0).pVar->setAssignment(cnf::V_TRUE);
    literals.at(1).pVar->setAssignment(cnf::V_TRUE);
    clause->evaluate();
    ASSERT_TRUE(clause->isSatisfied());
    
    literals.at(0).pVar->setAssignment(cnf::V_FALSE);
    literals.at(1).pVar->setAssignment(cnf::V_FALSE);
    literals.at(2).pVar->setAssignment(cnf::V_FALSE);
    clause->evaluate();
    ASSERT_FALSE(clause->isSatisfied());
}


TEST_F(ClauseFixture, GetLiteralTest) {
    
    auto clause = new cnf::Clause(Clause_ID, literals);
    
    auto p = clause->getLiteral(11);

    ASSERT_TRUE(p == boost::none);
    
    auto p1 = clause->getLiteral(1);
    ASSERT_TRUE(p1 != boost::none);
    
    
}



