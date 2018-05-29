//
//  Config.cpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//
#include "Config.hpp"




void util::Config::setSolverType(std::string type) { this->_solverType = type; }
std::string util::Config::getSolverType() { return this->_solverType; }

void util::Config::setFilename(std::string file) { this->_filename = file; }
std::string util::Config::getFilename() { return this->_filename; }

time_t util::Config::getTimestamp() { return this->_timestamp; }

void util::Config::setdecisionTracking(bool v) { this->_decisionTracking = v; }
bool util::Config::getdecisionTracking() {return this->_decisionTracking; }

void util::Config::setdecisionScoreTracking(bool v) { this->_decisionScoreTracking = v; }
bool util::Config::getdecisionScoreTracking() { return this->_decisionScoreTracking; }


