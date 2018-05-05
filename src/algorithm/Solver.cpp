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
    this->verbose = false;
}


algorithms::Solver::Solver(std::string type, std::string outputFile, bool verbose) {
    this->output = true;
    this->verbose = verbose;
    util::Config config = util::Config(type, outputFile);
    //config.setdecisionTracking(true);
    //config.setdecisionScoreTracking(true);
    this->outputter = util::Output(config);
}

// Provide a definition for destructor.  
algorithms::Solver::~Solver() {}

