//
//  Formula.hpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 28/02/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef Formula_hpp
#define Formula_hpp

#include <unordered_map>
#include <unordered_set>
#include <list>
#include "Clause.hpp"
#include "Randomizer.h"

namespace cnf {
    
    /// A CNF-Formula
    class Formula {
        
    public:
        
        /// Default constructor
        Formula()  = default;
        ~Formula() = default;
        
        /// Create a formula u.a.r
        /// \param k defines sat type
        /// \param m defines number of clauses
        /// \param n defines number of available variables
        Formula(int k, int m, int n);
        
        /// Create a formula based on parsing
        /// \param k defines sat type
        /// \param m defines number of clauses
        /// \param n defines number of available variables
        /// \param variableSet - map of variables
        /// \param clauses - vector of clauses
        Formula(int k, int m, int n, std::unordered_map<int, cnf::Variable *> variableSet, std::unordered_map<int, cnf::Clause *> clauses);
        
        /// Get sat type (size of clauses)
        /// \return k
        int getK();
        
        /// Get number of clauses
        /// \return m
        int getM();
        
        /// Get number of variables in formula
        /// \return n
        int getN();
        
        /// Log formula
        void log();
        
        /// Get variable with id
        /// Can return boost::none if not found in formula
        ///
        /// Example: auto p = literals.getLiteral(x)
        ///          if(p != boost::none) { found }
        boost::optional<cnf::Variable *> getVariable(int id);
        
        /// Get the variables as a map
        /// \return unordered map
        std::unordered_map<int, Variable *> &getVariables();
        
        /// Return vector of cluases
        /// \return clauses
        std::unordered_map<int, Clause *> & getClauses();
        
        Clause * getClause(int id);
        
        
        /// Update all clauses
        /// \return list of unsatisfied clauses
        std::vector<Clause *> updateClauseStates();
        
        /**
         * Has the formula unassigned variables
         * @return true if one or more is unassigned
         */
        bool hasUnassignedVariables();
        
        
        ///
        /// @return A unit clause if one exists
        /// @depricated
        ///
        //boost::optional<Clause *> getUnitClause();
        
        ///
        /// @return All unsatisfied clauses (if any)
        ///
        bool hasUnsatisfiedClauses();
        
        /// Evaluates if the formula contains any unsatisfied clauses with no unassigned literals
        /// @return True if any clauses contains conflicts. False otherwise.
        ///
        boost::optional<Clause *> containsConflict();
        
        /// Evaluates if the formula contains a conflict clause
        bool hasConflictClause();
        
        /// Gets the most recent found conflict clause
        cnf::Clause* getConflictClause();
        
        /// Evaluates if the formula contains a unit clause
        bool hasUnitClause();
        
        /// Gets the most recent found conflict clause
        cnf::Clause* getUnitClause();
        
        
        
        
        
        
        /// Textual representation of the formula for testing/debugging purposes.
        /// @return String containing representations of all clauses in the formula.
        ///
        std::string string();
        
        void addClause(std::unordered_map<int, Literal> l);
        cnf::Clause* addClause();
        
        Clause & getLastAddedClause();
        
    private:
        /**
         * SAT type
         */
        int k;
        
        /**
         * Number of clauses in formula
         */
        int m;
        
        /**
         * Number of variables in variable pool available to formula
         */
        int n;
        
        /**
         * Set of clauses is formula
         * Is in incremental order
         */
        std::unordered_map<int, Clause *> clauseSet;
        
        /**
         * Map of variables in formula
         * Key -> Id (e.g: X4 -> key(4))
         * Value -> Variable X4
         */
        std::unordered_map<int, Variable *> variableSet;
        
        /// The current conflict clause
        Clause* _conflictClause = nullptr;
        /// The current unit clause
        Clause* _unitClause     = nullptr;
        
        Clause lastAddedClause;
        
        
    };
}



#endif /* Formula_hpp */
