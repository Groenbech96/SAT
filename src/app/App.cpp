//
//  App.cpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include "App.hpp"
//#include "rapidjson/writer.h"

int Application::App::run() {
        
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
        } else {
            std::cout << "UNSAT" + std::to_string(i) << std::endl;
        }
        
        delete f;
        delete solver;
        
    }
    
    
    return 0;
}
