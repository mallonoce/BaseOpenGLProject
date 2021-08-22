// Local Headers
#include "glitter.hpp"
#include "ExecutionerAdvancedGL.h"

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define WINBUILD
#endif

int main(/*int argc, char * argv[]*/) {

    ExecutionerAdvancedGL exec;

    return exec.runDepthBuffer();
}
