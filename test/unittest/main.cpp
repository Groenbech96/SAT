//
//  main.cpp
//  SatTests
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "gtest/gtest.h"

int main(int argc, char** argv) {
    // Init google mock and run all tests
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
