//
//  Graph.cpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 07/03/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include "Graph.hpp"

void util::Graph::addVertex(cnf::Variable *variable, int decisionLevel, int antecedentClauseID)
{
    vertex *v;
    v = new vertex(variable, decisionLevel, antecedentClauseID);
    graphMap[variable] = v;
    
}

void util::Graph::addEdge(cnf::Variable* from, cnf::Variable* to){
    
    vertex *f = (graphMap.find(from)->second);
    vertex *t = (graphMap.find(to)->second);
    f->outgoingEdges.push_back(t);
    t->ingoingEdges.push_back(f);
}

bool util::Graph::deleteVertex(cnf::Variable* vexVar) {
    auto vex = new vertex(vexVar, -1, -1);
    
    try {
        auto vex = this->graphMap.find(vexVar);
    } catch (...) {
        return false;
    }
    
    for(auto it = vex->ingoingEdges.begin(); it != vex->ingoingEdges.end(); ++it) {
        
        int deleteIndex = -1;
        
        for(auto it2 = (*it)->outgoingEdges.begin(); it2 != (*it)->outgoingEdges.end(); ++it) {
            if ((*it2)->var == vexVar){
                
            }
        }
    
        (*it)->outgoingEdges.
        
        
        
    
    }
    
}

util::vertex* util::Graph::getVertex(cnf::Variable* v) {
    return graphMap.find(v)->second;
}

std::string util::Graph::stringJsStyle() {
    std::string s = "Vertexes (\n";
    for(auto g = graphMap.begin(); g != graphMap.end(); g++ ) {
        vertex* v = g->second;
        s += "{id: " + std::to_string(v->var->getKey()) + ", label: V" + std::to_string(v->var->getKey()) +"}\n";
    }
    
    s += ")\nEdges: (\n";
    for(auto g = graphMap.begin(); g != graphMap.end(); g++ ) {
        vertex* v = g->second;
        
        std::vector<vertex*> ve = v->outgoingEdges;
        for(auto vex : ve) {
            s += "{from: " + std::to_string(v->var->getKey()) + ", to: " + std::to_string(vex->var->getKey()) + ", arrows:'to', label: " + std::to_string(vex->antecedentClauseID) + "}\n";
        }
    }
    s += ")";
    return s;
}


