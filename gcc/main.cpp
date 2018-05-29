//
//  main.cpp
//  SAT
//
//  Created by
//  Christian Schmidt - DTU,
//  Casper Skjærris    - DTU,
//  Magnus Grønbech   - DTU
//  Date: 17/02/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include <iostream>
#include "App.hpp"

int main(int argc, char * argv[]) {
    Application::App app = Application::App(argc, argv);
    return app.run();
}
