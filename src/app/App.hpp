//
//  App.hpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef App_hpp
#define App_hpp

#include "CDCL.hpp"
#include "Parser.hpp"

namespace Application {

    class App {
        
    public:
        /**
         * Application constructor
         * @param argc is the number of arguments. If n args is passed, then argv is n+1 !
         * @param argv is a pointer to the arguments. They are of type char
         */
        App(int argc, char* argv[]) : m_argc(argc), m_argv(argv) {}
        
        /**
         * Run application
         * @return an exitcode
         */
        int run();
        
    private:
        int m_argc;
        char** m_argv;
        
    };
    
}

#endif /* App_hpp */
