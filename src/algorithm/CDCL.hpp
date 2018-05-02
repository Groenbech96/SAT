//
//  CDCL.hpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef CDCL_hpp
#define CDCL_hpp

#include "CDCLSolver.hpp"

namespace algorithms {
    
    class DTUSat : public CDCLSolver {
        
    public:
        DTUSat() { std::cout << "init CDCL" << std::endl; }
        ~DTUSat()  = default;
        
        void setup(cnf::Formula formula) override;
        bool solve() override;
        
        
        
        
        cnf::Variable* pickBranchingVariable();
        
        
        
        // void printGraph();
        
        void addToImplicationGraph(cnf::Variable *v, int decisionLvl, int antecedentClause);
        
        cnf::Formula & getFormulaState();
        
    private:
        
        
        cnf::Clause resolution();
        void backtrack(int beta);
        void backtrackToStart();
        
        
        
    };
    
}


#endif /* CDCL_hpp */
