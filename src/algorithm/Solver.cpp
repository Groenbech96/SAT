//
//  Solver.cpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include "Solver.hpp"

algorithms::Solver::Solver() {
    this->output = false;
}


algorithms::Solver::Solver(std::string outputFile) {
    this->output = true;
    util::Config config = util::Config("Solver","example.json");
    this->outputter = util::Output(config);
}

// Provide a definition for destructor.  
algorithms::Solver::~Solver() {}

