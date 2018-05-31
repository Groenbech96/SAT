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
    if(antecedentClauseID != -1)
        graphStack->push(variable);
    
    this->_lastEdit = v;
    
}

void util::Graph::addEdge(cnf::Variable* from, cnf::Variable* to){
    
    vertex *f = (graphMap.find(from)->second);
    vertex *t = (graphMap.find(to)->second);
    f->outgoingEdges.push_back(t);
    t->ingoingEdges.push_back(f);
}

bool util::Graph::deleteVertex(cnf::Variable* vexVar) {
    //auto vex = new vertex(vexVar, -1, -1);
    
    auto search = getVertex(vexVar);
    if(search != boost::none) {
        
        auto vex = search.get();
        
            
        this->graphMap.erase(vexVar);
        delete vex;
        
        return true;
    }
    
    return false;
}

std::stack<cnf::Variable*>* util::Graph::getStack() {
    return this->graphStack;
}

boost::optional<util::vertex*> util::Graph::getVertex(cnf::Variable *v) {
    
    auto res = this->graphMap.find(v);
    if(res != this->graphMap.end())
        return res->second;
    
    return boost::none;
    
}


void util::Graph::undo(int level) {
    

    auto it = this->graphMap.begin();
    while (it != this->graphMap.end()) {
        
        // For all vertecies that needs to be kept, remove any outgoing edges to vertecies with
        // decision level higher than level
        
        if(it->second->decisionLevel <= level) {
            
            
            auto outgoingIt = it->second->outgoingEdges.begin();
            while(outgoingIt != it->second->outgoingEdges.end()) {
                auto vertex = *outgoingIt;
                
                if(vertex->decisionLevel > level) {
                    outgoingIt = it->second->outgoingEdges.erase(outgoingIt);
                } else {
                    outgoingIt++;
                }
            }
            
            it++;
            
        } else { // Remove any vertex that has dl higher than level
            
            if(it->second->var != nullptr) {
                it->second->var->setAssignment(cnf::UNASSIGNED);
            }
            rm.insert(it->second);
            //delete it->second;
            it = this->graphMap.erase(it);
        
        }
        
    }
    
    // clean up stack
    while(!graphStack->empty()) {
        
        auto var = graphStack->top();
        if(this->getVertex(var) == boost::none) {
            graphStack->pop();
        } else {
            break;
        }
    }
    
    return;
    
}

util::vertex* util::Graph::getLastEdited() {
    return this->_lastEdit;
}


//util::vertex* util::Graph::getVertex(cnf::Variable* v) {
//    return graphMap.find(v)->second;
//}

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




