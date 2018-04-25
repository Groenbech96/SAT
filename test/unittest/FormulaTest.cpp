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
    
    ASSERT_EQ(randomFormula->getClauseSet().size(), m);
}

///
/// Test variable map
///
TEST_F(FormulaFixture, VariableMapTest) {
    
    std::unordered_map<int, cnf::Variable*> vmap;
    for(auto it = randomFormula->getClauseSet().begin(); it != randomFormula->getClauseSet().end(); it++) {
        
        auto clause = it->second;
        
        for(auto itLiteral = clause->getLiterals().begin(); itLiteral != clause->getLiterals().end(); itLiteral++) {
            int idVar = itLiteral->first;
            auto var = itLiteral->second.pVar;
            
            vmap[idVar] = var;
        }
    }
    
    ASSERT_TRUE(vmap.size() == randomFormula->getVariableSet().size());
    
    // check that they contain same elements
    for(auto it = vmap.begin(); it != vmap.end(); ++it) {
        int i = it->first;
        ASSERT_TRUE(randomFormula->getVariableSet().find(i) != randomFormula->getVariableSet().end());
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
    
    cnf::Formula *f = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf20-91/A_updateClauseStates.cnf").parse();
    
    for(auto it = f->getClauseSet().begin(); it != f->getClauseSet().end(); ++it) {
        for(auto it1 = it->second->getLiterals().begin(); it1 != it->second->getLiterals().end(); it1++) {
            it1->second.pVar->setAssignment(it1->second.isNegated ? cnf::FALSE : cnf::TRUE);
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
    
    for(auto it = randomFormula->getVariableSet().begin(); it != randomFormula->getVariableSet().end(); ++it) {
        it->second->setAssignment(cnf::TRUE);
    }
    ASSERT_FALSE(this->randomFormula->hasUnassignedVariables());
}



///
/// Test assignment change
///
TEST_F(FormulaFixture, VariableSetChangeAssignmentTestOne) {
    
    int clauseN = 0;
    int key = randomFormula->getClauseSet().at(clauseN)->getLiterals().begin()->first;
    
    int id = randomFormula->getClauseSet().at(clauseN)->getLiterals().at(key).pVar->getKey();
    ASSERT_EQ(randomFormula->getClauseSet().at(clauseN)->getLiterals().at(key).pVar->getAssignment(), cnf::UNASSIGNED);
    ASSERT_EQ(randomFormula->getVariableSet().at(id)->getAssignment(), cnf::UNASSIGNED);
    
    
    randomFormula->getClauseSet().at(clauseN)->getLiterals().at(key).pVar->setAssignment(cnf::TRUE);
    ASSERT_EQ(randomFormula->getClauseSet().at(clauseN)->getLiterals().at(key).pVar->getAssignment(), cnf::TRUE);
    ASSERT_EQ(randomFormula->getVariableSet().at(id)->getAssignment(), cnf::TRUE);
    
}

///
/// Test assignment change
///
TEST_F(FormulaFixture, VariableSetChangeAssignmentTestTwo) {
    
    
    for(auto it = randomFormula->getVariableSet().begin(); it != randomFormula->getVariableSet().end(); ++it) {
        auto var = it->second;
        ASSERT_EQ(var->getAssignment(), cnf::UNASSIGNED);
        var->setAssignment(cnf::TRUE);
        ASSERT_EQ(randomFormula->getVariableSet().at(var->getKey())->getAssignment(), cnf::TRUE);
    }
    
  
    for(auto var : randomFormula->getVariableSet()) {
        auto v = var.second;
        ASSERT_EQ(v->getAssignment(), cnf::TRUE);
        v->setAssignment(cnf::FALSE);
        ASSERT_EQ(randomFormula->getVariableSet().at(v->getKey())->getAssignment(), cnf::FALSE);
        
    }
    
    
}

///
/// Test getVariable()
///

TEST_F(FormulaFixture, VariableSetGetVariableFromId) {
    
    // Get some id
    int id = randomFormula->getClauseSet().at(0)->getLiterals().begin()->second.pVar->getKey();
    int idNotPresent = randomFormula->getN();
    
    ASSERT_TRUE(randomFormula->getVariable(id) != boost::none);
    ASSERT_EQ(randomFormula->getVariable(id).get()->getKey(), id);
    ASSERT_TRUE(randomFormula->getVariable(idNotPresent) == boost::none);
    
}

TEST_F(FormulaFixture, UpdateClauseStates) {
    
    cnf::Formula *f = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf20-91/A_updateClauseStates.cnf").parse();
    
    f->getVariable(0).get()->setAssignment(cnf::TRUE);
    f->getVariable(1).get()->setAssignment(cnf::TRUE);
    
    auto res = f->updateClauseStates();
    ASSERT_TRUE(res.size() == 2);
    
    ASSERT_TRUE(res[1] == f->getClauseSet().find(1)->second);
    ASSERT_TRUE(res[0] == f->getClauseSet().find(2)->second);
    
    f->getVariable(0).get()->setAssignment(cnf::FALSE);
    
    res = f->updateClauseStates();
    ASSERT_TRUE(res.size() == 0);
    
    f->getVariable(1).get()->setAssignment(cnf::FALSE);
    
    res = f->updateClauseStates();
    ASSERT_TRUE(res.size() == 2);
    ASSERT_TRUE(res[1] == f->getClauseSet().find(0)->second);
    ASSERT_TRUE(res[0] == f->getClauseSet().find(3)->second);
    
}

TEST_F(FormulaFixture, GetUnitClause) {
    
    cnf::Formula *f = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf20-91/A_updateClauseStates.cnf").parse();
    
    f->getVariable(0).get()->setAssignment(cnf::FALSE);
    f->getVariable(1).get()->setAssignment(cnf::FALSE);
    
    auto res = f->getUnitClause();
    ASSERT_TRUE(res != boost::none);
    
    ASSERT_TRUE(res.get() == f->getClauseSet().find(0)->second);
    
    f->getVariable(0).get()->setAssignment(cnf::UNASSIGNED);
    f->getVariable(3).get()->setAssignment(cnf::FALSE);
    
    res = f->getUnitClause();
    ASSERT_TRUE(res != boost::none);
    
    ASSERT_TRUE(res.get() != f->getClauseSet().find(0)->second);
    ASSERT_TRUE(res.get() == f->getClauseSet().find(3)->second);
    
}

TEST_F(FormulaFixture, ContainsConflict) {
    
    cnf::Formula *f = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf20-91/A_updateClauseStates.cnf").parse();
    
    ASSERT_EQ(f->containsConflict(), boost::none);
    
    f->getVariable(0).get()->setAssignment(cnf::FALSE);
    f->getVariable(1).get()->setAssignment(cnf::FALSE);
    f->getVariable(2).get()->setAssignment(cnf::FALSE);
    
    ASSERT_EQ(f->containsConflict().get(), f->getClauseSet().find(0)->second);
    
    f->getVariable(2).get()->setAssignment(cnf::TRUE);
   
    ASSERT_EQ(f->containsConflict(), boost::none);
    
}

TEST_F(FormulaFixture, AddClause) {
    
    cnf::Formula *f = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf20-91/A_updateClauseStates.cnf").parse();
    
    ASSERT_EQ(f->getM(), 4);
    auto l = f->getClauseSet().find(2)->second->getLiterals();
    
    f->addClause(l);
    ASSERT_EQ(f->getM(), 5);
    ASSERT_TRUE(f->getClauseSet().find(4) != f->getClauseSet().end());
    
}


TEST_F(FormulaFixture, FormulaPassedByNonExsitingFile) {
    
    ASSERT_THROW(util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf20-91/nofile.cnf"), util::ParserException);

}


///
/// Test of parsing file
///
TEST_F(FormulaFixture, FormulaPassedByFile) {
    
    this->fileFormula = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf20-91/A_unitTest.cnf").parse();
    
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
        
        auto c = fileFormula->getClauseSet().find(i);
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
