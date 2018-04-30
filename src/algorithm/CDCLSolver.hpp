//
//  CompleteSolver.hpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef CompleteSolver_hpp
#define CompleteSolver_hpp

#include "Solver.hpp"
#include "Graph.hpp"
#include <set>
#include <queue>

namespace algorithms {
    
    typedef std::unordered_map<int, cnf::Literal> ClauseLiterals;
    
    class CDCLSolver : public Solver {
        
    public:
        
        CDCLSolver() : Solver() {}
        CDCLSolver(std::string outputFile) : Solver(outputFile) {}
        
        // Pure virtual functions
        virtual ~CDCLSolver()                                                                                           = 0;
        virtual void backtrack()                                                                                        = 0; // Backtrack to certain decision level
        virtual void backtrackToStart()                                                                                 = 0; // Backtrack to level 0
        virtual void conflictAnalysis()                                                                                 = 0; // Do conflict analysis
        virtual void updateActivity() = 0;
        virtual void propagate()                                                                                        = 0; // Do unit propagation
        virtual void resolution(ClauseLiterals, ClauseLiterals)     = 0; // Do resoultion between to clauses
        virtual cnf::Variable* pickBranchingVariable()                                                                  = 0; // Pick next decided variable
        
        
        int getGraphSize();
        int getBeta();
        int getDecisionLevel();
        void setBeta(int b);
        void setDecisionLevel(int dl);
        
        
        cnf::Clause * getConflictClause();
        
        bool canBacktrack();
        bool hasUnitClause();
        bool hasUndecidedVariables();
        bool hasConflict();
        
    protected:
        
        int decisionLevel   = 0; // Current decision level
        int beta            = 0; // Current level to backtrack to
        bool output         = false;
        
        
        util::Graph graph;                  // Graph object
        ClauseLiterals learnClauseLiterals; // Learned clause
        ClauseLiterals getLearnedClause();
        std::unordered_map<cnf::Variable*, float> activity;
        // Helper functions
        
        bool isImpliedLiteralAtDesicionLevel(cnf::Clause *c, cnf::Literal l, int d);
        int getAssertionLevel(cnf::Clause *c);
        void addToImplicationGraph(cnf::Variable *v, int decisionLvl, int antecedentClause);
        
        void findUIP(cnf::Clause c1, cnf::Clause reason, int level);
        bool isUIP(ClauseLiterals, int);
        int getAssertionLevel();
        
        // Not used atm
        void addConflict(cnf::Clause *c);
        
        
    private:
        
    
        
        
    };
    

}

#endif /* CompleteSolver_hpp */
