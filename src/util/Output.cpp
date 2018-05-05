//
//  Output.cpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 30/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include "Output.hpp"


util::Output::Output() {
    
    this->_step = 0;
    this->_outfile = std::ofstream("default.json");
    this->_document.SetObject();
    this->_document.AddMember(rapidjson::Value("status" , _document.GetAllocator()), rapidjson::Value(rapidjson::kStringType), this->_document.GetAllocator());
    this->_document.AddMember(rapidjson::Value("sat_solver" , _document.GetAllocator()), rapidjson::Value(rapidjson::kStringType), this->_document.GetAllocator());
    this->_document.AddMember(rapidjson::Value("timestamp"  , _document.GetAllocator()), rapidjson::Value(rapidjson::Value(rapidjson::kStringType), _document.GetAllocator()).Move(), this->_document.GetAllocator());
    this->_document.AddMember(rapidjson::Value("steps" , _document.GetAllocator()), rapidjson::Value(0), this->_document.GetAllocator());
}

util::Output::Output(util::Config config) {
    
    this->_outfile = std::ofstream(config.getFilename());
    
    this->_step = 0;
    this->_document.SetObject();

    this->_document.AddMember(rapidjson::Value("status" , _document.GetAllocator()), rapidjson::Value(rapidjson::kStringType), this->_document.GetAllocator());
    this->_document.AddMember(rapidjson::Value("sat_solver" , _document.GetAllocator()), rapidjson::Value(config.getSolverType().c_str(), _document.GetAllocator()), this->_document.GetAllocator());
    this->_document.AddMember(rapidjson::Value("timestamp"  , _document.GetAllocator()), rapidjson::Value(std::to_string(config.getTimestamp()).c_str(), _document.GetAllocator()).Move(), this->_document.GetAllocator());
    this->_document.AddMember(rapidjson::Value("tracking" , _document.GetAllocator()), rapidjson::Value(rapidjson::kObjectType), this->_document.GetAllocator());
    this->_document.AddMember(rapidjson::Value("formula_begin" , _document.GetAllocator()), rapidjson::Value(rapidjson::kObjectType), this->_document.GetAllocator());
    this->_document.AddMember(rapidjson::Value("formula_end" , _document.GetAllocator()), rapidjson::Value(rapidjson::kObjectType), this->_document.GetAllocator());
    this->_document.AddMember(rapidjson::Value("steps" , _document.GetAllocator()), rapidjson::Value(0), this->_document.GetAllocator());
}

void util::Output::addFormulaAtStart(std::unordered_map<int, cnf::Clause *> clauses) {
    
    rapidjson::Value& s = _document["formula_begin"];
    for(auto kv : clauses) {
        
        int id = kv.first + 1;
        auto c = kv.second;
        
        s.AddMember(rapidjson::Value(std::to_string(id).c_str(), _document.GetAllocator()), rapidjson::Value(rapidjson::kArrayType), _document.GetAllocator());
        
        // the current clause
        rapidjson::Value &d = _document["formula_begin"][std::to_string(id).c_str()];
        
        rapidjson::Value learnItem = rapidjson::Value(rapidjson::kArrayType);
        //std::vector<int> lits;
        
        for(auto l : c->getLiterals()) {
            
            int litId = l.first + 1;
            if(l.second.isNegated)
                litId *= -1;
        
            d.PushBack(rapidjson::Value(std::to_string(litId).c_str(), _document.GetAllocator()), _document.GetAllocator());
        }
    }
}

void util::Output::addFormulaAtEnd(std::unordered_map<int, cnf::Clause *> clauses) {
    
    rapidjson::Value& s = _document["formula_end"];
    for(auto kv : clauses) {
        
        int id = kv.first + 1;
        auto c = kv.second;
        
        s.AddMember(rapidjson::Value(std::to_string(id).c_str(), _document.GetAllocator()), rapidjson::Value(rapidjson::kArrayType), _document.GetAllocator());
        
        // the current clause
        rapidjson::Value &d = _document["formula_end"][std::to_string(id).c_str()];
        
        rapidjson::Value learnItem = rapidjson::Value(rapidjson::kArrayType);
        //std::vector<int> lits;
        
        for(auto l : c->getLiterals()) {
            
            int litId = l.first + 1;
            if(l.second.isNegated)
                litId *= -1;
            
            d.PushBack(rapidjson::Value(std::to_string(litId).c_str(), _document.GetAllocator()), _document.GetAllocator());
        }
    }
}

void util::Output::addStep(std::string type, util::Graph *g, cnf::Variable *v,  int decisionLevel) {
    
    rapidjson::Value& track = this->_document["tracking"];
    track.AddMember(rapidjson::Value(std::to_string(this->_step).c_str(), _document.GetAllocator()), rapidjson::Value(rapidjson::kObjectType), this->_document.GetAllocator());
    rapidjson::Value& step = this->_document["tracking"][std::to_string(this->_step).c_str()];
    
    step.AddMember("type", rapidjson::Value(type.c_str(), this->_document.GetAllocator()), this->_document.GetAllocator());
    step.AddMember("dlvl", rapidjson::Value(std::to_string(decisionLevel).c_str(), this->_document.GetAllocator()), this->_document.GetAllocator());
    step.AddMember("variable", rapidjson::Value(std::to_string(v->getKey()+1).c_str(), this->_document.GetAllocator()), this->_document.GetAllocator());
    bool a = v->getAssignment() == cnf::V_TRUE ? true : false;
    step.AddMember("value", a, this->_document.GetAllocator());
    step.AddMember("igraph", rapidjson::Value(rapidjson::kObjectType), this->_document.GetAllocator());
    
    this->addIGraph(g);
    
    this->_step++;
}

void util::Output::addStep(std::string type, std::unordered_map<int, cnf::Literal> solution, int decisionLevel, int backtrackLevel) {
    
    rapidjson::Value& track = this->_document["tracking"];
    track.AddMember(rapidjson::Value(std::to_string(this->_step).c_str(), _document.GetAllocator()), rapidjson::Value(rapidjson::kObjectType), this->_document.GetAllocator());
    rapidjson::Value& step = this->_document["tracking"][std::to_string(this->_step).c_str()];
    
    step.AddMember("type", rapidjson::Value(type.c_str(), this->_document.GetAllocator()), this->_document.GetAllocator());
    step.AddMember("dlvl", rapidjson::Value(std::to_string(decisionLevel).c_str(), this->_document.GetAllocator()), this->_document.GetAllocator());
    step.AddMember("backtracklvl", rapidjson::Value(std::to_string(backtrackLevel).c_str(), this->_document.GetAllocator()), this->_document.GetAllocator());
    step.AddMember("uip", rapidjson::Value(std::to_string(this->_UIP).c_str(), this->_document.GetAllocator()), this->_document.GetAllocator());
    step.AddMember("conflict", rapidjson::Value(std::to_string(this->_conflictClause).c_str(), this->_document.GetAllocator()), this->_document.GetAllocator());
    
    rapidjson::Value sol = rapidjson::Value(rapidjson::kArrayType);
    
    for(auto kv : solution) {
        
        int litId = kv.first + 1;
        if(kv.second.isNegated)
            litId *= -1;
        
        sol.PushBack(rapidjson::Value(std::to_string(litId).c_str(), _document.GetAllocator()), _document.GetAllocator());
    }
    
    step.AddMember("learned", sol, this->_document.GetAllocator());
    
    this->_step++;
}

void util::Output::addStep(std::string type, std::set<util::vertex *> rm, int backtrackLevel) {
    
    rapidjson::Value& track = this->_document["tracking"];
    track.AddMember(rapidjson::Value(std::to_string(this->_step).c_str(), _document.GetAllocator()), rapidjson::Value(rapidjson::kObjectType), this->_document.GetAllocator());
    rapidjson::Value& step = this->_document["tracking"][std::to_string(this->_step).c_str()];
    
    step.AddMember("type", rapidjson::Value(type.c_str(), this->_document.GetAllocator()), this->_document.GetAllocator());
    step.AddMember("backtracklvl", rapidjson::Value(std::to_string(backtrackLevel).c_str(), this->_document.GetAllocator()), this->_document.GetAllocator());
    
    step.AddMember("igraph", rapidjson::Value(rapidjson::kObjectType), this->_document.GetAllocator());
    rapidjson::Value& graph = _document["tracking"][std::to_string(this->_step).c_str()]["igraph"];
    graph.AddMember("nodes", rapidjson::Value(rapidjson::kArrayType).Move(), this->_document.GetAllocator());
    graph.AddMember("edges", rapidjson::Value(rapidjson::kArrayType).Move(), this->_document.GetAllocator());
    
    rapidjson::Value& nodes = this->_document["tracking"][std::to_string(this->_step).c_str()]["igraph"]["nodes"];
    rapidjson::Value& edges = this->_document["tracking"][std::to_string(this->_step).c_str()]["igraph"]["edges"];
    
    nodes.SetArray();
    edges.SetArray();
    
    for(auto v : rm) {

        rapidjson::Value vNode = rapidjson::Value(rapidjson::kObjectType);
        vNode.AddMember("variable", rapidjson::Value(std::to_string(v->var->getKey()+1).c_str(), this->_document.GetAllocator()), this->_document.GetAllocator());
        
        nodes.PushBack(vNode, this->_document.GetAllocator());
        
        for(auto vex : v->ingoingEdges) {
            
            rapidjson::Value vEdge = rapidjson::Value(rapidjson::kObjectType);
            
            vEdge.AddMember("source", rapidjson::Value(std::to_string(vex->var->getKey()+1).c_str(), this->_document.GetAllocator()), this->_document.GetAllocator());
            vEdge.AddMember("target", rapidjson::Value(std::to_string(v->var->getKey()+1).c_str(), this->_document.GetAllocator()), this->_document.GetAllocator());
            
            edges.PushBack(vEdge, this->_document.GetAllocator());
        }
        
    }
    
    this->_step++;
    
}

void util::Output::addIGraph(util::Graph *g) {
    
    rapidjson::Value& graph = _document["tracking"][std::to_string(this->_step).c_str()]["igraph"];
    
    graph.AddMember("nodes", rapidjson::Value(rapidjson::kObjectType).Move(), this->_document.GetAllocator());
    graph.AddMember("edges", rapidjson::Value(rapidjson::kObjectType).Move(), this->_document.GetAllocator());
    
    rapidjson::Value& nodes = this->_document["tracking"][std::to_string(this->_step).c_str()]["igraph"]["nodes"];
    rapidjson::Value& edges = this->_document["tracking"][std::to_string(this->_step).c_str()]["igraph"]["edges"];
    
    nodes.SetObject();
    edges.SetArray();
    
    auto node = g->getLastEdited();
    bool a = node->var->getAssignment( )== cnf::V_TRUE ? true : false;
    
    nodes.AddMember("variable", rapidjson::Value(std::to_string(node->var->getKey()+1).c_str(), this->_document.GetAllocator()).Move(), this->_document.GetAllocator());
    nodes.AddMember("value", a, this->_document.GetAllocator());
    nodes.AddMember("dl", rapidjson::Value(std::to_string(node->decisionLevel).c_str(), this->_document.GetAllocator()).Move(),this->_document.GetAllocator());
    
    for(auto vex : node->ingoingEdges) {
        
        rapidjson::Value vEdge = rapidjson::Value(rapidjson::kObjectType);
        
        vEdge.AddMember("antecedent", rapidjson::Value(std::to_string(vex->antecedentClauseID).c_str(), this->_document.GetAllocator()).Move(), this->_document.GetAllocator());
        vEdge.AddMember("source", rapidjson::Value(std::to_string(node->var->getKey()+1).c_str(), this->_document.GetAllocator()).Move(), this->_document.GetAllocator());
        vEdge.AddMember("target", rapidjson::Value(std::to_string(vex->var->getKey()+1).c_str(), this->_document.GetAllocator()).Move(), this->_document.GetAllocator());
        
        edges.PushBack(vEdge, this->_document.GetAllocator());
    }
    
}

void util::Output::failure() {
    rapidjson::Value& s = _document["status"];
    s.SetString("fail", 4);
}


void util::Output::addConflictClause(cnf::Clause *c) {
    this->_conflictClause = c->getId()+1;
}
void util::Output::addUIP(int id) {
    this->_UIP = id+1;
}

void util::Output::add(std::string s) {
   this->_outfile << s << std::endl;
}
void util::Output::close() {
    this->_outfile.close();
}

void util::Output::addUnsat() {
    rapidjson::Value& s = _document["steps"];
    s.SetInt(this->_step);
    rapidjson::Value& s1 = _document["status"];
    s1.SetString("unsat", 4);
}

void util::Output::addSolution(std::unordered_map<int, cnf::Variable*> solution) {

    rapidjson::Value smap(rapidjson::kObjectType);
    for(auto it : solution) {
        std::string res = it.second->getAssignment() == cnf::V_TRUE ? "T" : "F";
        smap.AddMember(rapidjson::Value(std::to_string(it.first + 1).c_str(), this->_document.GetAllocator()), rapidjson::Value(res.c_str(), this->_document.GetAllocator()), this->_document.GetAllocator());
    }
    this->_document.AddMember("solution", smap, this->_document.GetAllocator());
    rapidjson::Value& s = _document["steps"];
    s.SetInt(this->_step);
    rapidjson::Value& s1 = _document["status"];
    s1.SetString("sat", 4);
    
    rapidjson::StringBuffer sb;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);
    this->_document.Accept(writer);
    
    this->_outfile << sb.GetString() << std::endl;

}



