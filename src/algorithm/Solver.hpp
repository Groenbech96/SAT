//
//  Solver.hpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef Solver_hpp
#define Solver_hpp

#include "Formula.hpp"

// Virtual Solver Class
// Has to be implemented by derived class

namespace algorithms {
    
    class Solver {
    
    public:
        
        // Pure virtual functions
        virtual ~Solver() = 0;

    protected:
        
        cnf::Formula _formula;
        
        // Pure virtual functions
        virtual void setup(cnf::Formula f) = 0;
        virtual bool solve() = 0;
        
        
    };
    
}

#endif /* Solver_hpp */
