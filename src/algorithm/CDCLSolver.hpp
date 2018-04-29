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
    
    class CDCLSolver : virtual public Solver {
        
    public:
        
        // Pure virtual functions
        virtual ~CDCLSolver()                                                                                           = 0;
        virtual void backtrack()                                                                                        = 0; // Backtrack to certain decision level
        virtual void backtrackToStart()                                                                                 = 0; // Backtrack to level 0
        virtual void conflictAnalysis()                                                                                 = 0; // Do conflict analysis
        virtual void propagate()                                                                                        = 0; // Do unit propagation
        virtual void resolution(ClauseLiterals, ClauseLiterals)     = 0; // Do resoultion between to clauses
        virtual cnf::Variable* pickBranchingVariable()                                                                  = 0; // Pick next decided variable
        
        int getGraphSize();
        
        int getBeta();
        void setBeta(int b);
        int getDecisionLevel();
        void setDecisionLevel(int dl);
        
        
        cnf::Clause * getConflictClause();
        
        bool canBacktrack();
        bool hasUnitClause();
        bool hasUndecidedVariables();
        bool hasConflict();
        
    protected:
        
        int decisionLevel   = 0; // Current decision level
        int beta            = 0; // Current level to backtrack to
        
        util::Graph graph;                  // Graph object
        ClauseLiterals learnClauseLiterals; // Learned clause
        ClauseLiterals getLearnedClause();
        
        // Helper functions
        
        bool isImpliedLiteralAtDesicionLevel(cnf::Clause *c, cnf::Literal l, int d);
        int getAssertionLevel(cnf::Clause *c);
        void addToImplicationGraph(cnf::Variable *v, int decisionLvl, int antecedentClause);
        void addConflict(cnf::Clause *c);
        void findUIP(cnf::Clause c1, cnf::Clause reason, int level);
        bool isUIP(ClauseLiterals, int);
        int getAssertionLevel();
        
    private:
        // Used for internal structure
        bool conflictClauseUpdated;
    
        
        
    };
    

}

#endif /* CompleteSolver_hpp */
