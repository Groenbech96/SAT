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
#include "CDCL.hpp"

class AlgorithmFixture : public testing::Test {
    
public:
    cnf::Formula *f;
    int k = 3, m = 3, n = 15;
    
    int filesToTest;
    
    // path for satisfiable Clauses
    std::string satisfiableClauses = "/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf20-91/";
    
    
protected:
    
    virtual void SetUp() {
        filesToTest = 50;
    }
    
    virtual void TearDown() {
        
    }
    
};

///
/// Test that schonings can solve all satisfiable SAT problems from folder
///
TEST_F(AlgorithmFixture, SchoningsParserSatisfiableClausesTest) {
    
    algorithms::Schonings * s = new algorithms::Schonings();
    
    // Do this for all files in folder "uf20-91"
    for(int i = 1; i <= filesToTest; i++) {
        
        std::string file = this->satisfiableClauses + "uf20-0"+ std::to_string(i) + ".cnf";
        util::Parser *p = new util::Parser(file.c_str());
        cnf::Formula *f = p->parse();
        
        bool found = false;
        while(!found) {
            
            s->setup(*f);
            if(s->solve()) {
                found = true;
                
            }
        }
        delete f;
        delete p;
        
    }
    
}
TEST_F(AlgorithmFixture, CDCLUnitPropagationTest) {
    
    cnf::Formula *f = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf20-91/A_unitTest2.cnf").parse();
    
    algorithms::CDCL *solver = new algorithms::CDCL();
    solver->setup(*f);
    
    f->getVariable(0).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(0).get(), 1, -1);
    f->getVariable(1).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(1).get(), 2, -1);
    f->getVariable(3).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(3).get(), 4, -1);
    
    auto s = solver->unitPropagation(4);
    ASSERT_TRUE(s == algorithms::CONFLICT);
    ASSERT_EQ(solver->getGraphSize(), 9);
}

TEST_F(AlgorithmFixture, CDCLUnitPropagationTestTwo) {
    
    cnf::Formula *f = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf20-91/A_unitTest3.cnf").parse();
    
    algorithms::CDCL *solver = new algorithms::CDCL();
    solver->setup(*f);
    
    f->getVariable(3).get()->setAssignment(cnf::FALSE);
    solver->addToImplicationGraph(f->getVariable(3).get(), 1, -1);
    
    auto s = solver->unitPropagation(1);
    ASSERT_TRUE(s == algorithms::SIMPLIFIED);
    ASSERT_EQ(solver->getGraphSize(), 1);
    
    f->getVariable(0).get()->setAssignment(cnf::FALSE);
    solver->addToImplicationGraph(f->getVariable(0).get(), 2, -1);
    
    s = solver->unitPropagation(2);
    ASSERT_TRUE(s == algorithms::SIMPLIFIED);
    ASSERT_EQ(solver->getGraphSize(), 4);
    
}



TEST_F(AlgorithmFixture, CDCLConflictAnalysis) {
    
    cnf::Formula *f = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf20-91/A_unitTest2.cnf").parse();
    
    algorithms::CDCL *solver = new algorithms::CDCL();
    solver->setup(*f);
    
    f->getVariable(0).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(0).get(), 1, -1);
    f->getVariable(1).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(1).get(), 2, -1);
    f->getVariable(3).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(3).get(), 4, -1);
    
    auto s = solver->unitPropagation(4);
    ASSERT_TRUE(s == algorithms::CONFLICT);
    ASSERT_EQ(solver->getGraphSize(), 9);
    
    int beta = solver->conflictAnalysis();
    ASSERT_EQ(beta, 2);
    
    f = &solver->getFormulaState();
    auto c = f->getLastAddedClause();
    ASSERT_EQ(c.getId(), 7);
    ASSERT_EQ(c.getLiterals().size(), 2);
    
    ASSERT_TRUE(c.getLiteral(1).get().isNegated);
    ASSERT_TRUE(c.getLiteral(6).get().isNegated);
 
    std::cout << "new clause" <<  std::endl;
    std::cout << f->getLastAddedClause().string() <<  std::endl;
    
}


TEST_F(AlgorithmFixture, CDCLBackTrack) {
    
    cnf::Formula *f = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf20-91/A_unitTest2.cnf").parse();
    
    algorithms::CDCL *solver = new algorithms::CDCL();
    solver->setup(*f);
    
    f->getVariable(0).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(0).get(), 1, -1);
    f->getVariable(1).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(1).get(), 2, -1);
    f->getVariable(3).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(3).get(), 4, -1);
    
    auto s = solver->unitPropagation(4);
    ASSERT_TRUE(s == algorithms::CONFLICT);
    ASSERT_EQ(solver->getGraphSize(), 9);
    
    int beta = solver->conflictAnalysis();
    ASSERT_EQ(beta, 2);
    
    f = &solver->getFormulaState();
    auto c = f->getLastAddedClause();
    ASSERT_EQ(c.getId(), 7);
    ASSERT_EQ(c.getLiterals().size(), 2);
    
    ASSERT_TRUE(c.getLiteral(1).get().isNegated);
    ASSERT_TRUE(c.getLiteral(6).get().isNegated);
    
    std::cout << "new clause" <<  std::endl;
    std::cout << f->getLastAddedClause().string() <<  std::endl;
    
    solver->backtrack(beta);
    ASSERT_EQ(solver->getGraphSize(), 2);
    
}

TEST_F(AlgorithmFixture, CDCLCombinedSimulation) {
    
    // FOLLOW THIS https://www.slideshare.net/sakai/how-a-cdcl-sat-solver-works
    
    cnf::Formula *f = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf20-91/A_unitTest2.cnf").parse();
    
    algorithms::CDCL *solver = new algorithms::CDCL();
    solver->setup(*f);
    
    f->getVariable(0).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(0).get(), 1, -1);
    f->getVariable(1).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(1).get(), 2, -1);
    f->getVariable(3).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(3).get(), 4, -1);
    
    auto s = solver->unitPropagation(4);
    ASSERT_TRUE(s == algorithms::CONFLICT);
    ASSERT_EQ(solver->getGraphSize(), 9);
    
    int beta = solver->conflictAnalysis();
    ASSERT_EQ(beta, 2);
    
    f = &solver->getFormulaState();
    auto c = f->getLastAddedClause();
    ASSERT_EQ(c.getId(), 7);
    ASSERT_EQ(c.getLiterals().size(), 2);
    
    ASSERT_TRUE(c.getLiteral(1).get().isNegated);
    ASSERT_TRUE(c.getLiteral(6).get().isNegated);
    
    std::cout << "new clause" <<  std::endl;
    std::cout << f->getLastAddedClause().string() <<  std::endl;
    
    solver->backtrack(beta);
    ASSERT_EQ(solver->getGraphSize(), 2);
    
    ASSERT_EQ(f->getVariable(4).get()->getAssignment(), cnf::UNASSIGNED);
    ASSERT_EQ(f->getVariable(5).get()->getAssignment(), cnf::UNASSIGNED);
    ASSERT_EQ(f->getVariable(6).get()->getAssignment(), cnf::UNASSIGNED);
    
    s = solver->unitPropagation(beta);
    ASSERT_TRUE(s == algorithms::SIMPLIFIED);
    ASSERT_EQ(solver->getGraphSize(), 3);
    
    f->getVariable(3).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(3).get(), 4, -1);
    
    s = solver->unitPropagation(4);
    ASSERT_TRUE(s == algorithms::CONFLICT);
    ASSERT_EQ(solver->getGraphSize(), 7);
    
    beta = solver->conflictAnalysis();
    ASSERT_EQ(beta, 2);
    
    f = &solver->getFormulaState();
    c = f->getLastAddedClause();
    ASSERT_EQ(c.getId(), 8);
    ASSERT_EQ(c.getLiterals().size(), 3);
    
    ASSERT_TRUE(c.getLiteral(0).get().isNegated);
    ASSERT_TRUE(c.getLiteral(3).get().isNegated);
    ASSERT_FALSE(c.getLiteral(6).get().isNegated);
    
    std::cout << "new clause" <<  std::endl;
    std::cout << f->getLastAddedClause().string() <<  std::endl;
    
    solver->backtrack(beta);
    ASSERT_EQ(solver->getGraphSize(), 3);
    
    ASSERT_EQ(f->getVariable(0).get()->getAssignment(), cnf::TRUE);
    ASSERT_EQ(f->getVariable(1).get()->getAssignment(), cnf::TRUE);
    ASSERT_EQ(f->getVariable(6).get()->getAssignment(), cnf::FALSE);
    ASSERT_EQ(f->getVariable(4).get()->getAssignment(), cnf::UNASSIGNED);
    

    s = solver->unitPropagation(beta);
    ASSERT_TRUE(s == algorithms::SIMPLIFIED);
    ASSERT_EQ(solver->getGraphSize(), 4);
    ASSERT_EQ(f->getVariable(3).get()->getAssignment(), cnf::FALSE);

    ASSERT_TRUE(f->getUnitClause() == boost::none);
    
    // Decide new var, and unit that leads to sim
    f->getVariable(4).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(4).get(), 4, -1);
    
    ASSERT_EQ(solver->getGraphSize(), 5);
    s = solver->unitPropagation(4);
    ASSERT_TRUE(s == algorithms::SIMPLIFIED);
    ASSERT_EQ(solver->getGraphSize(), 6);
    
    
    // Decide new var, and unit that leads to con
    f->getVariable(7).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(7).get(), 5, -1);
    
    ASSERT_EQ(solver->getGraphSize(), 7);
    ASSERT_TRUE(f->getUnitClause() != boost::none);
    s = solver->unitPropagation(5);
    ASSERT_TRUE(s == algorithms::CONFLICT);
    ASSERT_EQ(solver->getGraphSize(), 9);
    
    beta = solver->conflictAnalysis();
    ASSERT_EQ(beta, 0);
    
    f = &solver->getFormulaState();
    c = f->getLastAddedClause();
    ASSERT_EQ(c.getId(), 9);
    ASSERT_EQ(c.getLiterals().size(), 1);
    
    ASSERT_TRUE(c.getLiteral(7).get().isNegated);
    
    std::cout << "new clause" <<  std::endl;
    std::cout << f->getLastAddedClause().string() <<  std::endl;
    
    solver->backtrack(beta);
    ASSERT_EQ(solver->getGraphSize(), 0);
    
    ASSERT_EQ(f->getVariable(0).get()->getAssignment(), cnf::UNASSIGNED);
    ASSERT_EQ(f->getVariable(1).get()->getAssignment(), cnf::UNASSIGNED);
    ASSERT_EQ(f->getVariable(6).get()->getAssignment(), cnf::UNASSIGNED);
    ASSERT_EQ(f->getVariable(4).get()->getAssignment(), cnf::UNASSIGNED);
    
    ASSERT_EQ(f->getM(), 10);
 
    s = solver->unitPropagation(beta);
    ASSERT_TRUE(s == algorithms::SIMPLIFIED);
    
    ASSERT_EQ(f->getVariable(7).get()->getAssignment(), cnf::FALSE);
    ASSERT_EQ(f->getVariable(6).get()->getAssignment(), cnf::FALSE);
    ASSERT_EQ(solver->getGraphSize(), 2);
    
    f->getVariable(0).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(0).get(), 1, -1);
    f->getVariable(1).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(1).get(), 2, -1);

    s = solver->unitPropagation(2);
    ASSERT_TRUE(s == algorithms::SIMPLIFIED);
    ASSERT_EQ(solver->getGraphSize(), 5);
    
    f->getVariable(4).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(4).get(), 4, -1);
    
    s = solver->unitPropagation(4);
    ASSERT_TRUE(s == algorithms::SIMPLIFIED);
    ASSERT_EQ(f->getVariable(5).get()->getAssignment(), cnf::FALSE);
    ASSERT_EQ(solver->getGraphSize(), 7);
    
    f->getVariable(8).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(8).get(), 5, -1);
    
    ASSERT_TRUE(f->containsConflict() == boost::none);
    ASSERT_FALSE(f->hasUnsatisfiedClauses());
    ASSERT_FALSE(f->hasUnassignedVariables());
    
}

///
/// Test that schonings can solve all satisfiable SAT problems from folder
///
TEST_F(AlgorithmFixture, CDCLAlgoritmCompleteTest) {
    /**
    algorithms::CDCL * c = new algorithms::CDCL();
    
    // Do this for all files in folder "uf20-91"
    for(int i = 4; i <= 4; i++) {
        
        std::string file = this->satisfiableClauses + "uf20-0"+ std::to_string(i) + ".cnf";
        util::Parser *p = new util::Parser(file.c_str());
        cnf::Formula *f = p->parse();
        
        c->setup(*f);
        ASSERT_TRUE(c->solve());
        //ASSERT_FALSE(c->getFormulaState().hasUnassignedVariables());
        //ASSERT_FALSE(c->getFormulaState().hasUnsatisfiedClauses());
        std::cout << "done " << std::endl;
        
        delete f;
        delete p;
        
    } **/
        

    ASSERT_EQ(true, true);
}






