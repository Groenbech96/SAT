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
#include <map>

namespace algorithms {
    
    class Solver {
    
    public:
        
        Solver() = default;
        virtual ~Solver() = default;
        
        // Need to be implemented
        virtual void setup(cnf::Formula formula) = 0;
        virtual bool solve() = 0;
        
        
    protected:
        cnf::Formula formula;
        std::vector<int> assignment;
        /// List containing unsatisfied_clauses
        std::vector<cnf::Clause *> unsatisfied_clauses;
    
    
    
    };
    
}

#endif /* Solver_hpp */
