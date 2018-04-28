//
//  Schonings.hpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef Schonings_hpp
#define Schonings_hpp

#include "ProbabilisticSolver.hpp"
#include "Randomizer.h"

namespace algorithms {
    
    class Schonings : public ProbabilisticSolver {
        
    public:
        Schonings() : ProbabilisticSolver() {}
        ~Schonings() = default;
        
        /// Setup a formula to solve
        void setup(cnf::Formula formula) override;
    
        /// Solve method for Schonings
        bool solve() override;
       
    private:
        
        
    };
    
}

#endif /* Schonings_hpp */
