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
        
        void pickBranchingVariable(int decisionLevel);
        
        void backtrack(int beta);
        
        void printGraph();
        
    
        
        
        
    };
    
}


#endif /* CDCL_hpp */
