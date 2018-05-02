//
//  Variable.hpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 28/02/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef Variable_hpp
#define Variable_hpp

namespace cnf {
    
    enum VariableAssignment {
        UNASSIGNED, V_FALSE, V_TRUE
    };
    
    class Variable {
        
    public:
        Variable() = default;
        virtual ~Variable();
        
        ///
        /// Create an unassigned variable for SAT problem
        /// \param key - The variable name (Used as key, must unique)
        ///
        Variable(int key) : key(key), assignment(VariableAssignment::UNASSIGNED) {}
        
        ///
        /// Create a variable for SAT Problem
        /// \param key - The variable name (Used as key, must unique)
        /// \param assignment - Default should be unassigned!
        ///
        Variable(int key, VariableAssignment assignment) : key(key), assignment(assignment) {}
        
        ///
        /// Get assignment
        /// \return VariableAssignment
        ///
        VariableAssignment getAssignment() const;
        
        ///
        /// Get key (Also variable name)
        /// \return int
        ///
        int getKey() const;
        
        ///
        /// Changes the variable assignment
        /// \param a new assignment
        ///
        void setAssignment(VariableAssignment a);
        
        /// Comparing for variable
        bool operator > (const Variable& oVar) const{
            return key > oVar.key;
        }
        
        
    private:
        /**
         * Key for placement in map structure inside Formula
         * Key is also name of the variable
         */
        int key;
        
        /**
         * The assignment can be TRUE, FAlSE, or UNASSIGNED
         */
        VariableAssignment assignment;
        
        
    };
}

#endif /* Variable_hpp */
