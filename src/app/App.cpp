//
//  App.cpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include "App.hpp"

Application::App::App(int argc, char* argv[]) {
    this->m_argc = argc;
    this->m_argv = argv;
}

int Application::App::run() {
    
    if(this->m_argc != 3 && this->m_argc != 6 && this->m_argc != 5) {
        return -1;
    } else {
        
<<<<<<< HEAD
    for(int i = 1; i <= 2; i++) {
        std::string fe = "/Users/christianschmidt/Documents/Uddannelse/DTU/Semester4/Fagprojekt/SAT/data/2cnfs/uf50-218/";
        std::string file = fe + "uf50-0" + std::to_string(i) + ".cnf";
        //std::cout << file << std::endl;
        
        cnf::Formula *f = util::Parser(file.c_str()).parse();
        
        algorithms::DTUSat *solver = new algorithms::DTUSat();
        solver->setup(*f);
        bool res = false;
        res = solver->solve();
        
        if(res) {
            std::cout << "SAT" + std::to_string(i) << std::endl;
=======
        if(this->m_argc == 3) {
     
            if(std::strcmp(this->m_argv[1], "-f") == 0)  {
                
                cnf::Formula *f;
                algorithms::DTUSat *solver;
                
                try {
                    std::string file = std::string(this->m_argv[2]) + ".cnf";
                    solver = new algorithms::DTUSat();
                    f = util::Parser(file.c_str()).parse();
                } catch(util::ParserException p) {
                    solver->failed();
                    return -1;
                }
                
                solver->setup(*f);
                bool res = false;
                res = solver->solve();
                
                delete f;
                delete solver;
                
                if(res)
                    return 0;
                    
                return -1;
                
            } else {
                return -1;
            }
        } else if (this->m_argc == 5) {
            
            if(std::strcmp(this->m_argv[1], "-f") == 0 && std::strcmp(this->m_argv[3], "-o") == 0)  {
                
                cnf::Formula *f;
                algorithms::DTUSat *solver;
                
                try {
                    std::string file = std::string(this->m_argv[2]) + ".cnf";
                    solver = new algorithms::DTUSat("CDCL", std::string(this->m_argv[4])+".json", false);
                    f = util::Parser(file.c_str()).parse();
                } catch(util::ParserException p) {
                    solver->failed();
                    return -1;
                }
                
                solver->setup(*f);
                bool res = false;
                res = solver->solve();
                
                delete f;
                delete solver;
                
                if(res)
                    return 0;
                
                return -1;
                
            } else {
                return -1;
            }
>>>>>>> ead72f096fc38349de54213b70ceb4d8e42723c7
        } else {
            
            if(std::strcmp(this->m_argv[1], "-f") == 0 && std::strcmp(this->m_argv[3], "-o") == 0 && std::strcmp(this->m_argv[5], "--verbose") == 0)  {
            
                cnf::Formula *f;
                algorithms::DTUSat *solver;

                try {
                    std::string file = std::string(this->m_argv[2]) + ".cnf";
                    solver = new algorithms::DTUSat("CDCL", std::string(this->m_argv[4])+".json", true);
                    f = util::Parser(file.c_str()).parse();
                } catch(util::ParserException p) {
                    solver->failed();
                    return -1;
                }
                
                solver->setup(*f);
                bool res = false;
                res = solver->solve();
                
                delete f;
                delete solver;
                
                if(res)
                    return 0;
                
                return -1;
            
            } else {
                return -1;
            }
        }
        
    }
    
}
