#include <iostream>

#include "FixedPoint32.h"
#include "FixedPoint64.h"


using namespace Octree;
int main() {
    FixedPoint32 fp32(-11.0f);
    std::cout << fp32.getInteger() << '\n';

    return EXIT_SUCCESS;
}
