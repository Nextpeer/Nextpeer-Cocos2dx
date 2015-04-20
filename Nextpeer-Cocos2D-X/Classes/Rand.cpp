//
//  Created by Nextpeer development team.
//  Copyright (c) 2014 Nextpeer, Inc. All rights reserved.
//

#include "Rand.h"

namespace nextpeer {
    MTRand_int32 Rand::mGenerator;
    
    void Rand::seed(unsigned long s)
    {
        mGenerator.seed(s);
    }
    
    unsigned long Rand::generate()
    {
        return mGenerator();
    }
    
    unsigned long Rand::generate(unsigned long min, unsigned long max)
    {
        if (max<min) max = min;
        unsigned long r = Rand::generate();
        return (r % max) + min;
    }
}