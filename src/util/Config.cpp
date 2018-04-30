//
//  Config.cpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 30/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include "Config.hpp"




void util::Config::setSolverType(std::string type) { this->_solverType = type; }
std::string util::Config::getSolverType() { return this->_solverType; }

void util::Config::setFilename(std::string file) { this->_filename = file; }
std::string util::Config::getFilename() { return this->_filename; }

time_t util::Config::getTimestamp() { return this->_timestamp; }



