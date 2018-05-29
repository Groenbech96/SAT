//
//  Schonings.hpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 17/04/2018.
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
        Schonings(std::string type, std::string outputFile, bool verbose) : ProbabilisticSolver(type, outputFile, verbose) {}
        ~Schonings() = default;
        
        /// Setup a formula to solve
        void setup(cnf::Formula formula) override;
    
        /// Solve method for Schonings
        bool solve() override;
       
    private:
      
    };
    
}

#endif /* Schonings_hpp */
