//
//  ProbabilisticSolver.hpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef ProbabilisticSolver_hpp
#define ProbabilisticSolver_hpp

#include "Solver.hpp"

namespace algorithms {
    
    class ProbabilisticSolver : virtual public Solver {

    public:
        ProbabilisticSolver() : Solver() {};
        virtual ~ProbabilisticSolver() = 0;
        
        
    protected:
        /// Vector containing unsatisfied_clauses
        std::vector<cnf::Clause *> unsatisfied_clauses;
        
    };
}
#endif /* ProbabilisticSolver_hpp */
