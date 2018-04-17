//
//  Randomizer.h
//  SAT
//
//  Created by Magnus Hartvig Grønbech on 17/04/2018.
//  Copyright © 2018 DTU. All rights reserved.
//

#ifndef Randomizer_h
#define Randomizer_h
#include <random>

namespace util {
    class Randomizer {
        
    public:
        /**
         * Each time function is called, it returns random int
         * \param from number
         * \param to number
         * \return int in range from and to (inclusive)
         */
        static int GetRandomInt(int from, int to) {
            std::random_device rand_dev;
            std::mt19937 generator(rand_dev());
            std::uniform_int_distribution<int> distr(from, to);
            return distr(generator);
        }
    };
    
}

#endif /* Randomizer_h */
