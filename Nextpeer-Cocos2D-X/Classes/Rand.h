//
//  Created by Nextpeer development team.
//  Copyright (c) 2013 Nextpeer, Inc. All rights reserved.
//

#ifndef ___RAND_H
#define ___RAND_H

#include "mtrand.h"

namespace nextpeer {
    class Rand
    {
    public:
        static void seed(unsigned long s);
        static unsigned long generate();
        static unsigned long generate(unsigned long min, unsigned long max);
    protected:
        static MTRand_int32 mGenerator;
    };
}

#endif // ___RAND_H

