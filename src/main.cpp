//
//  main.cpp
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include <iostream>
#include "App.hpp"

int main(int argc, char * argv[]) {
    // insert code here...
    Application::App app = Application::App(argc, argv);
    app.run();
}
