// Local Headers
#include "glitter.hpp"
#include "ExecutionerLight.h"

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <iostream>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define WINBUILD
#endif

int main(/*int argc, char * argv[]*/) {

    ExecutionerLight exec;

    return exec.run();
}
