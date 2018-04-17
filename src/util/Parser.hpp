//
//  Parser.hpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 07/03/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include <exception>
#include <string>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <set>
#include <list>
#include "Formula.hpp"
#include "Variable.hpp"
#include "Literal.h"
#include "Clause.hpp"

namespace util {
    
    ///
    /// CNF parser class
    ///
    class Parser : public std::exception {
        
    public:
        /// CNF parser
        /// \param t_fn the file name
        Parser(const char* t_fn);
        
        /// Parse the file into a Formula Object
        /// \return a set of formulas (This depends on how many is in file)
        cnf::Formula* parse();
        
        
        
    private:
        /// input stream for file
        std::fstream *m_input;
        /// file name
        const char* m_fn;
        
        /// parse on line of cnf into a clause of literals
        /// \param st the "line" from file that contains literals
        /// \param varMap is the map of variables
        /// \return a map with literal id as key and literal object at value
        std::unordered_map<int, cnf::Literal> parseLine(std::istringstream *st, std::unordered_map<int, cnf::Variable*> &varMap);
        
        
    };
    
    ///
    /// Standard parser exception
    ///
    class ParserException : public std::exception {
        
    public:
        /// Exception type for parser
        /// \param t_fn the file to parse
        /// \param t_msg the error to throw
        ParserException(const char* t_fn, const char* t_msg) : m_fn(t_fn), m_msg(t_msg) {}
        /// overwritten from std::exception
        /// \return the error message
        virtual const char *what(void) const throw() {
            std::string out;
            out="Parse Exception: File ";
            out+=this->m_fn;
            out+= " ";
            out+= this->m_msg;
            return out.c_str();
        }
        
    private:
        /// file path or file name
        const char* m_fn;
        /// error message
        const char* m_msg;
    };
    
    
    
    
}

#endif /* Parser_hpp */

