//
//  FormulaTest.cpp
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
#include <queue>
#include "Parser.hpp"
#include "Formula.hpp"

class FormulaFixture : public testing::Test {
    
public:
    // This formula is created uar
    cnf::Formula *randomFormula;
    int k = 3, m = 3, n = 4;
    
    // This formula is created by parsing a file
    cnf::Formula *fileFormula;
    
protected:
    
    virtual void SetUp() {
        randomFormula = new cnf::Formula(k,m,n);
    }
    
    virtual void TearDown() {
        delete randomFormula;
    }
    
};

///
/// Test constructor
///
TEST_F(FormulaFixture, ConstructorTest) {
    
    ASSERT_EQ(randomFormula->getK(), k);
    ASSERT_EQ(randomFormula->getM(), m);
    ASSERT_EQ(randomFormula->getN(), n);
    
    ASSERT_EQ(randomFormula->getClauses().size(), m);
}

///
/// Test variable map
///
TEST_F(FormulaFixture, VariableMapTest) {
    
    std::unordered_map<int, cnf::Variable*> vmap;
    for(auto it = randomFormula->getClauses().begin(); it != randomFormula->getClauses().end(); it++) {
        
        auto clause = it->second;
        
        for(auto itLiteral = clause->getLiterals().begin(); itLiteral != clause->getLiterals().end(); itLiteral++) {
            int idVar = itLiteral->first;
            auto var = itLiteral->second.pVar;
            
            vmap[idVar] = var;
        }
    }
    
    ASSERT_TRUE(vmap.size() == randomFormula->getVariables().size());
    
    // check that they contain same elements
    for(auto it = vmap.begin(); it != vmap.end(); ++it) {
        int i = it->first;
        ASSERT_TRUE(randomFormula->getVariables().find(i) != randomFormula->getVariables().end());
    }
}

///
/// Test unassigned Clauses
///
TEST_F(FormulaFixture, UnassignedClauses) {
    ASSERT_TRUE(this->randomFormula->hasUnsatisfiedClauses());
}


///
/// Test unassigned Variables
///
TEST_F(FormulaFixture, NoUnassignedClauses) {
    
    cnf::Formula *f = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/tests/ClauseStates.cnf").parse();
    
    for(auto it = f->getClauses().begin(); it != f->getClauses().end(); ++it) {
        for(auto it1 = it->second->getLiterals().begin(); it1 != it->second->getLiterals().end(); it1++) {
            it1->second.pVar->setAssignment(it1->second.isNegated ? cnf::V_FALSE : cnf::V_TRUE);
        }

    }
    ASSERT_FALSE(f->hasUnsatisfiedClauses());
}

///
/// Test unassigned Variables
///
TEST_F(FormulaFixture, UnassignedVariables) {
    ASSERT_TRUE(this->randomFormula->hasUnassignedVariables());
}

///
/// Test unassigned Variables
///
TEST_F(FormulaFixture, NoUnassignedVariables) {
    
    for(auto it = randomFormula->getVariables().begin(); it != randomFormula->getVariables().end(); it++) {
        it->second->setAssignment(cnf::V_TRUE);
    }
    ASSERT_FALSE(this->randomFormula->hasUnassignedVariables());
}



///
/// Test assignment change
///
TEST_F(FormulaFixture, VariableSetChangeAssignmentTestOne) {
    
    int clauseN = 0;
    int key = randomFormula->getClauses().at(clauseN)->getLiterals().begin()->first;
    
    int id = randomFormula->getClauses().at(clauseN)->getLiterals().at(key).pVar->getKey();
    ASSERT_EQ(randomFormula->getClauses().at(clauseN)->getLiterals().at(key).pVar->getAssignment(), cnf::UNASSIGNED);
    ASSERT_EQ(randomFormula->getVariables().at(id)->getAssignment(), cnf::UNASSIGNED);
    
    
    randomFormula->getClauses().at(clauseN)->getLiterals().at(key).pVar->setAssignment(cnf::V_TRUE);
    ASSERT_EQ(randomFormula->getClauses().at(clauseN)->getLiterals().at(key).pVar->getAssignment(), cnf::V_TRUE);
    ASSERT_EQ(randomFormula->getVariables().at(id)->getAssignment(), cnf::V_TRUE);
    
}

///
/// Test assignment change
///
TEST_F(FormulaFixture, VariableSetChangeAssignmentTestTwo) {
    
    
    for(auto it = randomFormula->getVariables().begin(); it != randomFormula->getVariables().end(); ++it) {
        auto var = it->second;
        ASSERT_EQ(var->getAssignment(), cnf::UNASSIGNED);
        var->setAssignment(cnf::V_TRUE);
        ASSERT_EQ(randomFormula->getVariables().at(var->getKey())->getAssignment(), cnf::V_TRUE);
    }
    
  
    for(auto var : randomFormula->getVariables()) {
        auto v = var.second;
        ASSERT_EQ(v->getAssignment(), cnf::V_TRUE);
        v->setAssignment(cnf::V_FALSE);
        ASSERT_EQ(randomFormula->getVariables().at(v->getKey())->getAssignment(), cnf::V_FALSE);
        
    }
    
    
}

///
/// Test getVariable()
///

TEST_F(FormulaFixture, VariableSetGetVariableFromId) {
    
    // Get some id
    int id = randomFormula->getClauses().at(0)->getLiterals().begin()->second.pVar->getKey();
    int idNotPresent = randomFormula->getN();
    
    ASSERT_TRUE(randomFormula->getVariable(id) != boost::none);
    ASSERT_EQ(randomFormula->getVariable(id).get()->getKey(), id);
    ASSERT_TRUE(randomFormula->getVariable(idNotPresent) == boost::none);
    
}

TEST_F(FormulaFixture, UpdateClauseStates) {
    
    cnf::Formula *f = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/tests/ClauseStates.cnf").parse();
    
    f->getVariable(0).get()->setAssignment(cnf::V_TRUE);
    f->getVariable(1).get()->setAssignment(cnf::V_TRUE);
    
    auto res = f->updateClauseStates();
    ASSERT_TRUE(res.size() == 3);
    
    f->getVariable(0).get()->setAssignment(cnf::V_FALSE);
    
    res = f->updateClauseStates();
    ASSERT_TRUE(res.size() == 0);
    
}

TEST_F(FormulaFixture, GetUnitClause) {
    
    cnf::Formula *f = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/tests/ClauseStatesUnit.cnf").parse();
    
    f->getVariable(0).get()->setAssignment(cnf::V_TRUE);
    f->getVariable(1).get()->setAssignment(cnf::V_TRUE);
    
    ASSERT_TRUE(f->hasUnitClause());
    ASSERT_EQ(f->getUnitClause(), f->getClause(0));
    
    f->getVariable(0).get()->setAssignment(cnf::UNASSIGNED);
    f->getVariable(2).get()->setAssignment(cnf::V_TRUE);
    
    ASSERT_TRUE(f->hasUnitClause());
    ASSERT_EQ(f->getUnitClause(), f->getClause(0));
    
}

TEST_F(FormulaFixture, ContainsConflict) {
    
    cnf::Formula *f = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/tests/ClauseStates.cnf").parse();
    
    
    ASSERT_FALSE(f->hasConflictClause());
    
    f->getVariable(0).get()->setAssignment(cnf::V_TRUE);
    f->getVariable(1).get()->setAssignment(cnf::V_TRUE);
    f->getVariable(2).get()->setAssignment(cnf::V_TRUE);
    
    ASSERT_TRUE(f->hasConflictClause());
    ASSERT_EQ(f->getConflictClause(), f->getClause(0));
    
    f->getVariable(2).get()->setAssignment(cnf::V_FALSE);
   
    ASSERT_TRUE(f->hasConflictClause());
    ASSERT_EQ(f->getConflictClause(), f->getClause(2));
    
}

TEST_F(FormulaFixture, AddClause) {
    
    cnf::Formula *f = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/tests/ClauseStates.cnf").parse();
    
    ASSERT_EQ(f->getM(), 3);
    auto l = f->getClauses().find(2)->second->getLiterals();
    
    f->addClause(l);
    ASSERT_EQ(f->getM(), 4);
    ASSERT_TRUE(f->getClauses().find(3) != f->getClauses().end());
    
}


TEST_F(FormulaFixture, FormulaPassedByNonExsitingFile) {
    
    ASSERT_THROW(util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/tests/nofile.cnf"), util::ParserException);

}


///
/// Test of parsing file
///
TEST_F(FormulaFixture, FormulaPassedByFile) {
    
    this->fileFormula = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/tests/ParseTest.cnf").parse();
    
    ASSERT_TRUE(this->fileFormula->getN() == 5);
    ASSERT_TRUE(this->fileFormula->getM() == 5);
    
    std::queue<std::vector<int>> elements;
    std::vector<int> w1 {0,1,2};
    std::vector<int> w2 {0,1,2};
    std::vector<int> w3 {3,3,3};
    std::vector<int> w4 {4,4,4};
    std::vector<int> w5 {-4,-3,-2};
    
    elements.push(w1);
    elements.push(w2);
    elements.push(w3);
    elements.push(w4);
    elements.push(w5);
    
    for(int i = 0; i < 5; i++) {
        
        auto c = fileFormula->getClauses().find(i);
        std::vector<int> e = elements.front();
        for(auto itClause = c->second->getLiterals().begin(); itClause != c->second->getLiterals().end(); ++itClause) {
            
            int id = itClause->second.pVar->getKey();
            if(itClause->second.isNegated) {
                ASSERT_TRUE(std::find(e.begin(), e.end(), -id) != e.end());
            } else {
                ASSERT_TRUE(std::find(e.begin(), e.end(), id) != e.end());
            }
            
        }
        elements.pop();
        
    }
    
    delete fileFormula;
    
}
