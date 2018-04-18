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
        
        //Test if the formula is either satisfied or contains a conflict
        if (!this->formula.hasUnsatisfiedClauses()) {
            return SOLVED;
        } else if(conflictClause != boost::none){
            
            // Add conflict vertex to implication graph
            this->graph.addVertex(nullptr, decisionLevel, conflictClause.get()->getId());
            
            for(auto literals = conflictClause.get()->getLiterals().begin(); literals != conflictClause.get()->getLiterals().end();literals++ ){
                this->graph.addEdge(literals->second.pVar, nullptr);
            }
            
            return CONFLICT;
        }
        
        unitClause = this->formula.getUnitClause();
    }
    
    return SIMPLIFIED;
}

int algorithms::CompleteSolver::conflictAnalysis() {
    
    // Get the conflict clause k
    util::vertex* conflictVertex = this->graph.getVertex(nullptr);

    int currentDecisionLevel = conflictVertex->decisionLevel;

    // Get the antecedent clause of k
    int antecedentClauseID = conflictVertex->antecedentClauseID;
    auto antecedentClause = this->formula.getClauseSet().find(antecedentClauseID)->second;

    // Queue of literals assigned in this decision level
    std::queue<cnf::Literal> *q;
    std::unordered_set<int> *visitedLiterals;
    // Temporary learning clause - set
    auto tempClause = clauseToSet(antecedentClause);

    for(auto it = tempClause->begin(); it != tempClause->end(); ++it) {

        int id = *it;
        cnf::Literal l = antecedentClause->getLiteral(id).get();

        if(isImpliedLiteralAtDesicionLvl(l, currentDecisionLevel))
            q->push(l);
    }

    while(!q->empty()) {

        auto v = this->graph.getVertex(q->front().pVar);
        visitedLiterals->insert(q->front().pVar->getKey());
        q->pop();



        q->pop();
    }
    
    
        for(auto l : *tempClause) {
            //if(isImpliedLiteralAtDesicionLvl(l, currentDecisionLevel))
            //    q->push(l);
            
        }
    
        while(!q->empty()) {
    
            // get the vertex from the first var in que and remove it from queue
            auto v = this->graph.getVertex(q->front().pVar);
            visitedLiterals->insert(q->front().pVar->getKey());
            q->pop();
    
            int clID = v->antecedentClauseID;
            auto antecedentCluase = this->formula.getClauseSet().find(clID);
    
            //resolutionOperation(tempClause, antecedentClause, q, visitedLiterals, currentDecisionLevel);

        }
    return 0;
}

bool algorithms::CompleteSolver::isImpliedLiteralAtDesicionLvl(cnf::Literal l, int d) {
    auto vex = this->graph.getVertex(l.pVar);
    return d == vex->decisionLevel && vex->antecedentClauseID != -1;

}

std::unordered_set<int> *algorithms::CompleteSolver::clauseToSet(cnf::Clause *clause) {
    
    std::unordered_set<int> *l;
    
    for(auto kv = clause->getLiterals().begin(); kv != clause->getLiterals().end(); kv++) {
        auto literal = kv->second;
        literal.isNegated ? l->insert(-kv->first) : l->insert(kv->first);
    }
    
    return l;
}




