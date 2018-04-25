//
//  CDCL.hpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef CDCL_hpp
#define CDCL_hpp

#include "CompleteSolver.hpp"

namespace algorithms {
    
    class CDCL : public CompleteSolver {
        
    public:
        CDCL()   = default;
        ~CDCL()  = default;
        
        void setup(cnf::Formula formula) override;
        bool solve() override;
        
        cnf::Variable* pickBranchingVariable();
        
        void backtrack(int beta);
        
        void printGraph();
        
        void addToImplicationGraph(cnf::Variable *v, int decisionLvl, int antecedentClause);
        
        cnf::Formula & getFormulaState();
        
    private:
        
        
        
    };
    
}


#endif /* CDCL_hpp */
