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
#include "Schonings.hpp"



class BenchmarkFixture : public ::hayai::Fixture {
    
    
public:

    
    virtual void SetUp() {
        
    }
    
    virtual void TearDown()
    {
        
    }
    

};


int main() {
    
    std::ofstream some_file("/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/test/benchmarks/Schonings.json");
    
    hayai::JsonOutputter json = hayai::JsonOutputter(some_file);
    hayai::ConsoleOutputter out;
    
    hayai::Benchmarker::AddOutputter(json);
    hayai::Benchmarker::AddOutputter(out);
    hayai::Benchmarker::RunAllTests();
    return 0;
    
}


BENCHMARK_F(BenchmarkFixture, SOLVEUF20Prob, 4, 1) {
    
    int count = 0;
    for(int j = 1; j <= 1000; j++) {
        
        std::string file = "/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf20-91/uf20-0" + std::to_string(j) + ".cnf";
        util::Parser *p = new util::Parser(file.c_str());
        
        cnf::Formula *f = p->parse();
        
        algorithms::Schonings *solver = new algorithms::Schonings();
        solver->setup(*f);
        bool res = false;
        res = solver->solve();
        if(res)
            count++;
        
        delete solver;
        delete p;
        delete f;
        
    }
    
    std::cout << "corrects: " << count << std::endl;
    
}

BENCHMARK_F(BenchmarkFixture, SOLVEUF50Prob, 4, 1) {
    
    int count = 0;
    for(int j = 1; j <= 1000; j++) {
        
        std::string file = "/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf50-218/uf50-0" + std::to_string(j) + ".cnf";
        util::Parser *p = new util::Parser(file.c_str());
        
        cnf::Formula *f = p->parse();
        
        algorithms::Schonings *solver = new algorithms::Schonings();
        solver->setup(*f);
        bool res = false;
        res = solver->solve();
        if(res)
            count++;
        
        delete solver;
        delete p;
        delete f;
        
    }
    
    std::cout << "corrects: " << count << std::endl;
    
}


BENCHMARK_F(BenchmarkFixture, SolveUF20, 4, 1) {
    
    for(int j = 1; j <= 1000; j++) {
        
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
    
}

BENCHMARK_F(BenchmarkFixture, SolveUF50, 4, 1) {
    
    for(int j = 1; j <= 1000; j++) {
        
        std::string file = "/Users/gronbech/Desktop/Software/c++/SAT_XCode/SAT/data/cnfs/uf50-218/uf50-0" + std::to_string(j) + ".cnf";
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
    
}



