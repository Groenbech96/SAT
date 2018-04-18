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
        std::cout << unitClause.get()->string() << std::endl;
        if (l != boost::none) {

            cnf::Literal unpackedLiteral = l.get();

            //Assigns the variable to the value making the literal evaluate to true
            unpackedLiteral.pVar->setAssignment((!unpackedLiteral.isNegated) ? cnf::TRUE : cnf::FALSE);

            // Add the implied variable to the implication graph
            this->graph.addVertex(unpackedLiteral.pVar, decisionLevel, unitClause.get()->getId());

            // Add edges from all other variables in the same clause
            for(auto literals = unitClause.get()->getLiterals().begin(); literals != unitClause.get()->getLiterals().end();literals++ ){
                if (literals->second.pVar != unpackedLiteral.pVar) {
                    this->graph.addEdge(literals->second.pVar, unpackedLiteral.pVar);
                }
            }
        }
        
        boost::optional<cnf::Clause *> conflictClause = this->formula.containsConflict();
        
        if(conflictClause != boost::none) {
            // Add conflict vertex to implication graph
            this->graph.addVertex(nullptr, decisionLevel, conflictClause.get()->getId());
            
            for(auto literals = conflictClause.get()->getLiterals().begin(); literals != conflictClause.get()->getLiterals().end();literals++ ){
                this->graph.addEdge(literals->second.pVar, nullptr);
            }
            
            return CONFLICT;
        } else if(!this->formula.hasUnsatisfiedClauses()) {
            return SOLVED;
        }
        
        unitClause = this->formula.getUnitClause();
    }
    
    return SIMPLIFIED;
}

int algorithms::CompleteSolver::conflictAnalysis() {
    
    // Get the conflict clause k
    util::vertex* conflictVertex = this->graph.getVertex(nullptr);

    int currentDecisionLevel = conflictVertex->decisionLevel;
    int beta;
    
    // Get the antecedent clause of k
    int antecedentClauseID = conflictVertex->antecedentClauseID;
    auto antecedentClause = this->formula.getClauseSet().find(antecedentClauseID)->second;

    // Queue of literals assigned in this decision level
    std::queue<cnf::Literal> *q = new std::queue<cnf::Literal>;
    std::unordered_map<int, cnf::Literal> *visitedLiterals = new std::unordered_map<int, cnf::Literal>;
    // Temporary learning clause - set
    
    auto tempClause = clauseToMap(antecedentClause);

    for(auto it = tempClause->begin(); it != tempClause->end(); ++it) {
        //int id = it->first;
        //cnf::Literal l = antecedentClause->getLiteral(id).get();

        if(isImpliedLiteralAtDesicionLvl(it->second, currentDecisionLevel))
            q->push(it->second);
    }

    while(!q->empty()) {

        auto l = q->front();
        auto v = this->graph.getVertex(l.pVar);
        
        visitedLiterals->insert({l.pVar->getKey(), l});
        
        //visitedLiterals->insert(q->front().pVar->getKey(), q->front());
        q->pop();
        
        int antecedentClauseID = v->antecedentClauseID;
        auto antecedentClause = this->formula.getClauseSet().find(antecedentClauseID)->second;
        
        resolutionOperation(tempClause, antecedentClause, q, visitedLiterals, currentDecisionLevel);

    }
    
    this->formula.addClause(*tempClause);
    delete tempClause;

    return 0;
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
        if (duplicateLiterals.count(kv->first) == 0) {

            tempClauseMap->insert({kv->first, kv->second});

            if(visited->count(kv->first) == 0
               && isImpliedLiteralAtDesicionLvl(kv->second, decisionLevel))
            {
                // Update queue
                q->push(kv->second);
                visited->insert({kv->first, kv->second});
            }
        }
    }
}



bool algorithms::CompleteSolver::isImpliedLiteralAtDesicionLvl(cnf::Literal l, int d) {
    auto vex = this->graph.getVertex(l.pVar);
    return d == vex->decisionLevel && vex->antecedentClauseID != -1;

}

std::unordered_map<int, cnf::Literal> *algorithms::CompleteSolver::clauseToMap(cnf::Clause *clause) {
    std::unordered_map<int, cnf::Literal> *l = new std::unordered_map<int, cnf::Literal>;
    
    for(auto kv = clause->getLiterals().begin(); kv != clause->getLiterals().end(); kv++) {
        l->insert({kv->first, kv->second});
    }
    
    return l;
}




