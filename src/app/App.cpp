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
#include "Formula.hpp"
#include <ctime>
#include <cstdio>

Application::App::App(int argc, char* argv[]) {
    this->m_argc = argc;
    this->m_argv = argv;
}

int Application::App::run() {

    
    if(this->m_argc != 3 && this->m_argc != 6 && this->m_argc != 5) {
        return -1;
    } else {
        
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
                
                return 0;

            }
            else {
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
                
                return 0;

                
            }
            else if(std::strcmp(this->m_argv[1], "CDCL") == 0 && std::strcmp(m_argv[2], "-pt") == 0){
                int n = std::stoi(m_argv[3]);
                int m = std::stoi(m_argv[4]);
                int k = 3;
                auto f = new cnf::Formula(k,m,n);
                auto solver = new algorithms::DTUSat();
                
                solver->setup(*f);
                bool res = false;
                clock_t start = clock();
                res = solver->solve();
                clock_t end = clock();
                unsigned int totalTime = (unsigned int)(end-start);
                
                if (res)
                    std::cout << "t" << std::endl;
                else
                    std::cout << "f" << std::endl;
                std::cout << std::to_string(totalTime) << std::endl;
                
                delete f;
                delete solver;
                
                return 0;
            }
            else if (std::strcmp(this->m_argv[1], "SCH") == 0){
                int n = std::stoi(m_argv[3]);
                int m = std::stoi(m_argv[4]);
                int k = 3;
                auto f = new cnf::Formula(k,m,n);
                auto solver = new algorithms::Schonings();
                
                solver->setup(*f);
                bool res = false;
                clock_t start = clock();
                res = solver->solve();
                clock_t end = clock();
                uint64_t totalTime = (uint64_t)(end-start); 
                
                if (res)
                    std::cout << "t" << std::endl;
                else
                    std::cout << "f" << std::endl;
                std::cout << std::to_string(totalTime) << std::endl;
                
                delete f;
                delete solver;
                
                return 0;            }
            else {
                return -1;
            }
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
                
                return 0;
            
            } else {
                return -1;
            }
        }
        
    }
    
}
