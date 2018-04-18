//
//  App.cpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include "App.hpp"

int Application::App::run() {
    
    try {
        
        auto parser = new util::Parser("/Users/gronbech/Desktop/Software/c++/SAT/data/cnfs/uf20-91/test.cnf");
        cnf::Formula *f = parser->parse();
        
        algorithms::CDCL *c = new algorithms::CDCL();
        
        c->setup(*f);
        c->solve();
        
    
        
    } catch (util::ParserException &e) {
        std::cout << e.what() << std::endl;
    }
    

    
    return 0;
}
