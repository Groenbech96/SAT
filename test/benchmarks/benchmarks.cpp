//
//  benchmarks.cpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 28/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//


#include <fstream>
#include <hayai/hayai.hpp>
#include "Parser.hpp"
#include "DTUSat.hpp"



class BenchmarkFixture : public ::hayai::Fixture {
    
    
public:
    
    int size = 50;
    int SolveUF20Total = 1000;
    int offset = 0;
    int run = 0;
    
    virtual void SetUp() {
         offset = SolveUF20Total / size;
    }
    
    virtual void TearDown()
    {
        
    }
    
    
    
    
};



int main() {
    
    std::ofstream some_file("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/test/benchmarks/CDCL.json");
    
    hayai::JsonOutputter json = hayai::JsonOutputter(some_file);
    hayai::ConsoleOutputter out;
    
    hayai::Benchmarker::AddOutputter(json);
    hayai::Benchmarker::AddOutputter(out);
    hayai::Benchmarker::RunAllTests();
    return 0;
    
}

BENCHMARK_F(BenchmarkFixture, SolveUF20, 50, 1) {
    
    int i = size * run;
    int end = (size * run) + size;
    if(i == 0) {
        i++;
    }
    
    for(int j = i; j <= end; j++) {
        
        std::string file = "/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf20-91/uf20-0" + std::to_string(j) + ".cnf";
        util::Parser *p = new util::Parser(file.c_str());
        
        cnf::Formula *f = p->parse();
        
        algorithms::DTUSat *solver = new algorithms::DTUSat();
        solver->setup(*f);
        bool res = false;
        res = solver->solve();
        
        
        delete solver;
        delete p;
        delete f;
        
    }
    
    run++;
    
}


