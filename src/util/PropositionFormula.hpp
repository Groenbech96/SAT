//
//  PropositionFormula.hpp
//  SAT
//
//  Created by Casper Skjærris on 02/05/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef PropositionFormula_hpp
#define PropositionFormula_hpp

#include <stdio.h>
#include <string>
#include "Formula.hpp"

class PropositionFormula{
    std::string formula;
public:
    PropositionFormula(std::string propFormula) : formula(propFormula) { parse(formula);}
    cnf::Formula convertToCnf();
private:
    void parse(std::string s);
    
};
#endif /* PropositionFormula_hpp */

