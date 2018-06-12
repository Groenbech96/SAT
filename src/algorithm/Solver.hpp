//
//  Solver.hpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef Solver_hpp
#define Solver_hpp

#include "Formula.hpp"
#include <string>
#include "Output.hpp"
#include "Config.hpp"

// Virtual Solver Class
// Has to be implemented by derived class

namespace algorithms {
    
    class Solver {
    
    public:
        
        Solver();
        Solver(std::string type, std::string outputFile, bool verbose);
        
        // Pure virtual functions
        virtual ~Solver() = 0;

    protected:
        
        cnf::Formula formula;
        util::Output outputter;
        
        // Pure virtual functions
        virtual void setup(cnf::Formula f) = 0;
        virtual bool solve() = 0;
        bool output;
        bool verbose;
        
    private:
        
        
        
    };
    
}

#endif /* Solver_hpp */
