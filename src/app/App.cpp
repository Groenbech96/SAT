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
    
    
    cnf::Formula *f = util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf20-91/A_unitTest2.cnf").parse();
    
    algorithms::CDCL *solver = new algorithms::CDCL();
    solver->setup(*f);
    
    f->getVariable(0).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(0).get(), 1, -1);
    f->getVariable(1).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(1).get(), 2, -1);
    //f->getVariable(2).get()->setAssignment(cnf::TRUE);
    //solver->addToImplicationGraph(f->getVariable(2).get(), 3, -1);
    f->getVariable(3).get()->setAssignment(cnf::TRUE);
    solver->addToImplicationGraph(f->getVariable(3).get(), 4, -1);
    
    auto s = solver->unitPropagation(4);
    
    
    return 0;
    
    try {
        
        auto parser = new util::Parser("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf20-91/uf20-05.cnf");
        cnf::Formula *f = parser->parse();
        
        algorithms::CDCL *c = new algorithms::CDCL();
        
       // f->getVariableSet().find(21)->second->setAssignment(cnf::VariableAssignment::FALSE);
        
       // f->getVariableSet().find(31)->second->setAssignment(cnf::VariableAssignment::FALSE);
       // f->getVariableSet().find(1)->second->setAssignment(cnf::VariableAssignment::FALSE);
        
        //f->getVariableSet().find(1)->second->setAssignment(cnf::VariableAssignment::TRUE);
        
        //f->getVariableSet().find(2)->second->setAssignment(cnf::VariableAssignment::TRUE);
        // f->getVariableSet().find(3)->second->setAssignment(cnf::VariableAssignment::TRUE);
        

        c->setup(*f);
        bool solve = c->solve();
        std::string s = "";
        if (solve) {
            s += "SAT: ";
        } else {
            s += "UNSAT: ";
        }
        
        for(auto it : f->getVariableSet()) {
            std::string s1 = std::to_string(it.second->getKey());
            s.append(s1);
            s += "->";
            s += std::to_string(it.second->getAssignment() == cnf::TRUE ? 1 : 0);
            s += "; ";
        }
        
        std::cout << s << std::endl;
    
        
    } catch (util::ParserException &e) {
        std::cout << e.what() << std::endl;
    }
    

    
    return 0;
}
