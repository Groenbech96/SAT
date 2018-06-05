//
//  PropositionOperator.h
//  SAT
//
//  Created by Casper Skjærris on 02/05/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef PropositionOperator_h
#define PropositionOperator_h
#include "Literal.h"

enum Operator{
    AND, OR, IMPLICATION, BI_IMPLICATION
};

class PropositionalOperator {
    
    public:
        PropositionalOperator() = default;
        virtual ~PropositionalOperator();
    
    private:
        cnf::Literal lhs;
        cnf::Literal rhs;
        Operator op;
};

#endif /* PropositionOperator_h */
