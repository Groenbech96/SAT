//
//  Graph.hpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 07/03/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <vector>
#include <set>
#include <stack>
#include <unordered_map>
#include <string>
#include <boost/optional.hpp>
#include "Variable.hpp"

namespace util {
    
    /// Struct representing a vertex
    ///
    /// Contains id of a variable, decision level,
    ///
    /// where it was assigned it's value, and
    ///
    /// adjacency list of outgoing edges
    struct Vertex {
        std::vector<Vertex*> outgoingEdges;
        std::vector<Vertex*> ingoingEdges;
        int decisionLevel;
        int antecedentClauseID;
        cnf::Variable* var;
        Vertex(cnf::Variable* variable, int dl, int ac) : var(variable), decisionLevel(dl), antecedentClauseID(ac) {}
    };
    
    
    /// Graph made by a map of variable as key and vertex as value
    class Graph
    {
    public:
        /// Map og variables and vertexes 
        std::unordered_map<cnf::Variable*, Vertex *> graphMap;
        std::stack<cnf::Variable*> *graphStack = new std::stack<cnf::Variable*>;
        
        
        Graph() = default;
        /// Add vertex to the graph.
        /// \param variable Variable to add
        /// \param decisionLevel Decision level it was added at
        /// \param antecedentClauseID Antecedent Clause ID
        void addVertex(cnf::Variable *variable, int decisionLevel, int antecedentClauseID);
        
        /// Add outgoing edge from one vertex to another
        /// \param from Variable edge starts at
        /// \param to Variable edge ends at
        void addEdge(cnf::Variable* from, cnf::Variable* to);
        
        bool deleteVertex(cnf::Variable* var);
       
        void undo(int lvl);
        
        //  util::vertex* getVertex(cnf::Variable * v);
        
        boost::optional<util::Vertex*>getVertex(cnf::Variable *v);
        
        std::stack<cnf::Variable*> *getStack();
        
        std::set<util::Vertex *> rm;
        
        std::string stringJsStyle();
        
        util::Vertex* getLastEdited();
        
    private:
        
        util::Vertex* lastEdit;
        
        
    };
}

#endif /* Graph_hpp */
