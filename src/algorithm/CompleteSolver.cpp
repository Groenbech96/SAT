//
//  CompleteSolver.cpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include "CompleteSolver.hpp"


algorithms::UnitPropagationResult algorithms::CompleteSolver::unitPropagation(int decisionLevel) {
    
    auto unitClause = this->formula.getUnitClause();
    
    //While unsatisfied clauses still exist
    while( unitClause != boost::none) {
        
        boost::optional<cnf::Literal> l = unitClause.get()->getUnitLiteral();
        // std::cout << unitClause.get()->string() << std::endl;
        if (l != boost::none) {

            cnf::Literal unpackedLiteral = l.get();

            //Assigns the variable to the value making the literal evaluate to true
            unpackedLiteral.pVar->setAssignment((!unpackedLiteral.isNegated) ? cnf::TRUE : cnf::FALSE);
          
            // Add the implied variable to the implication graph
            this->graph.addVertex(unpackedLiteral.pVar, decisionLevel, unitClause.get()->getId());
            
            // Add edges from all other variables in the same clause
            for(auto literals = unitClause.get()->getLiterals().begin(); literals != unitClause.get()->getLiterals().end();literals++ ){
                if (literals->second.pVar != unpackedLiteral.pVar) {
                    // DEBUG
                    if(literals->second.pVar->getAssignment() == cnf::UNASSIGNED) {
                        std::cout << "ERROR FAILED" << std::endl;
                    }
                    this->graph.addEdge(literals->second.pVar, unpackedLiteral.pVar);
                }
            }
        }
        
        boost::optional<cnf::Clause *> conflictClause = this->formula.containsConflict();
        
        if(conflictClause != boost::none) {
            // Add conflict vertex to implication graph
            this->graph.addVertex(nullptr, decisionLevel, conflictClause.get()->getId());
            
            for(auto literals = conflictClause.get()->getLiterals().begin(); literals != conflictClause.get()->getLiterals().end();literals++ ){
                // DEBUG
                if(literals->second.pVar->getAssignment() == cnf::UNASSIGNED) {
                    std::cout << "ERROR FAILED" << std::endl;
                }
                this->graph.addEdge(literals->second.pVar, nullptr);
            }
            //std::cout << "conflict found " + conflictClause.get()->string()  << std::endl;
            
            return CONFLICT;
            
        } //else if(!this->formula.hasUnsatisfiedClauses()) {
         //   return SOLVED;
        // }
        
        unitClause = this->formula.getUnitClause();
    }
    
    return SIMPLIFIED;
}

int algorithms::CompleteSolver::conflictAnalysis() {
    
//    // Get the conflict clause k
//
//    auto search = this->graph.getVertex(nullptr);
//    util::vertex* conflictVertex = search.get();
//
//    if(search == boost::none) { exit(10); }
//
//    int currentDecisionLevel = conflictVertex->decisionLevel;
//    int assertionLevel;
//
//    // Get the antecedent clause of k
//    int antecedentClauseID = conflictVertex->antecedentClauseID;
//    auto antecedentClause = this->formula.getClauseSet().find(antecedentClauseID)->second;
//
//    // Queue of literals assigned in this decision level
//    std::queue<cnf::Literal> *q = new std::queue<cnf::Literal>;
//    std::unordered_map<int, cnf::Literal> *visitedLiterals = new std::unordered_map<int, cnf::Literal>;
//    // Temporary learning clause - set
//
//    auto tempClauseMap = convertClauseToMap(antecedentClause);
//    //std::cout << "conflict analysis started with " + antecedentClause->string()  << std::endl;
//
//
//    int literalInCurrentDL = 0;
//    for(auto it = tempClauseMap->begin(); it != tempClauseMap->end(); ++it) {
//
//        auto search = this->graph.getVertex(it->second.pVar);
//        auto vex = search.get();
//        if(search == boost::none) {
//            // Do some error handling here
//            // TODO: ERROR HANDLE
//            //std::cout << "error 2" << std::endl;
//        }
//        if(vex->decisionLevel == currentDecisionLevel) {
//            literalInCurrentDL++;
//        }
//        //cnf::Literal l = antecedentClause->getLiteral(id).get();
//
//        //std::cout << "here 1" << std::endl;
//        if(isImpliedLiteralAtDesicionLevel(it->second, currentDecisionLevel))
//            q->push(it->second);
//    }
//
//    // If the first clause what a UIP, then return it
//    if(literalInCurrentDL == 1) {
//        this->formula.addClause(*tempClauseMap);
//        int lvl = getAssertionLevel(tempClauseMap);
//        delete tempClauseMap;
//        delete q;
//        delete visitedLiterals;
//        return lvl;
//    }
//
//    while(!q->empty()) {
//
//        auto l = q->front();
//        q->pop();
//
//        visitedLiterals->insert({l.pVar->getKey(), l});
//
//        auto search = this->graph.getVertex(l.pVar);
//        auto v = search.get();
//        if(search == boost::none) {
//            // Do some error handling here
//            // TODO: ERROR HANDLE
//            //std::cout << "error 3" << std::endl;
//        }
//
//        int antecedentClauseID = v->antecedentClauseID;
//        auto antecedentClause = this->formula.getClauseSet().find(antecedentClauseID)->second;
//
//        resolutionOperation(tempClauseMap, antecedentClause, q, visitedLiterals, currentDecisionLevel);
//
//        int literalInCurrentDL = 0;
//        for(auto it = tempClauseMap->begin(); it != tempClauseMap->end(); ++it) {
//            auto search = this->graph.getVertex(it->second.pVar);
//            auto vex = search.get();
//            if(search == boost::none) {
//                // Do some error handling here
//                // TODO: ERROR HANDLE
//                //std::cout << "error 4" << std::endl;
//            }
//            if(vex->decisionLevel == currentDecisionLevel) {
//                literalInCurrentDL++;
//            }
//        }
//
//        // If learned clause is UIP, then return it
//        if(literalInCurrentDL == 1) {
//            this->formula.addClause(*tempClauseMap);
//            int lvl = getAssertionLevel(tempClauseMap);
//            delete tempClauseMap;
//            delete q;
//            delete visitedLiterals;
//
//            return lvl;
//        }
//
//
//    }
//
//
//    //std::cout << "this should not" << std::endl;
//    assertionLevel = getAssertionLevel(tempClauseMap);
//
//
//    this->formula.addClause(*tempClauseMap);
//    delete tempClauseMap;
//    delete q;
//    delete visitedLiterals;
//    return assertionLevel;
    
    return 0;
}


int algorithms::CompleteSolver::getAssertionLevel(std::unordered_map<int, cnf::Literal> *map) {
    int m1 = -1;
    int m2 = -1;
    
    if(map->size() == 1) {
        
        auto pvar = map->begin()->second.pVar;
        auto search = this->graph.getVertex(pvar);
        auto vex = search.get();
        if(search == boost::none) {
            // Do some error handling here
            // TODO: ERROR HANDLE
            //std::cout << "error 5" << std::endl;
        }
        auto vexDL = vex->decisionLevel;
        return (vexDL == 0) ? -1 : 0;
 
    }
    
    
    for(auto it = map->begin(); it != map->end(); ++it) {
        
        auto pvar = it->second.pVar;
        auto search = this->graph.getVertex(pvar);
        auto vex = search.get();
        if(search == boost::none) {
            // Do some error handling here
            // TODO: ERROR HANDLE
            //std::cout << "error 6" << std::endl;
        }
        

        // get second highest decision lvl
        if(vex->decisionLevel > m2) {
            if(vex->decisionLevel > m1) {
                m2 = m1;
                m1 = vex->decisionLevel;
            } else if (vex->decisionLevel != m1) {
                m2 = vex->decisionLevel;
            }
        }
    }
    
    // No second highest found
    // Learned clause only contains one decision level
    if( m2 == -1) {
        return m1;
    }
    return m2;
}



void algorithms::CompleteSolver::resolutionOperation(std::unordered_map<int, cnf::Literal>* tempClauseMap,
                                             cnf::Clause* antecedentClause,
                                             std::queue<cnf::Literal>* q,
                                             std::unordered_map<int, cnf::Literal>* visited,
                                             int decisionLevel) {

    std::unordered_set<int> duplicateLiterals;
    // create copy of antecendentClauseObject
    cnf::Clause antecedentClauseTemp = *antecedentClause;
    auto it = tempClauseMap->begin();

    // Loop through the literals currently in the tempClauseSet
    while(it != tempClauseMap->end()) {

        auto l = it->second;
        
        boost::optional<cnf::Literal &> search = antecedentClauseTemp.getLiteral(l.pVar->getKey());

        if(search != boost::none) {

            // Resolution operation - deletion of neg/not-neg pair of variables
            if((search->isNegated && !l.isNegated) || (!search->isNegated && l.isNegated)) {

                it = tempClauseMap->erase(it);
                antecedentClauseTemp.removeLiteral(search.get().pVar->getKey());

            }
            else {

                duplicateLiterals.insert(search.get().pVar->getKey());
                it++;

            }
        }
        else {
            it++;
        }
    }

    
    // Merge tempClauseSet with antecedentClause
    for (auto kv = antecedentClauseTemp.getLiterals().begin(); kv != antecedentClauseTemp.getLiterals().end(); ++kv) {
        int i = kv->first;
        auto c = kv->second;
        if (duplicateLiterals.count(i) == 0) {

            tempClauseMap->insert({i, c});
            
            //std::cout << "here 2" << std::endl; ERROR HERE
            if(visited->count(i) == 0
               && isImpliedLiteralAtDesicionLevel(c, decisionLevel))
            {
                // Update queue
                q->push(kv->second);
                visited->insert({kv->first, kv->second});
            }
        }
    }
}



bool algorithms::CompleteSolver::isImpliedLiteralAtDesicionLevel(cnf::Literal l, int d) {
    auto search = this->graph.getVertex(l.pVar);
    
    if(search == boost::none) {
        // Do some error handling here
        // TODO: ERROR HANDLE
        //std::cout << "error 7" << std::endl;
    }
    auto vex = search.get();
    return d == vex->decisionLevel && vex->antecedentClauseID != -1;

}

std::unordered_map<int, cnf::Literal> *algorithms::CompleteSolver::convertClauseToMap(cnf::Clause *clause) {
    
    std::unordered_map<int, cnf::Literal> *l = new std::unordered_map<int, cnf::Literal>;
    
    for(auto kv = clause->getLiterals().begin(); kv != clause->getLiterals().end(); kv++) {
        l->insert({kv->first, kv->second});
    }
    
    return l;
}


int algorithms::CompleteSolver::getGraphSize() {
    return (int) this->graph.graphMap.size();
}




