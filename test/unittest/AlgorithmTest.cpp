//
//  AlgorithmTest.cpp
//  SatTests
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

// Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
// Date: 12/03/2018.
// Copyright (c) 2018 DTU. All rights reserved.
//

#include <gtest/gtest.h>
#include "Parser.hpp"
#include "Schonings.hpp"
#include "DTUSat.hpp"
#include "Variable.hpp"
#include "Clause.hpp"

namespace algorithms {

    std::string cnfPath = "/Users/casperskjaerris/Documents/DTU/4. Semester/Fagprojekt/SAT/data/cnfs/uf20-91";
    std::string cnfPath50 = "/Users/casperskjaerris/Documents/DTU/4. Semester/Fagprojekt/SAT/data/cnfs/uf50-218/";
    std::string cnfTest = "/Users/casperskjaerris/Documents/DTU/4. Semester/Fagprojekt/SAT/data/cnfs/tests/";

class AlgorithmFixture : public testing::Test {
    
public:
    
    int k = 3, m = 3, n = 15;
    
    int filesToTest;
    
    // path for satisfiable Clauses
    std::string satisfiableClauses = cnfPath.c_str();
    
    
protected:
    
    virtual void SetUp() {
        filesToTest = 50;
        
    }
    
    virtual void TearDown() {
        
    }
    
};

    
///
/// Test that schonings can solve more than 50% of satisfiable SAT problems from folder
///
TEST_F(AlgorithmFixture, SchoningSolveRatio) {

    int count = 0;
    for(int j = 1; j <= 1000; j++) {

        std::string file = cnfPath50 + "uf50-0" + std::to_string(j) + ".cnf";
        util::Parser *p = new util::Parser(file.c_str());

        cnf::Formula *f = p->parse();

        algorithms::Schonings *solver = new algorithms::Schonings();
        solver->setup(*f);
        bool res = false;
        res = solver->solve();
        if(res)
            count++;

        delete solver;
        delete p;
        delete f;
    }

    ASSERT_GE(count, 500);
    std::cout  << count;
}


///
/// Test that schonings can solve more than 50% of satisfiable SAT problems from folder
///
TEST_F(AlgorithmFixture, SchoningsParserSatisfiableClausesTest) {



    // Do this for all files in folder "uf20-91"
    int count = 0;
    for(int i = 1; i <= filesToTest; i++) {

        std::string file = this->satisfiableClauses + "/uf20-0"+ std::to_string(i) + ".cnf";
        util::Parser *p = new util::Parser(file.c_str());

        cnf::Formula *f = p->parse();

        algorithms::Schonings *solver = new algorithms::Schonings();
        solver->setup(*f);
        bool res = false;
        res = solver->solve();
        if(res)
            count++;

        delete solver;
        delete p;
        delete f;
    }
    ASSERT_GE(count, filesToTest/2);
    std::cout  << count;
}
    
TEST_F(AlgorithmFixture, CDCLUnitPropagationTest) {
    std::string p = cnfTest +"UnitTestOne.cnf";
    cnf::Formula *f = util::Parser(p.c_str()).parse();
    
    algorithms::DTUSat *solver = new algorithms::DTUSat();
    solver->setup(*f);
    
    f->getVariable(0).get()->setAssignment(cnf::V_TRUE);
    solver->addToImplicationGraph(f->getVariable(0).get(), 1, -1);
    f->getVariable(3).get()->setAssignment(cnf::V_TRUE);
    solver->addToImplicationGraph(f->getVariable(3).get(), 2, -1);
    
    solver->setDecisionLevel(2);
    ASSERT_TRUE(solver->hasUnitClause());
    solver->propagate();
    ASSERT_TRUE(solver->hasConflict());
    ASSERT_EQ(solver->getGraphSize(), 3);
    
    delete f;
    delete solver;
}

TEST_F(AlgorithmFixture, CDCLUnitPropagationTestTwo) {
    
    std::string p = cnfTest +"UnitTestTwo.cnf";
    cnf::Formula *f = util::Parser(p.c_str()).parse();
    
    algorithms::DTUSat *solver = new algorithms::DTUSat();
    solver->setup(*f);
    
    f->getVariable(3).get()->setAssignment(cnf::V_TRUE);
    solver->addToImplicationGraph(f->getVariable(3).get(), 1, -1);
    solver->setDecisionLevel(1);
    
    ASSERT_TRUE(solver->hasUnitClause());
    solver->propagate();
    ASSERT_FALSE(solver->hasConflict());
    ASSERT_EQ(solver->getGraphSize(), 2);
    
    f->getVariable(1).get()->setAssignment(cnf::V_FALSE);
    solver->addToImplicationGraph(f->getVariable(1).get(), 2, -1);
    solver->setDecisionLevel(2);
    
    ASSERT_TRUE(solver->hasUnitClause());
    solver->propagate();
    ASSERT_FALSE(solver->hasConflict());
    ASSERT_EQ(solver->getGraphSize(), 4);
    
    delete f;
    delete solver;
    
}

TEST_F(AlgorithmFixture, CDCLUnitPropagationTestThree) {
    
    std::string p = cnfTest +"UnitTestThree.cnf";
    cnf::Formula *f = util::Parser(p.c_str()).parse();
    
    algorithms::DTUSat *solver = new algorithms::DTUSat();
    solver->setup(*f);
    
    f->getVariable(0).get()->setAssignment(cnf::V_TRUE);
    solver->setDecisionLevel(1);
    solver->addToImplicationGraph(f->getVariable(0).get(), 1, -1);
    
    ASSERT_TRUE(solver->hasUnitClause());
    solver->propagate();
    ASSERT_FALSE(solver->hasConflict());
    ASSERT_EQ(solver->getGraphSize(), 2);
    
    ASSERT_TRUE(solver->hasUnitClause());
    solver->propagate();
    ASSERT_EQ(solver->getGraphSize(), 3);
    ASSERT_TRUE(solver->hasUnitClause());
    
    ASSERT_TRUE(solver->hasUnitClause());
    solver->propagate();
    ASSERT_EQ(solver->getGraphSize(), 4);
    ASSERT_TRUE(solver->hasUnitClause());
    
    ASSERT_TRUE(solver->hasUnitClause());
    solver->propagate();
    ASSERT_EQ(solver->getGraphSize(), 5);
    ASSERT_TRUE(solver->hasUnitClause());
    
    ASSERT_TRUE(solver->hasUnitClause());
    solver->propagate();
    ASSERT_EQ(solver->getGraphSize(), 6);
    ASSERT_FALSE(solver->hasUnitClause());
    
    delete solver;
    delete f;
    
    f = util::Parser(p.c_str()).parse();
    
    solver = new algorithms::DTUSat();
    solver->setup(*f);
    
    f->getVariable(0).get()->setAssignment(cnf::V_TRUE);
    solver->setDecisionLevel(1);
    solver->addToImplicationGraph(f->getVariable(0).get(), 1, -1);
    
    ASSERT_TRUE(solver->hasUnitClause());
    solver->exhaustivePropagate();
    ASSERT_EQ(solver->getGraphSize(), 6);
    ASSERT_FALSE(solver->hasUnitClause());
    
    delete solver;

}

    
TEST_F(AlgorithmFixture, CDCLUnitResolutionTest) {
    std::string p = cnfTest +"ResolutionTest.cnf";
    cnf::Formula *f = util::Parser(p.c_str()).parse();

    
    algorithms::DTUSat *solver = new algorithms::DTUSat();
    solver->setup(*f);
    
    std::unordered_map<int, cnf::Literal> m1;
    std::unordered_map<int, cnf::Literal> m2;
    
    m1.insert(std::make_pair(0, f->getClause(0)->getLiteral(0).get()));
    m1.insert(std::make_pair(1, f->getClause(0)->getLiteral(1).get()));
    
    m2.insert(std::make_pair(0, f->getClause(0)->getLiteral(0).get()));
    m2.insert(std::make_pair(1, f->getClause(1)->getLiteral(1).get()));
    
    
    solver->resolution(m1, m2);
    
    auto m3 = solver->getLearnedClause();
    ASSERT_EQ(m3.size(), 1);
    
    delete f;
    delete solver;
    
}
    
TEST_F(AlgorithmFixture, CDCLUnitResolutionTestTwo) {
    
    cnf::Formula *f = util::Parser("/Users/casperskjaerris/Documents/DTU/4. Semester/Fagprojekt/SAT/data/cnfs/tests/ResolutionTest.cnf").parse();

    
    algorithms::DTUSat *solver = new algorithms::DTUSat();
    solver->setup(*f);
    
    std::unordered_map<int, cnf::Literal> m1;
    std::unordered_map<int, cnf::Literal> m2;
    
    m1.insert(std::make_pair(1, f->getClause(1)->getLiteral(1).get()));
    m1.insert(std::make_pair(3, f->getClause(2)->getLiteral(3).get()));
    m1.insert(std::make_pair(4, f->getClause(3)->getLiteral(4).get()));
    
    m2.insert(std::make_pair(0, f->getClause(0)->getLiteral(0).get()));
    m2.insert(std::make_pair(1, f->getClause(1)->getLiteral(1).get()));
    m2.insert(std::make_pair(3, f->getClause(4)->getLiteral(3).get()));
    
    solver->resolution(m1, m2);
    
    auto m3 = solver->getLearnedClause();
    ASSERT_EQ(m3.size(), 3);
    
    delete f;
    delete solver;
}


TEST_F(AlgorithmFixture, CDCLConflictAnalysisConflicLevel0) {
    //Arrange
    algorithms::DTUSat *solver = new algorithms::DTUSat();
    auto clauseSet = std::unordered_map<int, cnf::Clause*>();
    auto cl = new cnf::Clause(2);
    clauseSet.insert({1,cl});
    auto form = new cnf::Formula(1,1,1, std::unordered_map<int, cnf::Variable *>(), clauseSet);
    solver->setup(*form);
    solver->graph.addVertex(new cnf::Variable(1), 0, 2);
    auto originalClauses = solver->formula.getClauses();
    
    //Act
    solver->conflictAnalysis();
    
    //Assert
    ASSERT_EQ(-1, solver->getBeta());
    ASSERT_EQ(solver->formula.getClauses(), originalClauses);
    
    delete solver;
}
    

    
TEST_F(AlgorithmFixture, CompleteTestA) {
    
    std::string p = cnfTest +"CompleteTestA.cnf";
    cnf::Formula *f = util::Parser(p.c_str()).parse();
    
    algorithms::DTUSat *solver = new algorithms::DTUSat();
    solver->setup(*f);
    bool res = solver->solve();
    
    ASSERT_FALSE(res);
    
    delete f;
    delete solver;
    
}
    
TEST_F(AlgorithmFixture, CompleteTestB) {
 
    //cnf::Formula *f = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/tests/CompleteTestB.cnf").parse();
    
    for(int i = 1; i <= 1000; i++) {
        
        std::string file = this->satisfiableClauses + "/uf20-0" + std::to_string(i) + ".cnf";
        //std::cout << file << std::endl;
        
        cnf::Formula *f = util::Parser(file.c_str()).parse();
        
        algorithms::DTUSat *solver = new algorithms::DTUSat();
        solver->setup(*f);
        bool res = false;
        res = solver->solve();
        
        ASSERT_TRUE(res);
        ASSERT_FALSE(solver->getFormulaState().hasUnsatisfiedClauses());
        
        solver->getFormulaState().clean();
        delete f;
        delete solver;
    }
    
}
    
TEST_F(AlgorithmFixture, CompleteTestC) {
    
    //cnf::Formula *f = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/tests/CompleteTestB.cnf").parse();
    
    for(int i = 1; i <= 1000; i++) {
        this->satisfiableClauses = cnfPath50.c_str();
        std::string file = this->satisfiableClauses + "uf50-0" + std::to_string(i) + ".cnf";
        
        cnf::Formula *f = util::Parser(file.c_str()).parse();
        
        algorithms::DTUSat *solver = new algorithms::DTUSat();
        solver->setup(*f);
        bool res = false;
        res = solver->solve();
        
        ASSERT_TRUE(res);
        ASSERT_FALSE(solver->getFormulaState().hasUnsatisfiedClauses());
        delete f;
        delete solver;
    }
    
}
    
    
TEST_F(AlgorithmFixture, OutputTest) {
    
    for(int i = 1; i <= 5; i++) {
        
        std::string file = this->satisfiableClauses + "/uf20-0" + std::to_string(i) + ".cnf";
        
        cnf::Formula *f = util::Parser(file.c_str()).parse();
        
        algorithms::DTUSat *solver = new algorithms::DTUSat();
        solver->setup(*f);
        bool res = false;
        res = solver->solve();
        
        ASSERT_TRUE(res);
        ASSERT_FALSE(solver->getFormulaState().hasUnsatisfiedClauses());
        
        delete f;
        delete solver;
    }
    
}
    
TEST_F(AlgorithmFixture, CDCLUndoDecidedVar) {
    //Arrange
    auto solver = new algorithms::DTUSat();
    solver->graph.addVertex(new cnf::Variable(1), 1, -1);
    solver->graph.addVertex(new cnf::Variable(2), 2, -1);
    solver->setBeta(1);
    
    //Act
    solver->backtrack();
    
    //Assert
    ASSERT_EQ(1, solver->getGraphSize());
    
    delete solver;
}


} // namespace






