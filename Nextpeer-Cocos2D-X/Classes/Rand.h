//
//  Created by Nextpeer development team.
//  Copyright (c) 2014 Nextpeer, Inc. All rights reserved.
//

#ifndef __NextpeerRand__
#define __NextpeerRand__

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

#endif /* defined(__NextpeerRand__) */

