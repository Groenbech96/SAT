//
//  App.cpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include "App.hpp"

int Application::App::run() {
        
    for(int i = 1; i <= 2; i++) {
        
        std::string fe = "/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf50-218/";
        std::string file = fe + "uf50-0" + std::to_string(i) + ".cnf";
        
        cnf::Formula *f = util::Parser(file.c_str()).parse();
        
        algorithms::DTUSat *solver = new algorithms::DTUSat("example.json");
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
    
    std::cout << "See example.json for output"  << std::endl;
    
    return 0;
}
