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
    
    // Result returned from unitPropagation
    enum UnitPropagationResult {
        SIMPLIFIED, SOLVED, CONFLICT, NOT_SIMPLIFIED
    };
    
    class CompleteSolver : public Solver {
        
    protected:
        util::Graph graph;
        
        // Helper functions
        
        std::unordered_map<int, cnf::Literal> *convertClauseToMap(cnf::Clause *clause);
        bool isImpliedLiteralAtDesicionLevel(cnf::Literal l, int d);
        
        int getAssertionLevel(std::unordered_map<int, cnf::Literal> *map);
        
        virtual void setup(cnf::Formula formula) = 0;
        virtual bool solve() = 0;
        
    public:
        CompleteSolver() = default;
        virtual ~CompleteSolver() = default;
        
        UnitPropagationResult unitPropagation(int decisionLevel);
        
        
        int conflictAnalysis();
        
        void resolutionOperation(
                                 std::unordered_map<int, cnf::Literal>* tempClauseSet,
                                 cnf::Clause* antecedentClause,
                                 std::queue<cnf::Literal>* q,
                                 std::unordered_map<int, cnf::Literal>* visited,
                                 int decisionLevel);
        
        
        int getGraphSize();
        
    };
    

}

#endif /* CompleteSolver_hpp */
