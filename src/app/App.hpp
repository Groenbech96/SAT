//
//  App.hpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef App_hpp
#define App_hpp

#include "DTUSat.hpp"
#include "Schonings.hpp"
#include "Parser.hpp"

namespace Application {

    class App {
        
    public:
        ///
        /// Application constructor
        /// \param argc is the number of arguments. If n args is passed, then argv is n+1 !
        /// \param argv is a pointer to the arguments. They are of type char
        ///
        App(int argc, char* argv[]);
        
        ///
        ///Run application
        ///@return an exitcode
        ///
        int run();
        
    private:
        int m_argc;
        char** m_argv;
        
    };
    
}

#endif /* App_hpp */
