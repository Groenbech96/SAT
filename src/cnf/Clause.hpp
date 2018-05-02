//
//  Clause.hpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 28/02/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef Clause_hpp
#define Clause_hpp

#include <vector>
#include <unordered_map>
#include <boost/optional.hpp>
#include "Literal.h"
#include <iostream>
#include <string>


namespace cnf {
    /// CNF Clause
    class Clause {
        
    public:
        
        //
        // General Methods
        //
        
        Clause() = default;
        ~Clause();
        
        /// Create a new clause
        /// \param id of the clause (e.g placement in the Formula)
        /// \param literals that are in this clause
        Clause(int id, std::unordered_map<int, Literal> literals) : id(id), literals(literals), satisfied(false) {}
        
        /// Create a new clause
        /// \param id of the clause (e.g placement in the Formula)
        Clause(int id) : id(id), satisfied(false) {}
        
        /// Return map of literals in the clause
        /// \return the map
        std::unordered_map<int, Literal> &getLiterals();
        
        /// Return the literal if present
        /// \param id of item
        /// \return boost none or literal
        ///
        /// Example: auto p = literals.getLiteral(x)
        ///          if(p != boost::none) { found }
        boost::optional<Literal&> getLiteral(int id);
        
        /// True if clause is satisfied by current variable assignment
        /// \return bool
        bool isSatisfied();
        bool isUnit();
        bool containsConflict();
        boost::optional<Literal> getUnitLiteral();
        
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
        
        
        /// Updates the clause state to either satisfied or unsatisfied
        void evaluate();
        
        
    private:
        
        /// Flag true if clause is satisfied
        bool satisfied;
        bool unit;
        int unitLiteralKey;
        bool conflict;
        
        /// Id for this clause
        int id;
        
        /// Literals inside clause
        std::unordered_map<int, Literal> literals;
        
    };
}


#endif /* Clause_hpp */
