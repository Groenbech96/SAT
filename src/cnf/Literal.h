//
//  Literal.h
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 28/02/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef Literal_h
#define Literal_h

#include "Variable.hpp"

namespace cnf {
    
    ///
    /// Literal consist of two tings
    /// A pointer to a variable in the formula
    /// A flag that is true if literal is negated in formula
    ///
    struct Literal {
        Variable * pVar;
        bool isNegated;
    };
    
}

#endif /* Literal_h */
