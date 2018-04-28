//
//  CDCL.hpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef CDCL_hpp
#define CDCL_hpp

#include "CDCLSolver.hpp"

#ifdef ADDTEST
    #include "gtest/gtest_prod.h"
#endif

#include <stack>

namespace algorithms {
    
    
    
    class DTUSat : public CDCLSolver {
        
    public:
        DTUSat() = default;
        ~DTUSat()  = default;
        
        void setup(cnf::Formula formula) override;
        bool solve() override;
        
        //void printGraph();
        
        
        
        cnf::Formula & getFormulaState();
        ClauseLiterals getLearnedClause();
        
    private:
        
        // Google test private method access
#ifdef ADDTEST
        FRIEND_TEST(AlgorithmFixture, CDCLUnitPropagationTest);
        FRIEND_TEST(AlgorithmFixture, CDCLUnitPropagationTestTwo);
        FRIEND_TEST(AlgorithmFixture, CDCLUnitResolutionTest);
        FRIEND_TEST(AlgorithmFixture, CDCLConflictAnalysis);
        FRIEND_TEST(AlgorithmFixture, CDCLUnitPropagationTestThree);
        FRIEND_TEST(AlgorithmFixture, CDCLBackTrack);
        FRIEND_TEST(AlgorithmFixture, CDCLResolutionOperationTest);
        FRIEND_TEST(AlgorithmFixture, CDCLUndoDecidedVar);
#endif
        
        // std::queue<int> assignments;
        ClauseLiterals learnClauseLiterals;
    
        void backtrack() override;
        void backtrackToStart() override;
        void conflictAnalysis() override;
        void resolution(ClauseLiterals, ClauseLiterals) override;
        cnf::Variable* pickBranchingVariable() override;
        void propagate() override;
        void exhaustivePropagate();
        void addToImplicationGraph(cnf::Variable *v, int decisionLvl, int antecedentClause);
        void addConflict(cnf::Clause *c);
        void findUIP(cnf::Clause c1, cnf::Clause reason, int level);
        
        bool hasConflict() override;
        void learn(int i);
        
        bool isUIP(ClauseLiterals, int);
        int getAssertionLevel();
        void print(std::stack<cnf::Variable*> s);
        
    };
    
}


#endif /* CDCL_hpp */
