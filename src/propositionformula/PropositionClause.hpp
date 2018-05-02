//
//  PropositionClause.hpp
//  SAT
//
//  Created by Casper Skjærris on 02/05/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef PropositionClause_hpp
#define PropositionClause_hpp

#include <stdio.h>
#include <unordered_map>
#include "Literal.h"

class PropositionalClause {
    
public:
    
    //
    // General Methods
    //
    
    PropositionalClause() = default;
    ~PropositionalClause();
    
    /// Create a new clause
    /// \param id of the clause (e.g placement in the Formula)
    /// \param literals that are in this clause
    PropositionalClause(int id, std::unordered_map<int, cnf::Literal> literals) : id(id), literals(literals) {}
    
    /// Create a new clause
    /// \param id of the clause (e.g placement in the Formula)
    PropositionalClause(int id) : id(id) {}
    
    /// Return map of literals in the clause
    /// \return the map
    std::unordered_map<int, cnf::Literal> &getLiterals();
    
    /// Return the literal if present
    /// \param id of item
    /// \return boost none or literal
    ///
    /// Example: auto p = literals.getLiteral(x)
    ///          if(p != boost::none) { found }
    cnf::Literal& getLiteral(int id);

    
    bool containsLiteral(cnf::Literal l);
    
    
    //
    // Getter and setter methods
    //
    
    /// Return id
    int getId() const;
    
    /// Textual representation of the clause for testing/debugging purposes.
    /// \return String containing representations of all literals in the formula.
    ///
    std::string string();
    
    void addLiteral();
    void removeLiteral(int id);

private:
    
    /// Id for this clause
    int id;
    
    /// Literals inside clause
    std::unordered_map<int, cnf::Literal> literals;
    
};

#endif /* PropositionClause_hpp */
