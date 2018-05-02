//
//  Parser.cpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 07/03/2018.
//  Copyright © 2018 DTU. All rights reserved.
//


#include "Parser.hpp"


util::Parser::~Parser() {
    
}

util::Parser::Parser(const char *fn) {
    this->m_fn = fn;
    struct stat info;
    if(stat(this->m_fn, &info)) {
        throw ParserException(this->m_fn, "is not in directory");
    }
    
    this->m_input = new std::fstream(fn, std::fstream::in);
    if(this->m_input->fail())
        throw ParserException(this->m_fn, "wont open");
}


cnf::Formula* util::Parser::parse() {
    
    std::string line;
    std::set<cnf::Formula *> cnfs;
    cnf::Formula *f = nullptr;
    
    *this->m_input>>std::ws; // remove whitespace
    
    getline(*this->m_input, line); // get first line and copy into "line" string
    while (!m_input->eof()) {
        
        switch(line[0]) {
            case '0': { // Never last 0
                break;
            }
            case 'c': { // Never mind comments
                break;
            }
            case 'p': { // start of clauses begin
                
                int nVars;
                int nClauses;
                
                
                std::string p, cnf;
                auto in = new std::istringstream(line); // This way we can get numbers easily
                *in >> p >> cnf >> nVars >> nClauses; // The information is now stored in variables
                delete in;
                
                std::unordered_map<int, cnf::Variable *> variableSet;
                std::unordered_map<int, cnf::Clause *> clauseSet;
                std::set<int> usedVars;
                std::set<int> allVars;
                for(int i = 0; i < nVars; i++) {
                    allVars.insert(i);
                }
                int clauseCounter = 0;
                
                // Create nVar new variables
                for (int i = 0; i < nVars; i++) {
                    // std::shared_ptr<cnf::Variable> pVar = std::make_shared<cnf::Variable>(i);
                    auto *pVar = new cnf::Variable(i);
                    variableSet.insert({i, pVar});
                }
                
                line.clear(); // clear string
                *this->m_input >> std::ws; // remove whitespace on the line we are about to get
                while (getline(*this->m_input, line)) {
                    
                    if (line[0] == '%') { // end of read
                        break;
                    } else {
                        
                        // Line start
                        
                        auto inLine = new std::istringstream(line);
                        std::unordered_map<int, cnf::Literal> clauseLiterals = this->parseLine(inLine, variableSet);
                    
                        
                        for(auto it : clauseLiterals) {
                            usedVars.insert(it.first);
                        }
                        
                        // Line end
                        auto pClause = new cnf::Clause(clauseCounter, clauseLiterals);
                        clauseSet.insert({clauseCounter, pClause});
                        clauseCounter++;
                        line.clear();
                        
                        delete inLine;
                        
                    }
                    
                }
                
                std::set<int> diff;
                std::set_difference(allVars.begin(), allVars.end(), usedVars.begin(), usedVars.end(), std::inserter(diff, diff.begin()));
                
                for(auto i : diff) {
                    auto v = variableSet.find(i);
                    delete v->second;
                    variableSet.erase(i);
                }
                
                nVars = (int)variableSet.size();
                
                // TODO: Implement more than 3-SAT here
                f = new cnf::Formula(3, nClauses, nVars, variableSet, clauseSet);
                
                
                // clear containers
                variableSet.clear();
                clauseSet.clear();
                
                break;
                
            } default: {
                throw ParserException(this->m_fn, "error in file format");
                
            }
                
                
        }  // because we removed whitespace, we can now look at index 0 in the line
        
        line.clear(); // empty the string
        *this->m_input>>std::ws; // remove whitespace
        getline(*this->m_input, line);
        
    }
    
    // We return first element
    // return *std::next(cnfs.begin());
    delete this->m_input;
    
    return f;
    
}

std::unordered_map<int, cnf::Literal> util::Parser::parseLine(std::istringstream *ss,
                                                              std::unordered_map<int, cnf::Variable*> &varMap) {

    std::unordered_map<int, cnf::Literal> lits;
    
    std::string var;
    int id;
    bool negated;
    
    while(!ss->eof()) {
        
        *ss>>var; // Load the variables into var
        
        if(var == "0") // break if line end
            break;
        
        if(var[0] == '-') {
            negated = true;
            id = atoi(var.substr(1).c_str());
        } else {
            negated = false;
            id = atoi(var.c_str());
        }
        
        id--;   // Dimacs format has literal id from 1 to N, instead of 0 to N-1.
        // We need 0 to N-1
        
        cnf::Literal l = {varMap.at(id), negated};
        lits.insert({id, l});
        
    }
    
    return lits;
}

