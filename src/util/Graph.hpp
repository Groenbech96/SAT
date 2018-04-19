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
#include <map>
#include <string>
#include "Variable.hpp"

namespace util {
    
    /// Struct representing a vertex
    ///
    /// Contains id of a variable, decision level,
    ///
    /// where it was assigned it's value, and
    ///
    /// adjacency list of outgoing edges
    struct vertex {
        std::vector<vertex*> outgoingEdges;
        std::vector<vertex*> ingoingEdges;
        int decisionLevel;
        int antecedentClauseID;
        cnf::Variable* var;
        vertex(cnf::Variable* variable, int dl, int ac) : var(variable), decisionLevel(dl), antecedentClauseID(ac) {}
    };
    
    /// Graph made by a map of variable as key and vertex as value
    class Graph
    {
    public:
        typedef std::map<cnf::Variable*, vertex *> variableGraph;
        
        variableGraph graphMap;
        
        Graph() = default;
        /// Add vertex to the graph.
        /// \param variable Variable to add
        /// \param decisionLevel Decision level it was added at
        void addVertex(cnf::Variable *variable, int decisionLevel, int antecedentClauseID);
        
        /// Add outgoing edge from one vertex to another
        /// \param from Variable edge starts at
        /// \param to Variable edge ends at
        void addEdge(cnf::Variable* from, cnf::Variable* to);
        
        bool deleteVertex(cnf::Variable* vex);
        
        util::vertex* getVertex(cnf::Variable * v);
        std::string stringJsStyle();
        
    };
}

#endif /* Graph_hpp */
